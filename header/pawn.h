#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#include <set>
#include <memory>

class Pawn : public Piece {
public:
    Pawn(int location, bool c);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
    bool firstMove;
};

#endif