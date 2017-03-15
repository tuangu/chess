#ifndef UTILITY_H
#define UTILITY_H

#include <utility>

using std::pair;

// 1d to 2d: pair<file, rank>, ex: 36 -> pair<4, 5>
pair<int, int> to2d(int loc);

// 2d to 1d
int to1d(int f, int r);

#endif