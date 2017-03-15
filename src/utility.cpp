#include "utility.h"

#include <utility>
using std::pair;

pair<int, int> to2d(int loc) {
    // file, rank
    int f, r;

    f = 1;
    while ((loc - f) % 8 != 0)
        ++f;
    r = (loc - f) / 8 + 1;

    return pair<int, int>(f, r);
}

int to1d(int f, int r) {
    return f + (r-1)*8;
}