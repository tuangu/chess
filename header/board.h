#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <fstream>
#include <utility>
#include <vector>

#include "piece.h"
#include "command.h"

class Board {
public:
    Board();

    ~Board();

    void initializeNewGame();

    void loadSaveGame(std::ifstream&);

    void saveCurrentGame(std::ofstream&);

    void handleCommand(Command&);

    
private:
    std::map<int, Piece*> *titles;

    bool whiteTurn;

    std::vector<std::pair<string, string>> gameMoves;

    int to1d(int file, int rank);

    std::pair<int, int> toXy(int location); 

    void handleInvalidCmd();

    void validateMove(Command& c);
};
#endif