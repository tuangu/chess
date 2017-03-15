#include "../header/board.h"
#include "../header/command.h"
#include "../header/piece.h"

#include "../header/king.h"
#include "../header/queen.h"
#include "../header/rook.h"
#include "../header/bishop.h"
#include "../header/knight.h"
#include "../header/pawn.h"

#include <utility>
#include <map>
#include <set>

using std::map;

Board::Board(): titles(new map<int, Piece*>()), whiteTurn(true) {
}

Board::~Board() {
}

void
Board::initializeNewGame() {
    // white
    titles->insert(to1d(1,1), new Rook()); 
    titles->insert(to1d(8,1), new Rook());
    titles->insert(to1d(2,1), new Knight()); 
    titles->insert(to1d(7,1), new Knight());
    titles->insert(to1d(3,1), new Bishop());
    titles->insert(to1d(6,1), new Bishop());
    titles->insert(to1d(4,1), new Queen());
    titles->insert(to1d(5,1), new King());
    for (int i = 1; i < 9; ++i) 
        titles->insert(to1d(i,2), new Pawn());

    // black
    titles->insert(to1d(1,8), new Rook()); 
    titles->insert(to1d(8,8), new Rook());
    titles->insert(to1d(2,8), new Knight()); 
    titles->insert(to1d(7,8), new Knight());
    titles->insert(to1d(3,8), new Bishop());
    titles->insert(to1d(6,8), new Bishop());
    titles->insert(to1d(4,8), new Queen());
    titles->insert(to1d(5,8), new King());
    for (int i = 1; i < 9; ++i) 
        titles->insert(to1d(i,7), new Pawn());

    
}

void
Board::handleCommand(Command &c) {
    auto square = titles->find(c.origin);
    if (square == titles->end()) {
        handleInvalidCmd();
        return;
    }

    Piece* men = square->second;

    if ((men->pieceType() != c.type) || 
        (men->getColor() ^ whiteTurn) ) {
        handleInvalidCmd();
        return;
    }

    //bool capture = c.capture;

    if (c.capture) {
        auto destSqr = titles->find(c.dest);
        if (destSqr == titles->end()) {
            handleInvalidCmd();
            return;
        }
    }

    if (men->checkPossibleMoves(c.dest)) {
        if (validateMove(c)) {
            // remove piece at destination
            if (c.capture)
                titles->erase(c.dest);
            //titles->erase(c.origin);

            // insert piece to the destination
            titles->insert(c.dest, square->second);

            // update new location
            titles->at(dest)->

        } else {
            handleInvalidCmd();
            return;
        }
    } else {
        handleInvalidCmd();
        return;
    }

}


//!-- utility
int 
Board::to1d(int file, int rank) {
    if (file < 1 || file > 8 || rank < 1 || rank > 8)
        return 0;
    else
        return file + (rank-1)*8;
}

std::pair<int, int> 
Board::toXy(int location) {
    if (location > 64 || location < 1)
        return make_pair<int, int>(0, 0);
    
    std::pair<int, int> ret(1, 0);
    while ((location - ret.first) % 8 != 0)
        ++ret.first;
    ret.second = (location - ret.first) / 8 + 1;

    return ret;
}