#include "../header/parser.h"
#include "../header/command.h"
#include "../header/piece.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main() {
    vector<string> cmd = {
        "e2-e4",
        "Nb1-c3",
        "Rd3xd7",
        "e4xf5",
        "e4f5",
        "Ne4f5",
        " a6-f8",
        "Na6-f9",
        "load",
        "loodd",
        "save",
        "quit"
    };

    Parser p;
    for (auto s : cmd) {
        Command c = p.parse(s);
        if (c.type != command_type::PLAY) {
            cout << cmd << endl;
            cout << c.type << endl;
        } else {
            cout << c.str << endl;
            cout << c.type << endl;
            cout << c.piece << endl;
            cout << c.origin << endl;
            cout << c.dest << endl;
            cout << c.capture << endl;
        }
    }
}