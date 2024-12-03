#include "GameOfLife.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <filesystem>

GameOfLife::GameOfLife(const std::string& filename, GameMode mode)
    : grid(20, 20),  // Initialisation explicite avec une taille par défaut
    simulationSpeed(100),
    generationCount(0),
    maxGenerations(100) {

    if (mode == GameMode::CONSOLE) {
        outputDir = filename + "_out";
        std::filesystem::create_directory(outputDir);
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
    std::ifstream file(filename);
    if (!file.is_open()) {
        initializeDefaultGrid();
        return;
    }

    int height, width;
    file >> height >> width;
    height = std::min(std::max(height, 5), 50);
    width = std::min(std::max(width, 5), 50);

    grid = Grid(height, width);

    int state;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (file >> state) {
                grid.setCellState(x, y, state == 1);
            }
        }
    }
}

void GameOfLife::initializeDefaultGrid() {
    grid = Grid(20, 20);
    placeGlider(10, 10);  // Place un planeur au centre
}

void GameOfLife::saveToFile(int generation) {
    if (outputDir.empty()) return;

    std::string filename = outputDir + "/generation_" + std::to_string(generation) + ".txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier pour la sauvegarde: " << filename << std::endl;
        return;
    }

    file << grid.getHeight() << " " << grid.getWidth() << std::endl;

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            file << (grid.getCellState(x, y) ? "1" : "0");
            if (x < grid.getWidth() - 1) file << " ";
        }
        file << std::endl;
    }
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
        saveToFile(generationCount);
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
        while (sfmlRenderer->isOpen() && generationCount < maxGenerations) {
            sfmlRenderer->handleEvents(&grid);
            sfmlRenderer->render(grid);

            // Mettre à jour seulement si pas en pause
            if (!sfmlRenderer->isPauseActive()) {
                updateSimulation();
                if (grid.isStable() && generationCount > 0) {
                    break;
                }

                if (generationCount % 10 == 0) {
                    std::cout << "Generation: " << generationCount << std::endl;
                }

                sf::sleep(sf::milliseconds(static_cast<int>(sfmlRenderer->getSimulationSpeed())));
            }
        }
    }
    else {
        // Mode console
        while (renderer->isOpen() && generationCount < maxGenerations) {
            renderer->handleEvents();
            renderer->render(grid);

            updateSimulation();
            if (grid.isStable() && generationCount > 0) {
                break;
            }

            if (generationCount % 10 == 0) {
                std::cout << "Generation: " << generationCount << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(simulationSpeed));
        }
    }

    std::cout << "\nSimulation terminée après " << generationCount << " générations.\n";
}