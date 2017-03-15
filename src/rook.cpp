#include "../header/rook.h"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <cstdlib>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;

Rook::Rook(int location, bool c):
    color(c), currentLocation(location), 
    possibleMoves(shared_ptr<set<int>>(new set<int>())) {
    type = PieceType::ROOK;
    generatePossibleMoves(currentLocation);
}

int 
Rook::getCurrentLocation() {
    return currentLocation;
}

bool
Rook::getColor() {
    return color;
}

PieceType
Rook::getType() {
    return type;
}

void
Rook::setCurrentLocation(int newLoc) {
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}


bool 
Rook::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if (search == possibleMoves->end())
        return false;
    else 
        return true;
}

set<int>
Rook::getBlockedPosition(int ori, int des) {
    // return empty set in case of invalid origin and destination
    if (ori > 64 || ori < 1 || des > 64 || des < 1)
        return set<int>();

    pair<int, int> origin = to2d(ori);
    pair<int, int> dest = to2d(des);

    int diffFile = dest.first - origin.first;
    int diffRank = dest.second - origin.second;

    // legal move or not
    bool horizontal = (diffRank == 0);
    bool vertical = (diffFile == 0);

    if (!horizontal && !vertical)
        return set<int>();

    set<int> ret;
    if (horizontal) {
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
Rook::generatePossibleMoves(int loc) {
    possibleMoves->clear();
    pair<int, int> location = to2d(loc);

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