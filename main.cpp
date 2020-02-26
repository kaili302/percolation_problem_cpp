#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include "grid.h"


std::vector<int> random(size_t size) {
    std::vector<int> nums(size);
    std::iota(nums.begin(), nums.end(), 0);
    std::random_shuffle(nums.begin(), nums.end());
    return nums;
}

int main(int argc, char* args[]) {
    const size_t N = std::stoi(std::string(args[1]));

    const auto runTest = [N] {
        Grid grid{N};
        for (const auto pos : random(N*N)) {
            grid.open(pos/N, pos%N);
            if (grid.isPercolated()) {
                break;
            }
        }
        std::cout << grid.percentOfOpenCells() << std::endl;
    };

    size_t repeat = std::stoi(std::string(args[2]));
    while (repeat--) { runTest(); }
}
