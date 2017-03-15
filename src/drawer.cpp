#include "../header/drawer.h"
#include "../header/board.h"
#include "../header/piece.h"
#include "../header/utility.h"

#include <ostream>
#include <iostream>
#include <string>
#include <memory>
#include <utility>

using std::shared_ptr;
using std::string;
using std::endl;
using std::pair;
using std::cout;


void
Drawer::draw(Board* board) {
    char dot = '.';
    string rep(64, dot);
    
    for (auto beg = board->squares.begin(); beg != board->squares.end(); ++beg) {
        int pos = beg->first;
        shared_ptr<Piece> piece = beg->second;

        bool color = piece->getColor();
        PieceType type = piece->getType();

        char pie = pieceToString(color, type);
        rep[pos-1] = pie;  
        // pair<int, int> xy = to2d(pos);
        // cout << xy.first << ":" << xy.second;
        // cout << " " << (color ? "white " : "black ");
        // cout << type << endl; 
    }

    if (system("CLS")) 
        system("clear");
    cout << "white piece: lower letter, BLACK piece: UPPER letter" << endl;
    cout << "Command:\n\t[origin][dest]: move piece from origin(ex: e7) to dest(ex: e5)\n\tload: load saved game\n\tsave: save current game\n\trestart: reset board\n\tquit: quit game\n" << endl;
    cout << "   " << "a b c d e f g h " << endl;
    cout << "-------------------" << endl;
    for (string::size_type i = 0; i < 8; ++i) {
        cout << i+1 << "| ";
        string out = rep.substr(i*8, 8);
        for (auto i : out)
            cout << i << " ";
        cout << endl;
    }
    cout << "-------------------" << endl;
    cout << "   " << "a b c d e f g h " << endl;
    cout << (board->whiteTurn ? "WHITE" : "BLACK");
}

char
Drawer::pieceToString(bool color, PieceType type) {
    char ret;

    switch (type) {
        case PieceType::PAWN :
            ret = 'a';
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