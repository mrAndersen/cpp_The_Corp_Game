#include <fstream>
#include <Office/OfficeClerk.h>
#include <cstring>
#include "../Characters/Clerk.h"
#include "../Characters/Manager.h"
#include "../Characters/Accountant.h"
#include "SaveManager.h"
#include "EntityContainer.h"
#include "../../vendor/zlib/zlib.h"
#include "thread"

namespace SaveManager {

    void save(bool zip) {
        std::thread saver([zip]() {
            sf::String buffer;
            std::ofstream file;

            file.open("save.dat", std::ios_base::trunc | std::ios::binary);

            if (!EntityContainer::items[SC_Game].empty()) {
                for (auto &e:EntityContainer::items[SC_Game]) {
                    if (e->isSerializable() && e->isSpawned()) {
                        buffer += e->serialize() + "\n";
                    }
                }

                std::vector<std::string> systemVars = {
                        std::to_string(System::cash),
                        System::gameTime.get(),
                };

                auto sysString = System::join(systemVars, ';');
                buffer += sysString;

                if(zip){
                    auto zipped = compress_string(buffer.toAnsiString());
                    file << zipped;
                }else{
                    file << buffer.toAnsiString();
                }
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

    void load(bool zip) {
        std::thread loader([zip]() {
            std::fstream file("save.dat", std::ios::out | std::ios::binary | std::ios::in);

            if (!file.is_open()) {
                return;
            }

            std::string contents;
            std::vector<std::string> data;

            while (!file.eof()) {
                contents.append(1, file.get());
            }

            if(zip){
                data = System::split(decompress_string(contents), '\n');
            }else{
                data = System::split(contents, '\n');
            }

            file.close();

            for (int i = 0; i < data.size(); ++i) {
                if (i != data.size() - 1) {
                    deserialize(data[i]);
                } else {
                    //populate sys vars
                    auto sysArray = System::split(data[i], ';');

                    System::cash = std::stod(sysArray[0]);
                    System::gameTime = GameTime(std::stoi(System::split(sysArray[1], ':')[0]), std::stoi(System::split(sysArray[1], ':')[1]));
                }
            }
        });

        loader.detach();
    }

    void deserialize(std::string &stringData) {
        auto array = System::split(stringData, ';');

        auto eType = static_cast<Entities>(std::stoi(array[0]));
        auto coordinates = sf::Vector2f(std::stof(array[6]), std::stof(array[7]));

        Entity *e;

        switch (eType) {
            case E_OfficeDefault:
                e = new OfficeClerk(coordinates);
                break;
            case E_ElevatorShaftMiddle:
                e = new ElevatorShaftMiddle(coordinates);
                break;
            case E_ElevatorShaftTop:
                e = new ElevatorShaftTop(coordinates);
                break;
            case E_ElevatorCabin:
                e = new ElevatorCabin(coordinates);
                break;
            case E_Clerk:
                e = new Clerk(coordinates);
                break;
            case E_Manager:
                e = new Manager(coordinates);
                break;
            case E_Accountant:
                e = new Accountant(coordinates);
                break;
            default:
                break;
        }

//        e->populate(array);
        e->spawn();
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
                outstring.append(outbuffer, zs.total_out - outstring.size());
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