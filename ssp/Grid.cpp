#include "Grid.hpp"

Grid::Grid(int height, int width)
    : height(height), width(width) {
    cells.resize(height, std::vector<Cell>(width, Cell()));
    previousState.resize(height, std::vector<Cell>(width, Cell()));
}

bool Grid::getCellState(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return cells[y][x].getState();
}

void Grid::setCellState(int x, int y, bool state, bool isUser) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    cells[y][x].setState(state, isUser);
}

int Grid::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int newX = x + dx;
            int newY = y + dy;

            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                if (cells[newY][newX].getState()) count++;
            }
        }
    }
    return count;
}

void Grid::update() {
    previousState = cells;

    // Calculer les prochains états
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int neighbors = countNeighbors(x, y);
            cells[y][x].computeNextState(neighbors);
        }
    }

    // Mettre à jour tous les états
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[y][x].updateState();
        }
    }
}

bool Grid::isStable() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[y][x].getState() != previousState[y][x].getState()) {
                return false;
            }
        }
    }
    return true;
}

bool Grid::getCellUserCreated(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return cells[y][x].isUserCreated();
}


int Grid::getLivingCellsCount() const {
    int count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (getCellState(x, y)) count++;
        }
    }
    return count;
}

int Grid::getUserCreatedCellsCount() const {
    int count = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (getCellState(x, y) && getCellUserCreated(x, y)) count++;
        }
    }
    return count;
}