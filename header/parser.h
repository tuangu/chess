#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include "piece.h"
#include "board"

#include <string>
#include <memory>
#include <map>

class Parser {
public:
    Parser();

    Command parseCommand(std::string&, Board*); 
    
private:
    bool isValidMove(int origin, int dest, Board*);

    int to1d(char, char);
};
#endif 