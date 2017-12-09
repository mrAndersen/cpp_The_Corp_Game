#include <fstream>
#include "SaveManager.h"
#include "EntityContainer.h"
#include "../../vendor/zlib/zlib.h"
#include "mingw.thread.h"

namespace SaveManager {

    void save() {
        std::thread saver([]() {
            sf::String buffer;
            std::ofstream file;

            file.open("save.dat", std::ios_base::trunc | std::ios::binary);

            if (!EntityContainer::items[SC_Game].empty()) {
                for (auto &e:EntityContainer::items[SC_Game]) {
                    auto data = e->serialize();
                    buffer += data + "\n";
                }

                auto zipped = compress_string(buffer.toAnsiString());
                file << zipped;
            }

            sf::String s;
            s += ResourceLoader::getTranslation("a.saved");

            if (System::versionType == "Debug") {
                s += " (" + std::to_string(file.tellp()) + " B)";
            }

            auto *hint = new TextEntity(System::c_green, 40);
            hint->setFixed(true);
            hint->setString(s);
            hint->setLeftOffset(250);
            hint->setTopOffset(600);
            hint->setDirection(Direction::Up);
            hint->setLiveTimeSeconds(5);

            file.close();
        });

        saver.detach();
    }

    void load() {
        std::thread loader([]() {
            std::fstream file("save.dat", std::ios::out | std::ios::binary | std::ios::in);
            std::string contents;

            while (!file.eof()) {
                contents.append(1, file.get());
            }

            auto decompressed = decompress_string(contents);
            file.close();
            auto data = System::split(decompressed, '\n');

            for (auto &e:data) {
                Entity::deserialize(e);
            }
        });
    }


    std::string compress_string(const std::string &str, int compressionlevel) {
        z_stream zs;                        // z_stream is zlib's control structure
        memset(&zs, 0, sizeof(zs));

        if (deflateInit(&zs, compressionlevel) != Z_OK)
            throw (std::runtime_error("deflateInit failed while compressing."));

        zs.next_in = (Bytef *) str.data();
        zs.avail_in = str.size();           // set the z_stream's input

        int ret;
        char outbuffer[32768];
        std::string outstring;

        // retrieve the compressed bytes blockwise
        do {
            zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
            zs.avail_out = sizeof(outbuffer);

            ret = deflate(&zs, Z_FINISH);

            if (outstring.size() < zs.total_out) {
                // append the block to the output string
                outstring.append(outbuffer,
                                 zs.total_out - outstring.size());
            }
        } while (ret == Z_OK);

        deflateEnd(&zs);

        if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
            std::ostringstream oss;
            oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
            throw (std::runtime_error(oss.str()));
        }

        return outstring;
    }

    std::string decompress_string(const std::string &str) {
        z_stream zs;                        // z_stream is zlib's control structure
        memset(&zs, 0, sizeof(zs));

        if (inflateInit(&zs) != Z_OK)
            throw (std::runtime_error("inflateInit failed while decompressing."));

        zs.next_in = (Bytef *) str.data();
        zs.avail_in = str.size();

        int ret;
        char outbuffer[32768];
        std::string outstring;

        // get the decompressed bytes blockwise using repeated calls to inflate
        do {
            zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
            zs.avail_out = sizeof(outbuffer);

            ret = inflate(&zs, 0);

            if (outstring.size() < zs.total_out) {
                outstring.append(outbuffer,
                                 zs.total_out - outstring.size());
            }

        } while (ret == Z_OK);

        inflateEnd(&zs);

        if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
            std::ostringstream oss;
            oss << "Exception during zlib decompression: (" << ret << ") "
                << zs.msg;
            throw (std::runtime_error(oss.str()));
        }

        return outstring;
    }

}