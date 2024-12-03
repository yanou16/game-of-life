#pragma once
#include <vector>
#include "Cell.hpp"



class Grid {
private:

    
    
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<Cell>> previousState;
    int width;
    int height;
    


public:
    Grid(int height, int width);
    void update();
    bool getCellState(int x, int y) const;
    void setCellState(int x, int y, bool state, bool isUser = false);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool isStable() const;
    bool getCellUserCreated(int x, int y) const;  // Juste la déclaration, sans implémentation
    int getLivingCellsCount() const;
    int getUserCreatedCellsCount() const;
private:
    int countNeighbors(int x, int y) const;
};