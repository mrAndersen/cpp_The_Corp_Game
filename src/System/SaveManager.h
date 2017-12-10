#ifndef THE_CORP_GAME_SAVEMANAGER_H
#define THE_CORP_GAME_SAVEMANAGER_H

#include "../../vendor/zlib/zlib.h"

namespace SaveManager {

    void save();
    void load();
    void deserialize(std::string &stringData);

    std::string compress_string(const std::string &str, int compressionlevel = Z_BEST_SPEED);
    std::string decompress_string(const std::string &str);
};


#endif //THE_CORP_GAME_SAVEMANAGER_H
