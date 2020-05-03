//
// Created by sebasmora on 15/4/20.
//

#ifndef GC_UUID_H
#define GC_UUID_H

#include "cstdlib"
#include "string"
#include <random>


class UUID {

private:
    static const std::string CHARS;

public:
    static std::string generateUUID();

};


#endif //GC_UUID_H
