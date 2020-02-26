#include "grid.h"
#include <iterator>
#include <iostream>

Grid::Grid(size_t N)
: d_N {N}
, d_totalCells{N * N}
, d_openCells{0}
, d_virtualTop{d_totalCells}
, d_virtualBot{d_totalCells + 1}
, d_isOpen(d_totalCells, false)
, d_ufRoots(d_totalCells + 2)
{
    for (size_t cell = 0; cell < d_totalCells; ++cell) {
        if (cell < N) {
            d_ufRoots[cell] = d_virtualTop;
        }
        else if (cell >= N * (N -1)) {
            d_ufRoots[cell] = d_virtualBot;
        }
        else {
            d_ufRoots[cell] = cell;
        }
    }
    d_ufRoots[d_virtualTop] = d_virtualTop;
    d_ufRoots[d_virtualBot] = d_virtualBot;
}

bool Grid::isPercolated() {
    return getUfRoot(d_virtualTop) == getUfRoot(d_virtualBot);
}

void Grid::open(size_t row, size_t col) {
    size_t pos = row * d_N + col;
    if (pos >= d_totalCells || d_isOpen[pos]) {
        // invalid position or position is already opened
        return;
    }

    ++d_openCells;
    d_isOpen[pos] = true;

    connectAdjacents(pos);
}

double Grid::percentOfOpenCells() const {
    return d_openCells * 1.0 / d_totalCells;
}

size_t Grid::getUfRoot(size_t pos) {
    while (pos != d_ufRoots[pos]) {
        d_ufRoots[pos] = d_ufRoots[d_ufRoots[pos]];
        pos = d_ufRoots[pos];
    }
    return pos;
}

bool Grid::isOpen(size_t pos) const{
    return pos < d_totalCells && d_isOpen[pos];
}

void Grid::connectAdjacents(size_t pos) {
    if (isOpen(pos-1)) { d_ufRoots[getUfRoot(pos-1)] = pos; }
    if (isOpen(pos+1)) { d_ufRoots[getUfRoot(pos+1)] = pos; }
    if (isOpen(pos-d_N)) { d_ufRoots[getUfRoot(pos-d_N)] = pos; }
    if (isOpen(pos+d_N)) { d_ufRoots[getUfRoot(pos+d_N)] = pos; }
}
