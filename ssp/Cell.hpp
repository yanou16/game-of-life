#pragma once

class Cell {
private:
    bool isAlive;
    bool nextState;
    bool userCreated;

public:
    Cell();
    bool getState() const;
    void setState(bool state, bool isUser = false);
    void computeNextState(int liveNeighbors);
    void updateState();
    bool isUserCreated() const;
};