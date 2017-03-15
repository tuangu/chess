#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include "piece.h"
#include "board.h"

#include <string>
#include <memory>
#include <map>

class Board;
class Parser {
public:
    Command parseCommand(std::string&, Board*); 
    
private:
    bool isValidMove(int origin, int dest, Board*);

    int to1d(char, char);
};
#endif 