#pragma once

#include <vector>

class Grid {
  public:
    explicit Grid(size_t N);
        // Create a grid of size [N * N]. All the cells are closed.

    bool isPercolated();
        // return true if grid is percolated.

    void open(size_t row, size_t col);
        // open the cell located at (row, col)

    double percentOfOpenCells() const;
        // return the percentage of opened cells

  private:
    size_t d_N;

    size_t d_totalCells;

    size_t d_openCells;

    size_t d_virtualTop;
        // All cells at first row are connected to the virtual top

    size_t d_virtualBot;
        // All cells at bottom row are connected to the virtual bottom

    std::vector<bool> d_isOpen;
        // Track if a cell is opened

    bool isOpen(size_t pos) const;
        // Return true if 'pos' **is valid** and cell is open

    std::vector<int> d_ufRoots;
        // Union-find roots tracker

    size_t getUfRoot(size_t pos);
        // Union-find get root of 'pos'

    void connectAdjacents(size_t pos);
        // Connect all adjacent cells (up, down, left, right)
};
