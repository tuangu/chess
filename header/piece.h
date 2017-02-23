#ifndef PIECE_H
#define PIECE_H

#include <set>

enum piece_type{
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
};

class Piece {
public:
    virtual ~Piece();
    
    virtual std::set<int> possibleMoves() = 0;
    
    virtual void generateMoves() = 0;
    
    virtual bool getColor() = 0;
    
    virtual piece_type pieceType() = 0;

    virtual bool checkPossibleMoves(int dest) = 0;

    virtual void updateCurrentLocation(int lo) = 0;
private:
    bool color;
    piece_type type;
    int currentLocation;
    bool died;
};

#endif