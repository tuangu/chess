#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

#include <set>
#include <memory>

class Queen : public Piece {
public:
    Queen(int location, bool c);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
};

#endif