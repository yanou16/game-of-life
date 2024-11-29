#pragma once
#include "Grid.hpp"

class Render {
protected:
    float simulationSpeed;
    bool isPaused;

public:
    Render() : simulationSpeed(100.0f), isPaused(false) {}
    virtual ~Render() = default;

    virtual void render(const Grid& grid) = 0;
    virtual bool isOpen() const = 0;
    virtual void handleEvents(Grid* grid = nullptr) = 0;

    virtual void setSimulationSpeed(float speed) { simulationSpeed = speed; }
    virtual float getSimulationSpeed() const { return simulationSpeed; }
    virtual bool isPauseActive() const { return isPaused; }
};