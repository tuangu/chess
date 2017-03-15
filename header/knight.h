#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

#include <set>
#include <memory>

class Knight : public Piece {
public:
    Knight(int location, bool c);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
};

#endif