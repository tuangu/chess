#include <iostream>
#include <string>

#include "parser.h"
#include "board.h"
#include "command.h"

using std::string;
using std::cin;
using std::cout;

int main() {
    Parser* parser = new Parser();
    Drawer* drawer = new Drawer();
    Board board(parser, drawer);

    board.startGame();

    if (parser)
        delete parser;
    if (drawer)
        delete drawer;

    return 0;
}