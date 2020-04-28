
#ifndef GC_UUID_H
#define GC_UUID_H

#include "cstdlib"
#include "string"
#include <random>


    const std::string CHARS = "qwertyuiopasdfghjklzxcvbnm123456789";
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, CHARS.size() - 1);

    std::string generateUUID() {

        std::string currentUUID = std::string(24, ' ');
        for (char &i : currentUUID) {

            int index = dist(mt);
            i = CHARS[index];
        }
        return currentUUID;
    }

#endif //GC_UUID_H
