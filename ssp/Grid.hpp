#pragma once
#include <vector>

class Grid {
private:
    std::vector<std::vector<bool>> cells;
    std::vector<std::vector<bool>> previousState;
    int width;
    int height;

public:
    Grid(int height, int width);
    void update();
    bool getCellState(int x, int y) const;
    void setCellState(int x, int y, bool state);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool isStable() const;
private:
    int countNeighbors(int x, int y) const;
};