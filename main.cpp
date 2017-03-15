#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "board.h"
#include "command.h"

using std::string;
using std::cin;
using std::cout;

int main() {
    Parser parser;
    Board board;

    string input;
    while (cin >> input) {
        Command c = parser.parse(input);

        if (c.type == command_type::QUIT) break;
        if (c.type == command_type::INVALID) continue;

        board.handleCommand(c);
    }

    return 0;
}