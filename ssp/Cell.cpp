#include "Cell.hpp"

Cell::Cell() : isAlive(false), nextState(false) {}

bool Cell::getState() const {
    return isAlive;
}

void Cell::setState(bool state) {
    isAlive = state;
    nextState = state;
}

void Cell::computeNextState(int liveNeighbors) {
    if (isAlive) {
        nextState = (liveNeighbors == 2 || liveNeighbors == 3);
    }
    else {
        nextState = (liveNeighbors == 3);
    }
}

void Cell::updateState() {
    isAlive = nextState;
}