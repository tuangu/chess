#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

#include <set>
#include <memory>

class Bishop : public Piece {
public:
    Bishop(int location, bool c);
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

    void generatePossibleMoves(int);
};

#endif