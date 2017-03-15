#include "../header/board.h"
#include "../header/command.h"
#include "../header/piece.h"
#include "../header/utility.h"

#include "../header/king.h"
#include "../header/queen.h"
#include "../header/rook.h"
#include "../header/bishop.h"
#include "../header/knight.h"
#include "../header/pawn.h"

#include <utility>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

using std::map;
using std::vector;
using std::string;
using std::shared_ptr;
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;

// white first
Board::Board(Parser* p, Drawer* d):
    squares(map<int, shared_ptr<Piece>()),
    moves(vector<string>()),
    parser(p), drawer(d), whiteTurn(true) {
    
}

// destructor
Board::~Board() {
    if (parser)
        delete parser;
    if (drawer)
        delete drawer;
}

// copy constructor
Board::Board(const Board& rhs):
    squares(rhs.squares), moves(rhs.moves),
    parser(rhs.parser), drawer(rhs.drawer), whiteTurn(rhs.whiteTurn) {
}

// copy-assign operator
void 
Board::operator=(const Board& rhs) {
    if (parser)
        delete parser;
    if (drawer)
        delete drawer;
    
    squares = rhs.squares;
    moves = rhs.moves;
    parser = rhs.parser;
    drawer = rhs.drawer;
    whiteTurn = rhs.whiteTurn;
}

// TODO
void
Board::startGame() {
    // print instruction

    while (true) {
        // draw board 
        drawer->draw(std::cout, this);

        // get input
        string in;
        cout << ": ";
        cin >> in;

        // parse input
        Command c = parser->parseCommand(in, this);

        // handle input
        if (c.type == CommandType::QUIT) {
            break;
        } else if (c.type == CommandType::LOAD) {
            string file;
            cin >> file;
            loadGame(file);
        } else if (c.type == CommandType::SAVE) {
            string file;
            cin >> file;
            saveGame(file);
        } else if (c.type == CommandType::RESTART) {
            initBoard();
        } else if (c.type == CommandType::CONTROL) {
            movePiece(c.origin, c.dest);
            moves.push_back(c.raw);
        } else if (c.type == CommandType::INVALID) {
            continue;
        }
    }
}

void 
Board::movePiece(int origin, int dest) {
    // remove piece at dest
    auto destPiece = squares.find(dest);
    if (destPiece != squares.end())
        squares.erase(destPiece);
    
    // copy piece from origin into dest
    auto originPiece = squares.find(origin);
    std::shared_ptr<Piece> chessPiece = originPiece->second;
    squares.insert(std::make_pair(dest, chessPiece));

    // remove piece at origin
    squares.erase(originPiece);

    // update currentLocation
    //squares[dest]->setCurrentLocation(dest);
    auto newDest = squares.find(dest);
    newDest->second->setCurrentLocation(dest);
}

void 
Board::saveGame(string fileName) {
    ofstream out;
    out.open(fileName);

    if (out) {
        for (int i = 0; i < moves.size(); ++i) {
            out << moves[i] << "\n";
        }

        if (whiteTurn)
            out << "1" << "\n";
        else 
            out << "0" << "\n";

        out.close();
    } else {
        // error 
        cout << "Error: can not write game to given file." << endl;
    }
}

void
Board::loadGame(string fileName) {
    ifstream in;
    
    in.open(fileName);
    if (in) {
        string line;
        vector<string> loaded;
        bool success = true;

        while (getline(in, line)) {
            loaded.push_back(line);
        }

        moves.clear();
        for (int i = 0, sz = loaded.size() - 1; i < sz; ++i) {
            Command c = parser->parseCommand(loaded[i].substr(0,4));
            if (c.type != CommandType::CONTROL) {
                // error
                success = false;
                cout << "Error: can not read game from given file." << endl;
                // init new board
                initBoard();
                break;
            } else {
                movePiece(c.origin, c.dest);
                moves.push_back(c.raw);
            }
        }
        // restore whiteTurn value
        if (success) {
            string oldState = loaded[loaded.size() - 1];
            if (oldState.substr(0,1) == "1")
                whiteTurn = true;
            else if (oldState.substr(0,1) == "0")
                whiteTurn = false;
            else {
                // error
                cout << "Error: can not read game from given file." << endl;
                cout << "Chessboard will be reset." << endl;
                initBoard();
            } 
        }
    } else {
        // error
        cout << "Error: can not read game from given file." << endl;
        cout << "Chessboard will be reset." << endl;
    }
}

// TODO
void 
Board::initBoard() {
    squares.clear();
    moves.clear();
    whiteTurn = true;

    // white
    squares[1] = shared_ptr<Piece>(new Rook(1, true));
    squares[2] = shared_ptr<Piece>(new Knight(2, true));
    squares[3] = shared_ptr<Piece>(new Bishop(3, true));
    squares[4] = shared_ptr<Piece>(new Queen(4, true));
    squares[5] = shared_ptr<Piece>(new King(5, true));
    squares[6] = shared_ptr<Piece>(new Bishop(6, true));
    squares[7] = shared_ptr<Piece>(new Knight(7, true));
    squares[8] = shared_ptr<Piece>(new Rook(8, true));

    for (int i = 9; i < 17; ++i)
        squares[i] = shared_ptr<Piece>(new Pawn(i, true));

    // black
    squares[57] = shared_ptr<Piece>(new Rook(57, false));
    squares[58] = shared_ptr<Piece>(new Knight(58, false));
    squares[59] = shared_ptr<Piece>(new Bishop(59, false));
    squares[60] = shared_ptr<Piece>(new Queen(60, false));
    squares[61] = shared_ptr<Piece>(new King(61, false));
    squares[62] = shared_ptr<Piece>(new Bishop(62, false));
    squares[63] = shared_ptr<Piece>(new Knight(63, false));
    squares[64] = shared_ptr<Piece>(new Rook(64, false));

    for (int i = 49; i < 57; ++i) 
        squares[i] = shared_ptr<Piece>(new Pawn(i, false));

}

