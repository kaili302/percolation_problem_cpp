#include "grid.h"

Grid::Grid(size_t N)
: d_N { N }
, d_size{ N * N }
, d_topRoot{ d_size }
, d_botRoot{ d_size + 1 }
, d_roots( d_size + 2 )
{
    for (size_t cell = 0; cell < d_size; ++cell) {
        if (cell < N) {
            d_roots[cell] = d_topRoot;
        }
        else if (cell >= N * (N -1)) {
            d_roots[cell] = d_botRoot;
        }
        else {
            d_roots[cell] = cell;
        }
    }
    d_roots[d_topRoot] = d_topRoot;
    d_roots[d_botRoot] = d_botRoot;
}

bool Grid::isPercolated() {
    return getRoot(d_topRoot) == getRoot(d_botRoot);
}

void Grid::openCell(size_t row, size_t col) {
    size_t pos = row * d_N + col;
    if (pos >= d_size || d_roots[pos] != pos) {
        // invalid position or position is already opened
        return;
    }

    ++d_opens;

    connectAdjacents(pos);
}

double Grid::percentOfOpenCells() const {
    return d_opens * 1.0 / d_size;
}

size_t Grid::getRoot(size_t pos) {
    while (pos != d_roots[pos]) {
        d_roots[pos] = d_roots[d_roots[pos]];
        pos = d_roots[pos];
    }
    return pos;
}

void Grid::connectAdjacents(size_t pos) {
    d_roots[pos-1] = pos;
    d_roots[pos+1] = pos;
    d_roots[pos-d_N] = pos;
    d_roots[pos+d_N] = pos;
}
