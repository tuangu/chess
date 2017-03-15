#include "../header/pawn.h"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <cstdlib>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;

Pawn::Pawn(int location, bool c, bool first):
    color(c), currentLocation(location), 
    possibleMoves(shared_ptr<set<int>>(new set<int>())),
    firstMove(first) {
    type = PieceType::PAWN;
    generatePossibleMoves(currentLocation);
}

int 
Pawn::getCurrentLocation() {
    return currentLocation;
}

bool
Pawn::getColor() {
    return color;
}

PieceType
Pawn::getType() {
    return type;
}

void
Pawn::setCurrentLocation(int newLoc) {
    // set firstMove to false in the first call to setCurrentLocation
    if (firstMove)
        firstMove = false;
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}


bool 
Pawn::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if (search == possibleMoves->end())
        return false;
    else 
        return true;
}

// TODO
set<int>
Pawn::getBlockedPosition(int ori, int des) {
    // return empty set in case of invalid origin and destination
    if (ori > 64 || ori < 1 || des > 64 || des < 1)
        return set<int>();

    set<int> ret;
    pair<int, int> origin = to2d(ori);
    pair<int, int> dest = to2d(des);

    if (firstMove && (origin.second == 2) && (dest.second == 4))
        ret.insert(to1d(origin.first, origin.second + 1));
    else if (firstMove && (origin.second == 7) && (dest.second == 5))
        ret.insert(to1d(origin.first, origin.second - 1));

    return ret;
}

//TODO
void 
Pawn::generatePossibleMoves(int loc) {
    possibleMoves->clear();
    pair<int, int> location = to2d(loc);

    int left, right, ver;
    left = location.first - 1;
    right = location.first + 1;

    // white pawn
    if (color == true)
        ver = location.second + 1;
    // black pawn
    else
        ver = location.second - 1;

    // first move only
    if (firstMove && (location.second == 2))
        possibleMoves->insert(to1d(location.first, location.second + 2));
    else if (firstMove && (location.second == 7))
        possibleMoves->insert(to1d(location.first, location.second - 2));

    //
    if (ver > 0 && ver < 9) {
        if (left > 0)
            possibleMoves->insert(to1d(left, ver));
        if (right < 9)
            possibleMoves->insert(to1d(right, ver));
        possibleMoves->insert(to1d(location.first, ver));
    }
}