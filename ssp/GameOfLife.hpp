#pragma once
#include "Grid.hpp"
#include "Render.hpp"
#include <memory>
#include <vector>
#include <string>

enum class GameMode {
    CONSOLE,
    GRAPHICAL
};

class GameOfLife {
private:
    Grid grid;
    std::unique_ptr<Render> renderer;
    int simulationSpeed;  // en millisecondes

public:
    GameOfLife(const std::string& filename, GameMode mode);
    void run(int maxGenerations = 100);
    void setSimulationSpeed(int speed_ms);  // Déclaration seulement, pas d'implémentation ici

private:
    void loadFromFile(const std::string& filename);
};