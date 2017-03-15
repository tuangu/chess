#include "../header/knight.cpp"

#include "../header/piece.h"
#include "../header/utility.h"

#include <set>
#include <memory>
#include <utility>

using std::pair;
using std::set;
using std::shared_ptr;

Knight::Knight(int location, bool c):
    color(c), currentLocation(location),
    possibleMoves(shared_ptr<set<int>>(new set<int>())) {
    type = PieceType::KNIGHT;
    generatePossibleMoves(currentLocation);       
}

int 
Knight::getCurrentLocation() {
    return currentLocation;
}

bool
Knight::getColor() {
    return color;
}

PieceType
Knight::getType() {
    return type;
}

void
Knight::setCurrentLocation(int newLoc) {
    currentLocation = newLoc;
    generatePossibleMoves(currentLocation);
}

bool
Knight::isPossibleMove(int loc) {
    auto search = possibleMoves->find(loc);
    if(search == possibleMoves->end())
        return false;
    else
        return true;
}

set<int>
Knight::getBlockedPosition(int ori, int des) {
    return set<int>();
}

void 
Knight::generatePossibleMoves(int loc) {
    possibleMoves->clear();
    pair<int, int> location = to2d(loc);

    int left_1 = location.first - 1;
    int left_2 = location.first - 2;
    int right_1 = location.first + 1;
    int right_2 = location.first + 2;

    int top_2 = location.second + 2;
    int top_1 = location.second + 1;
    int bottom_2 = location.second - 2;
    int bottom_1 = location.second - 1;

    if (left_1 > 0 && bottom_2 > 0)
        possibleMoves->insert(to1d(left_1, bottom_2));
    if (left_1 > 0 && top_2 < 9)
        possibleMoves->insert(to1d(left_1, top_2));
    if (left_2 > 0 && bottom_1 > 0)
        possibleMoves->insert(to1d(left_2, bottom_1));
    if (left_2 > 0 && top_1 < 9)
        possibleMoves->insert(to1d(left_2, top_1));

    if (right_1 < 9 && bottom_2 > 0) 
        possibleMoves->insert(to1d(right_1, bottom_2));
    if (right_1 < 9 && top_2 < 9)
        possibleMoves->insert(to1d(right_1, top_2));
    if (right_2 < 9 && bottom_1 > 0)
        possibleMoves->insert(to1d(right_2, bottom_1));
    if (right_2 < 9 && top_1 < 9)
        possibleMoves->insert(to1d(right_2, top_1));   
}