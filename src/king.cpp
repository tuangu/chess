#include "../header/king.h"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;

King::King(int location, bool c):
    color(c), currentLocation(location), 
    possibleMoves(shared_ptr<set<int>>(new set<int>())) {

    type = PieceType::KING;
    generatePossibleMoves(currentLocation);
}

int 
King::getCurrentLocation() {
    return currentLocation;
}

bool 
King::getColor() {
    return color;
}

PieceType
King::getType() {
    return type;
}

void 
King::setCurrentLocation(int newLoc) {
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}

bool
King::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if (search == possibleMoves->end())
        return false;
    else 
        return true;
}

// TODO
set<int>
King::getBlockedPosition(int ori, int des) {
    // return empty set in case of invalid origin and destination
    // if (ori > 64 || ori < 1 || des > 64 || des < 1)
    //     return set<int>();

    // pair<int, int> origin = to2d(ori);
    // pair<int, int> dest = to2d(des);

    return set<int>();
}

void 
King::generatePossibleMoves(int loc) {
    possibleMoves->clear();
    pair<int, int> location = to2d(loc);

    int left = location.first - 1;
    int right = location.first + 1;
    int top = location.second + 1;
    int bottom = location.second - 1;

    if (left > 0) {
        possibleMoves->insert(to1d(left, location.second));
        if (top < 9)
            possibleMoves->insert(to1d(left, top));
        if (bottom > 0)
            possibleMoves->insert(to1d(left, bottom));
    }

    if (right > 0) {
        possibleMoves->insert(to1d(right, location.second));
        if (top < 9)
            possibleMoves->insert(to1d(right, top));
        if (bottom > 0)
            possibleMoves->insert(to1d(right, bottom));
    }

    if (top < 9)
        possibleMoves->insert(to1d(location.first, top));

    if (bottom > 0)
        possibleMoves->insert(to1d(location.first, bottom));
}