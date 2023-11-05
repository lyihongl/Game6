#include "inc/grid.hpp"
#include <utility>
#include <queue>
#include <cmath>

Grid::Grid(unsigned int screen_w, unsigned int screen_h, unsigned int cell_size)
    : screen_w(screen_w), screen_h(screen_h), cell_size(cell_size),
      data(screen_h / cell_size, std::vector<int>(screen_w / cell_size, 0)) {
}

void GridUtil::bfs(std::vector<std::vector<int>> &dist,
                   const std::vector<std::vector<unsigned int>> &blocked,
                   int startX, int startY) {

    std::vector<std::vector<unsigned int>> visited(
        dist.size(), std::vector<unsigned int>(dist[0].size(), 0));

    std::queue<std::pair<int, int>> work;
    work.push({startX, startY});

    // clang-format off
    std::vector<std::pair<int, int>> dirs = {
        {0, 1}, 
        {0, -1}, 
        {1, 1}, 
        {-1, -1}, 
        {-1, 0}, 
        {1, 0}, 
        {-1, 1}, 
        {1, -1}
    };
    // clang-format on

    unsigned int path_length = 0;
    while (!work.empty()) {
        int n = work.size();
        for (int i = 0; i < n; i++) {
            auto [x, y] = work.front();
            work.pop();
            visited[y][x] = 1;
            dist[y][x] = path_length;
            // std::cout<<"bfs "<<x<<" : "<<y<<" : "<<path_length<<std::endl;
            for (const auto &[dx, dy] : dirs) {
                if (x + dx >= 0 && x + dx < dist[0].size() && y + dy >= 0 &&
                    y + dy < dist.size() && visited[y + dy][x + dx] == 0 &&
                    blocked[y + dy][x + dx] == 0) {
                    work.push({x + dx, y + dy});
                    // dist[y + dy][x + dx] = dist[y][x] + 1;
                    visited[y + dy][x + dx] = 1;
                }
            }
        }
        path_length++;
    }
}
void GridUtil::compute_gradient_mtx(
    const std::vector<std::vector<int>> &grid1,
    std::vector<std::vector<std::pair<float, float>>> &grid2) {
    for (int i = 1; i < grid1.size() - 1; i++) {
        for (int j = 1; j < grid1[0].size() - 1; j++) {
            float diag_1 =
                std::sqrt(abs(grid1[i - 1][j - 1] - grid1[i + 1][j + 1]));
            float diag_2 =
                std::sqrt(abs(grid1[i - 1][j + 1] - grid1[i + 1][j - 1]));
            float x_comp_1 =
                (grid1[i - 1][j - 1] > grid1[i + 1][j + 1]) ? diag_1 : -diag_1;
            float x_comp_2 =
                (grid1[i - 1][j + 1] > grid1[i + 1][j - 1]) ? -diag_2 : diag_2;
            float y_comp_1 =
                (grid1[i - 1][j - 1] > grid1[i + 1][j + 1]) ? diag_1 : -diag_1;
            float y_comp_2 =
                (grid1[i - 1][j + 1] > grid1[i + 1][j - 1]) ? diag_2 : -diag_2;
            grid2[i][j] = {
                static_cast<float>(grid1[i][j - 1] - grid1[i][j + 1]) +
                    x_comp_1 + x_comp_2,
                static_cast<float>(grid1[i - 1][j] - grid1[i + 1][j]) +
                    y_comp_1 + y_comp_2};
        }
    }
}