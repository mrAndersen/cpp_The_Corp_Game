#ifndef THE_CORP_GAME_SAVEMANAGER_H
#define THE_CORP_GAME_SAVEMANAGER_H

#include "Basic/Entity.h"
#include "../../vendor/zlib/zlib.h"


namespace SaveManager {

    void save(bool zip = false);
    void load(bool zip = false);
    void deserialize(std::string &stringData);

    std::string compress_string(const std::string &str, int compressionlevel = Z_BEST_SPEED);
    std::string decompress_string(const std::string &str);
};


#endif //THE_CORP_GAME_SAVEMANAGER_H
