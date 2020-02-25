#pragma once

#include <vector>

constexpr int OPEN = 1;
constexpr int CLOSE = 0;

class Grid {
  public:
    explicit Grid(size_t N);
        // Create a grid of size [N * N]. All the cells are closed.

    bool isPercolated();
        // return true if grid is percolated.

    void openCell(size_t row, size_t col);
        // open the cell located at (row, col)

    double percentOfOpenCells() const;
        // return the percentage of opened cells

  private:
    size_t d_N;

    size_t d_size;

    size_t d_opens;

    size_t d_topRoot;

    size_t d_botRoot;

    std::vector<int> d_roots;

    size_t getRoot(size_t pos);

    void connectAdjacents(size_t pos);
};


