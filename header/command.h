#ifndef COMMAND_H
#define COMMAND_H

#include "piece.h"
#include "string"

enum CommandType{
    INVALID,
    LOAD,
    SAVE,
    QUIT,
    PLAY
};

struct Command {
    Command(CommandType t, std::string in, int ori = 0, int des = 0):
        type(t), raw(in), origin(ori), dest(des) { }
    CommandType type;
    int origin;
    int dest;
    std::string raw;
};
#endif