#include "../header/drawer.h"
#include "../header/board.h"
#include "../header/piece.h"

#include <ostream>
#include <string>
#include <memory>

using shared_ptr;
using std::string;


void
Drawer::draw(std::ostream& out, Board* board) {
    string rep = string(".", 64);
    
    for (auto beg = board->squares.begin(); beg != board->squares.end(); ++beg) {
        int pos = beg->first;
        shared_ptr<Piece> piece = beg->second;

        bool color = piece->getColor();
        PieceType type = piece->getType();

        char pie = pieceToString(color, type);
        rep[pos-1] = pie;  
    }

    out << "  " << "abcdefgh" << "\n";
    out << "\n";
    out << "1 " << rep.substr(0,8) << "\n";
    out << "2 " << rep.substr(8,8) << "\n";
    out << "3 " << rep.substr(16,8) << "\n";
    out << "4 " << rep.substr(24,8) << "\n";
    out << "5 " << rep.substr(32,8) << "\n";
    out << "6 " << rep.substr(40,8) << "\n";
    out << "7 " << rep.substr(48,8) << "\n";
    out << "8 " << rep.substr(56,8) << "\n";
    out << "\n";
}

char
Drawer::pieceToString(bool color, PieceType type) {
    char ret;

    switch (type) {
        case PieceType::PAWN :
            ret = 'p';
            break;
        case PieceType::BISHOP :
            ret = 'b';
            break;
        case PieceType::KNIGHT :
            ret = 'n';
            break;
        case PieceType::ROOK :
            ret = 'r';
            break;
        case PieceType::QUEEN :
            ret = 'q';
            break;
        case PieceType::KING :
            ret = 'k';
            break;
        default: break;
    }

    if (!color)
        ret -= 32;

    return ret; 
}