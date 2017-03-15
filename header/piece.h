#ifndef PIECE_H
#define PIECE_H

#include <set>
#include <memory>

enum PieceType{
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
};

class Piece {
public:    
    virtual int getCurrentLocation() = 0;

    virtual bool getColor() = 0;

    virtual PieceType getType() = 0;

    virtual void setCurrentLocation(int) = 0;

    virtual bool isPossibleMove(int) = 0;

    virtual std::set<int> getBlockedPosition(int, int) = 0;

private:
    virtual void generatePossibleMoves(int) = 0;

    //virtual std::shared_ptr<std::set<int>> getPossibleMoves() = 0;
};

#endif