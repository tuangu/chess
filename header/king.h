#ifndef KING_H
#define KING_H

#include "piece.h"

#include <set>
#include <memory>

class King : public Piece {
public:
    King(int location, bool c);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
};

#endif