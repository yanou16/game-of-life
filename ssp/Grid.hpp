#pragma once
#include <vector>
#include "Cell.hpp"

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int width;
    int height;

public:
    Grid(int w, int h);
    void setCellState(int x, int y, bool state);
    bool getCellState(int x, int y) const;
    int countLiveNeighbors(int x, int y) const;
    void updateCells();
    int getWidth() const;
    int getHeight() const;
};