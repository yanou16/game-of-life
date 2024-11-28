#pragma once
#include "Grid.hpp"
#include "Render.hpp"
#include "ConsoleRender.hpp"
#include "SFMLRender.hpp"
#include <memory>
#include <string>

enum class GameMode {
    CONSOLE,
    GRAPHICAL
};

class GameOfLife {
private:
    Grid grid;
    std::unique_ptr<Render> renderer;
    int simulationSpeed;
    int maxGenerations;  // Ajout de maxGenerations comme membre

public:
    GameOfLife(const std::string& filename, GameMode mode);
    void run();
    void setSimulationSpeed(int speed) { simulationSpeed = speed; }
    void setMaxGenerations(int gens) { maxGenerations = gens; }
};