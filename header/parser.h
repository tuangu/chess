#ifndef PARSER_H
#define PARSER_H

#include "command.h"

#include <string>

class Parser {
public:
    Parser() = default;

    Command parse(std::string&); 

private:
    int files(char);
    int ranks(char); 
};
#endif 