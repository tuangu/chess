#include "../header/bishop.h"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <cstdlib>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;


Bishop::Bishop(int location, bool c):
    color(c), currentLocation(location), 
    possibleMoves(shared_ptr<set<int>>(new set<int>())) {
    type = PieceType::BISHOP;
    generatePossibleMoves(currentLocation);
}

int 
Bishop::getCurrentLocation() {
    return currentLocation;
}

bool
Bishop::getColor() {
    return color;
}

PieceType
Bishop::getType() {
    return type;
}

void
Bishop::setCurrentLocation(int newLoc) {
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}


bool 
Bishop::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if (search == possibleMoves->end())
        return false;
    else 
        return true;
}

set<int>
Bishop::getBlockedPosition(int ori, int des) {
    // return empty set in case of invalid origin and destination
    if (ori > 64 || ori < 1 || des > 64 || des < 1)
        return set<int>();

    pair<int, int> origin = to2d(ori);
    pair<int, int> dest = to2d(des);

    int diffFile = dest.first - origin.first;
    int diffRank = dest.second - origin.second;

    // return empty set if origin and dest are not legal move
    if (std::abs(diffFile) != std::abs(diffRank))
        return set<int>();
    
    // generate blocked position
    set<int> ret;
    for (int i = 1, diff = std::abs(diffFile); i < diff; ++i) {
        int x = origin.first + i*diffFile/std::abs(diffFile);
        int y = origin.second + i*diffRank/std::abs(diffRank);
        ret.insert(to1d(x,y));
    }

    return ret;
}

void
Bishop::generatePossibleMoves(int loc) {
    possibleMoves->clear();
    pair<int, int> location = to2d(loc);

    // left-bottom 
    for (int x = location.first, y = location.second; x > 1 && y > 1;)
        possibleMoves->insert(to1d(--x, --y));

    // left-top
    for (int x = location.first, y = location.second; x > 1 && y < 8;)
        possibleMoves->insert(to1d(--x, ++y));

    // right-bottom
    for (int x = location.first, y = location.second; x < 8 && y > 1;)
        possibleMoves->insert(to1d(++x, --y));

    // right-top
    for (int x = location.first, y = location.second; x < 8 && y < 8;)
        possibleMoves->insert(to1d(++x, ++y));
}
