#ifndef COMMAND_H
#define COMMAND_H

#include "piece.h"
#include "string"

enum CommandType{
    INVALID,
    LOAD,
    SAVE,
    QUIT,
    CONTROL,
    RESTART
};

struct Command {
    Command() = default;
    Command(CommandType t, std::string in, int ori = 0, int des = 0):
        type(t), origin(ori), dest(des), raw(in) { }
    CommandType type;
    int origin;
    int dest;
    std::string raw;
};
#endif