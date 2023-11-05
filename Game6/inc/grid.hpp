#pragma once

#include <vector>

class Grid {
    unsigned int screen_w;
    unsigned int screen_h;
    unsigned int cell_size;

    public:
    Grid(unsigned int screen_w, unsigned int screen_h, unsigned int cell_size);
    std::vector<std::vector<int>> data;
};

namespace GridUtil {
    void bfs(std::vector<std::vector<int>> &dist,
             const std::vector<std::vector<unsigned int>> &blocked, int startX,
             int startY);
    void compute_gradient_mtx(
        const std::vector<std::vector<int>> &grid1,
        std::vector<std::vector<std::pair<float, float>>> &grid2);

}; // namespace GridUtil