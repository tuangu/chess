#include "../header/queen.h"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <cstdlib>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;

Queen::Queen(int location, bool c):
    color(c), currentLocation(location), 
    possibleMoves(shared_ptr<set<int>>(new set<int>())) {
    type = PieceType::QUEEN;
    generatePossibleMoves(currentLocation);
}

int 
Queen::getCurrentLocation() {
    return currentLocation;
}

bool
Queen::getColor() {
    return color;
}

PieceType
Queen::getType() {
    return type;
}

void
Queen::setCurrentLocation(int newLoc) {
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}


bool 
Queen::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if (search == possibleMoves->end())
        return false;
    else 
        return true;
}

set<int>
Queen::getBlockedPosition(int ori, int des) {
    // return empty set in case of invalid origin and destination
    if (ori > 64 || ori < 1 || des > 64 || des < 1)
        return set<int>();

    pair<int, int> origin = to2d(ori);
    pair<int, int> dest = to2d(des);

    int diffFile = dest.first - origin.first;
    int diffRank = dest.second - origin.second;

    // legal move or not
    bool diagonal = (std::abs(diffFile) == std::abs(diffRank));
    bool horizontal = (diffRank == 0);
    bool vertical = (diffFile == 0);

    if (!diagonal && !horizontal && !vertical)
        return set<int>();

    // generate blocked position
    set<int> ret;
    if (diagonal) {
        for (int i = 1, diff = std::abs(diffFile); i < diff; ++i) {
            int x = origin.first + i*diffFile/std::abs(diffFile);
            int y = origin.second + i*diffRank/std::abs(diffRank);
            ret.insert(to1d(x,y));
        }
    } else if (horizontal) {
        for (int i = 1, diff = std::abs(diffFile); i < diff; ++i) {
            int x = origin.first + i*diffFile/std::abs(diffFile);
            ret.insert(to1d(x, origin.second));
        }
    } else if (vertical) {
        for (int i = 1, diff = std::abs(diffRank); i < diff; ++i) {
            int y = origin.second + i*diffRank/std::abs(diffRank);
            ret.insert(to1d(origin.first, y));
        }
    }

    return ret;
}

void 
Queen::generatePossibleMoves(int loc) {
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

    // left
    for (int x = location.first; x > 1;)
        possibleMoves->insert(to1d(--x, location.second));
    
    // right
    for (int x = location.first; x < 8;)
        possibleMoves->insert(to1d(++x, location.second));

    // up
    for (int y = location.second; y < 8;)
        possibleMoves->insert(to1d(location.first, ++y));
    
    // down
    for (int y = location.second; y > 1;)
        possibleMoves->insert(to1d(location.first, --y));
}