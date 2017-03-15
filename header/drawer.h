#ifndef DRAWER_H
#define DRAWER_H

#include "board.h"
#include "piece.h"

#include <ostream>
#include <string>

class Board;
class Drawer {
public:
    void draw(Board* board);
private:
    char pieceToString(bool color, PieceType type);
    
};

#endif