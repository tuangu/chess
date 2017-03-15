#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#include <set>
#include <memory>

class Pawn : public Piece {
public:
    Pawn(int location, bool c, bool firstMove);
    int getCurrentLocation();
    bool getColor();
    PieceType getType();
    void setCurrentLocation(int);
    bool isPossibleMove(int);
    std::set<int> getBlockedPosition(int, int);
private:
    bool color;
    PieceType type;
    int currentLocation;
    std::shared_ptr<std::set<int>> possibleMoves;
    bool firstMove;

    void generatePossibleMoves(int);
};

#endif