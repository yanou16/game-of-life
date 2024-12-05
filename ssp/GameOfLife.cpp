#include "GameOfLife.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <filesystem>

GameOfLife::GameOfLife(const std::string& filename, GameMode mode)
    : grid(20, 20),
    simulationSpeed(100),
    generationCount(0),
    maxGenerations(100)
{
    if (mode == GameMode::CONSOLE) {
        outputDir = FileService::createOutputDirectory(filename);
    }

    initializeFromFile(filename);

    if (mode == GameMode::CONSOLE) {
        renderer = std::make_unique<ConsoleRender>(filename);
    }
    else {
        renderer = std::make_unique<SFMLRender>(grid.getWidth(), grid.getHeight());
    }
    renderer->setSimulationSpeed(static_cast<float>(simulationSpeed));
}

void GameOfLife::initializeFromFile(const std::string& filename) {
    try {
        FileService::loadFromFile(filename, grid);
    }
    catch (const std::exception&) {
        initializeDefaultGrid();
    }
}

 

void GameOfLife::initializeDefaultGrid() {
    grid = Grid(20, 20);
    placeGlider(10, 10);  // Place un planeur au centre
}



void GameOfLife::placeGlider(int x, int y) {
    if (x >= 0 && x + 2 < grid.getWidth() && y >= 0 && y + 2 < grid.getHeight()) {
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x + 2, y + 1, true, true);
        grid.setCellState(x, y + 2, true, true);
        grid.setCellState(x + 1, y + 2, true, true);
        grid.setCellState(x + 2, y + 2, true, true);
    }
}

void GameOfLife::placeBlock(int x, int y) {
    if (x >= 0 && x + 1 < grid.getWidth() && y >= 0 && y + 1 < grid.getHeight()) {
        grid.setCellState(x, y, true, true);
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x, y + 1, true, true);
        grid.setCellState(x + 1, y + 1, true, true);
    }
}

void GameOfLife::placeBlinker(int x, int y) {
    if (x >= 0 && x + 2 < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
        grid.setCellState(x, y, true, true);
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x + 2, y, true, true);
    }
}

void GameOfLife::clearGrid() {
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            grid.setCellState(x, y, false, false);
        }
    }
}

void GameOfLife::randomFill() {
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            grid.setCellState(x, y, rand() % 2 == 1, false);
        }
    }
}

void GameOfLife::handleUserAction(UserAction action, int x, int y) {
    switch (action) {
    case UserAction::PLACE_GLIDER:
        placeGlider(x, y);
        break;
    case UserAction::PLACE_BLOCK:
        placeBlock(x, y);
        break;
    case UserAction::PLACE_BLINKER:
        placeBlinker(x, y);
        break;
    case UserAction::CLEAR_GRID:
        clearGrid();
        break;
    case UserAction::RANDOM_FILL:
        randomFill();
        break;
    case UserAction::TOGGLE_CELL:
        grid.setCellState(x, y, !grid.getCellState(x, y), true);
        break;
    }
}

void GameOfLife::updateSimulation() {
    if (grid.isStable() && generationCount > 0) {
        std::cout << "\n=== État stable détecté après " << generationCount << " générations ! ===\n";
        return;
    }

    grid.update();
    generationCount++;

    if (!outputDir.empty()) {
        FileService::saveGenerationState(outputDir, generationCount, grid);
    }
}

void GameOfLife::setSimulationSpeed(int speed) {
    simulationSpeed = speed;
    if (renderer) {
        renderer->setSimulationSpeed(static_cast<float>(speed));
    }
}

void GameOfLife::run() {
    if (auto* sfmlRenderer = dynamic_cast<SFMLRender*>(renderer.get())) {
        // Mode graphique
        while (sfmlRenderer->isOpen() && generationCount < maxGenerations) {
            sfmlRenderer->handleEvents(&grid);

            // Obtenir la vitesse actuelle avant de mettre à jour
            float currentSpeed = sfmlRenderer->getSimulationSpeed();

            // Mettre à jour seulement si pas en pause
            if (!sfmlRenderer->isPauseActive()) {
                // Appliquer le délai AVANT la mise à jour
                sf::sleep(sf::milliseconds(static_cast<int>(currentSpeed)));

                updateSimulation();
                if (grid.isStable() && generationCount > 0) {
                    std::cout << "Configuration stable détectée!" << std::endl;
                    break;
                }

                if (generationCount % 10 == 0) {
                    std::cout << "Generation: " << generationCount
                        << " (Vitesse: " << currentSpeed << "ms)" << std::endl;
                }
            }

            sfmlRenderer->render(grid);
        }
    }
    else {
        // Mode console
        while (renderer->isOpen() && generationCount < maxGenerations) {
            renderer->handleEvents();

            // D'abord vérifier si on est stable
            if (grid.isStable() && generationCount > 0) {
                renderer->render(grid);  // Dernier affichage
                break;                   // Sort de la boucle
            }

            renderer->render(grid);      // Affichage normal
            updateSimulation();          // Met à jour la grille

            // Utiliser la vitesse de simulation du mode console
            std::this_thread::sleep_for(std::chrono::milliseconds(simulationSpeed));
        }
    }

    std::cout << "\nSimulation terminée après " << generationCount << " générations.\n";
    if (grid.isStable()) {
        std::cout << "État final: Configuration stable\n";
    }
}
    