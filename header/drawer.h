#ifndef DRAWER_H
#define DRAWER_H

#include "board.h"
#include "piece.h"

#include <ostream>

class Drawer {
public:
    void draw(std::ostream& out, Board* board);

private:
    char pieceToString(bool color, PieceType type);
};

#endif