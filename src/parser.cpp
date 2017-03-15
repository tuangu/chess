#include "../header/parser.h"
#include "../header/command.h"
#include "../header/piece.h"
#include "../header/board.h"

#include <string>
#include <memory>
#include <set>

using std::set;
using std::string;

Command
Parser::parseCommand(string& in, Board* board) {
    Command ret;

    if (in == "quit")
        ret = Command(CommandType::QUIT, in);

    else if (in == "save")
        ret = Command(CommandType::SAVE, in);

    else if (in == "load")
        ret = Command(CommandType::LOAD, in);

    else if (in == "restart")
        ret = Command(CommandType::RESTART, in);

    else if (in.length() == 4) {
        int origin = to1d(in[0], in[1]);
        int dest = to1d(in[2], in[3]);

        bool isValid = isValidMove(origin, dest, board);
        if (isValid)
            ret = Command(CommandType::CONTROL, in, origin, dest);
        else 
            ret = Command(CommandType::INVALID, in);
    }

    else 
        ret = Command(CommandType::INVALID, in);

    return ret;
}

// check if the input contains valid move or not
bool 
Parser::isValidMove(int origin, int dest, Board* board) {
    // invalid input, ex: 
    if (origin == 0 || dest == 0)
        return false;
    
    // check at origin point
    auto originPiece = board->titles.find(origin);
    if (originPiece == board->titles.end())
        return false;

    // check if piece at origin can move to destination point or not
    bool isPossibleMove = board->titles.at(origin)->isPossibleMove(dest);
    if (!isPossibleMove)
        return false;
    
    // if piece is a pawn, it can only perform a capture move if there is 
    // a enemy piece at the destination square
    if ((board->titles.at(origin)->getType() == PieceType::PAWN)
        && (((dest - origin) % 8) != 0) ) {
        auto searchCapture = board->titles.find(dest);
        if (searchCapture == board->titles.end())
            return false;
    }
    
    // check if piece at origin and dest are friendly or not
    auto searchDest = board->titles.find(dest);
    if (searchDest != board->titles.end())
        if (searchDest->second->getColor() == originPiece->second->getColor())
            return false;
    
    // check if piece is blocked by other piece or not
    set<int> blockedPos = originPiece->second->getBlockedPosition(origin, dest);
    for (auto beg = blockedPos.begin(); beg != blockedPos.end(); ++beg) {
        auto searchBlocked = board->titles.find(*beg);
        if (searchBlocked != board->titles.end())
            return false;
    }

    // otherwise, return true
    return true;
}

// 2d to 1d, ex: e5 = 20
// if rank or file or both is invalid (!a-h, !1-8), return 0
int 
Parser::to1d(char file, char rank) {
    int f, r;

    // file to int
    switch (file) {
        case 'a':
            f = 1;
            break;
        case 'b':
            f = 2;
            break;
        case 'c':
            f = 3;
            break;
        case 'd':
            f = 4;
            break;
        case 'e':
            f = 5;
            break;
        case 'f':
            f = 6;
            break;
        case 'g':
            f = 7;
            break;
        case 'h':
            f = 8;
            break;
        default:
            f = 0;
            break;
    }

    // rank to int
    if ((rank > 48) && (rank < 57))
        r =  (int)rank - 48;
    else
        r = 0;

    if (f == 0 || r == 0)
        return 0; 
    else
        return f + (r - 1)*8;
}