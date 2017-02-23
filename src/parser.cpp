#include "../header/parser.h"
#include "../header/command.h"
#include "../header/piece.h"

#include <string>

using std::string;

Command
Parser::parse(string& in) {
    if (in == "quit") {
        Command c;
        c.type = command_type::QUIT;
        return c;
    }

    if (in == "save") {
        Command c;
        c.type = command_type::SAVE;
        return c;
    }

    if (in == "load") {
        Command c;
        c.type = command_type::LOAD;
        return c;
    }

    // command of PAWN
    // ex: e5-e7, e5xf6
    if (in.length() == 5) {
        Command c;

        char origin_c = in[0];
        char origin_i = in[1];
        char dash = in[2];
        char dest_c = in[3];
        char dest_i = in[4];

        // dash should be '-' or 'x'
        bool capture;
        if (dash == '-') 
            capture = false;
        else if (dash == 'x')
            capture = true;
        else {
            c.type = command_type::INVALID;
            return c;
        }

        int origin_f = files(origin_c);
        int origin_r = ranks(origin_i);
        int dest_f = files(dest_c);
        int dest_r = ranks(dest_i);

        // check whether origin and dest are valid
        if (origin_f == 0 || origin_r == 0 || dest_f == 0 || dest_r == 0) {
            c.type = command_type::INVALID;
            return c;
        }

        c.type = command_type::PLAY;
        c.piece = piece_type::PAWN;
        c.origin = origin_f + (origin_r - 1)*8;
        c.dest = dest_f + (dest_r - 1)*8;
        c.capture = capture ? true : false;
        c.str = in;

        return c; 
    }

    // the rest
    if (in.length() == 6) {
        Command c;

        piece_type chessType;
        char chessMen = in[0];
        switch (chessMen) {
            case 'K':
                chessType = piece_type::KING;
                break;
            case 'Q':
                chessType = piece_type::QUEEN;
                break;
            case 'R':
                chessType = piece_type::ROOK;
                break;
            case 'B':
                chessType = piece_type::BISHOP;
                break;
            case 'N':
                chessType = piece_type::KNIGHT;
                break;
            default:
                c.type = command_type::INVALID;
                return c;
        }

        char origin_c = in[1];
        char origin_i = in[2];
        char dash = in[3];
        char dest_c = in[4];
        char dest_i = in[5];
            
        // dash should be '-' or 'x'
        bool capture;
        if (dash == '-') 
            capture = false;
        else if (dash == 'x')
            capture = true;
        else {
            c.type = command_type::INVALID;
            return c;
        }

        int origin_f = files(origin_c);
        int origin_r = ranks(origin_i);
        int dest_f = files(dest_c);
        int dest_r = ranks(dest_i);

        // check whether origin and dest are valid
        if (origin_f == 0 || origin_r == 0 || dest_f == 0 || dest_r == 0) {
            c.type = command_type::INVALID;
            return c;
        }

        c.type = command_type::PLAY;
        c.piece = chessType;
        c.origin = origin_f + (origin_r - 1)*8;
        c.dest = dest_f + (dest_r - 1)*8;
        c.capture = capture ? true : false;
        c.str = in;

        return c; 
    }

    //otherwise, return invalid command
    Command c;
    c.type = command_type::INVALID;
    return c;
}

int
Parser::files(char c) {
    int ret;

    switch (c) {
        case 'a':
            ret = 1;
            break;
        case 'b':
            ret = 2;
            break;
        case 'c':
            ret = 3;
            break;
        case 'd':
            ret = 4;
            break;
        case 'e':
            ret = 5;
            break;
        case 'f':
            ret = 6;
            break;
        case 'g':
            ret = 7;
            break;
        case 'h':
            ret = 8;
            break;
        default:
            ret = 0;
            break;
    }

    return ret;
}

int 
Parser::ranks(char c) {
    int tmp = c;

    if ((c > 48) && (c < 57))
        return tmp - 48;
    else
        return 0;
}