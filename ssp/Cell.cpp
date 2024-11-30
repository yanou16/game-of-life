#include "Cell.hpp"

Cell::Cell() : isAlive(false), nextState(false), userCreated(false) {
}

bool Cell::getState() const {
    return isAlive;
}

void Cell::setState(bool state, bool isUser) {
    isAlive = state;
    nextState = state;
    userCreated = isUser;
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

bool Cell::isUserCreated() const {
    return userCreated;
}