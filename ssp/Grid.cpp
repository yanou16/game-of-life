#include "Grid.hpp"

Grid::Grid(int w, int h) : width(w), height(h) {
    cells.resize(height, std::vector<Cell>(width));
}

void Grid::setCellState(int x, int y, bool state) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].setState(state);
    }
}

bool Grid::getCellState(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return cells[y][x].getState();
    }
    return false;
}

int Grid::countLiveNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            if (getCellState(x + dx, y + dy)) count++;
        }
    }
    return count;
}

void Grid::updateCells() {
    // Compute next state for all cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int neighbors = countLiveNeighbors(x, y);
            cells[y][x].computeNextState(neighbors);
        }
    }
    // Update all cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[y][x].updateState();
        }
    }
}

int Grid::getWidth() const { return width; }
int Grid::getHeight() const { return height; }