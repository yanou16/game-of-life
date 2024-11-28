#pragma once

class Cell {
private:
    bool isAlive;
    bool nextState;

public:
    Cell();
    bool getState() const;
    void setState(bool state);
    void computeNextState(int liveNeighbors);
    void updateState();
};