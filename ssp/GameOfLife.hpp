#pragma once
#include "Grid.hpp"
#include "Render.hpp"
#include "ConsoleRender.hpp"
#include "SFMLRender.hpp"
#include <memory>
#include <string>
#include "FileService.hpp"
enum class GameMode {
    CONSOLE,
    GRAPHICAL
};

// Définir UserAction avant la classe GameOfLife
enum class UserAction {
    PLACE_GLIDER,
    PLACE_BLOCK,
    PLACE_BLINKER,
    CLEAR_GRID,
    RANDOM_FILL,
    TOGGLE_CELL
};

class GameOfLife {
private:
    Grid grid;
    std::unique_ptr<Render> renderer;
    int simulationSpeed;
    int maxGenerations;
    std::string outputDir;
    int generationCount;
    

    // Méthodes privées pour la logique métier
    void initializeFromFile(const std::string& filename);
    void initializeDefaultGrid();
    
    void placeGlider(int x, int y);
    void placeBlock(int x, int y);
    void placeBlinker(int x, int y);
    void clearGrid();
    void randomFill();
    void updateSimulation();

public:
    GameOfLife(const std::string& filename, GameMode mode);
    void run();
    void setSimulationSpeed(int speed);
    void setMaxGenerations(int gens) { maxGenerations = gens; }

    // Méthode pour gérer les actions utilisateur
    void handleUserAction(UserAction action, int x, int y);
};