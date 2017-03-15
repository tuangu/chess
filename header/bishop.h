#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

#include <set>
#include <memory>

class Bishop : public Piece {
public:
    Bishop(int location, bool c);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
};

#endif