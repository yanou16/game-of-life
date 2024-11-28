#include "Grid.hpp"

Grid::Grid(int height, int width)
    : height(height), width(width) {
    cells.resize(height, std::vector<bool>(width, false));
    previousState.resize(height, std::vector<bool>(width, false));  // Pour isStable()
}

bool Grid::getCellState(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return cells[y][x];
}

void Grid::setCellState(int x, int y, bool state) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    cells[y][x] = state;
}

int Grid::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int newX = x + dx;
            int newY = y + dy;

            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                if (cells[newY][newX]) count++;
            }
        }
    }
    return count;
}

void Grid::update() {
    // Sauvegarder l'état actuel avant la mise à jour
    previousState = cells;

    auto newCells = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int neighbors = countNeighbors(x, y);
            bool currentState = cells[y][x];

            if (currentState) {
                newCells[y][x] = (neighbors == 2 || neighbors == 3);
            }
            else {
                newCells[y][x] = (neighbors == 3);
            }
        }
    }

    cells = std::move(newCells);
}

bool Grid::isStable() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[y][x] != previousState[y][x]) {
                return false;
            }
        }
    }
    return true;
}