#ifndef COMMAND_H
#define COMMAND_H

#include "piece.h"
#include "string"

enum command_type{
    INVALID,
    LOAD,
    SAVE,
    QUIT,
    PLAY
};

struct Command {
    command_type type;
    //bool color;
    piece_type piece;
    int origin;
    int dest;
    bool capture;
    std::string str;
};
#endif