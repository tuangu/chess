#ifndef BOARD_H
#define BOARD_H

#include "drawer.h"
#include "parser.h"
#include "piece.h"
#include "command.h"

#include <map>
#include <vector>
#include <string>

class Drawer;
class Parser;

class Board {
    friend class Parser;
    friend class Drawer;
public:
    Board(Parser* parser, Drawer* drawer);
    ~Board();
    Board(const Board& rhs);
    void operator=(const Board& rhs);
    void startGame();

private:
    std::map<int, std::shared_ptr<Piece>> squares;
    std::vector<std::string> moves;
    Parser* parser;
    Drawer* drawer;
    bool whiteTurn;

    void movePiece(int origin, int dest);
    void saveGame(std::string fileName);
    void loadGame(std::string fileName);
    void initBoard();
};
#endif