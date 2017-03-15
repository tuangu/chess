#ifndef UTILITY_H
#define UTILITY_H

#include <utility>

using std::pair;

// 1d to 2d: pair<file, rank>, ex: 36 -> pair<4, 5>
pair<int, int> to2d(int loc) {
    // file, rank
    int f, r;

    f = 1;
    while ((loc - f) % 8 != 0)
        ++f;
    r = (loc - f) / 8 + 1;

    return pair<int, int>(f, r);
}

// 2d to 1d
int to1d(int f, int r) {
    return f + (r-1)*8;
}

#endif