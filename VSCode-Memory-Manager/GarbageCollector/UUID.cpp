#include "UUID.h"


std::string const  UUID::CHARS  = "qwertyuiopasdfghjklzxcvbnm123456789";

std::string UUID::generateUUID() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, CHARS.size() - 1);
    std::string currentUUID = std::string(24, ' ');
    for (char &i : currentUUID) {
        int index = dist(mt);
        i = CHARS[index];
    }
    return currentUUID;
}