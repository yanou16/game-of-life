#include "GameOfLife.hpp"
#include "ConsoleRender.hpp"
#include "SFMLRender.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>

GameOfLife::GameOfLife(const std::string& filename, GameMode mode)
    : grid(1, 1), simulationSpeed(500) {
    loadFromFile(filename);

    switch (mode) {
    case GameMode::CONSOLE:
        renderer = std::make_unique<ConsoleRender>(filename);
        std::cout << "Console mode initialized. Output directory: " << filename << "_out" << std::endl;
        break;
    case GameMode::GRAPHICAL:
        renderer = std::make_unique<SFMLRender>(grid.getWidth(), grid.getHeight());
        std::cout << "Graphical mode initialized." << std::endl;
        break;
    }
}

void GameOfLife::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    int width, height;
    file >> height >> width;

    if (file.fail() || width <= 0 || height <= 0) {
        throw std::runtime_error("Invalid grid dimensions in file: " + filename);
    }

    grid = Grid(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int state;
            file >> state;
            if (file.fail() || (state != 0 && state != 1)) {
                throw std::runtime_error("Invalid cell state in file: " + filename);
            }
            grid.setCellState(x, y, state == 1);
        }
    }

    std::cout << "Loaded grid: " << width << "x" << height << std::endl;
}

void GameOfLife::run(int maxGenerations) {
    int generation = 0;
    bool running = true;

    std::cout << "Starting simulation..." << std::endl;
    std::cout << "Press Ctrl+C to stop (console mode) or close window (graphical mode)" << std::endl;

    try {
        while (running && (maxGenerations == -1 || generation < maxGenerations)) {
            // Gestion des événements
            renderer->handleEvents();
            if (!renderer->isOpen()) {
                std::cout << "Renderer closed. Stopping simulation." << std::endl;
                break;
            }

            // Mise à jour de la grille
            grid.updateCells();

            // Rendu
            renderer->render(grid);

            // Compteur de générations
            generation++;
            if (generation % 10 == 0) {
                std::cout << "Generation: " << generation << std::endl;
            }

            // Pause entre les générations
            std::this_thread::sleep_for(std::chrono::milliseconds(simulationSpeed));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error during simulation: " << e.what() << std::endl;
        throw;
    }

    if (maxGenerations != -1 && generation >= maxGenerations) {
        std::cout << "Reached maximum number of generations (" << maxGenerations << ")" << std::endl;
    }

    std::cout << "Simulation ended after " << generation << " generations" << std::endl;
}

void GameOfLife::setSimulationSpeed(int speed_ms) {
    if (speed_ms < 0) {
        throw std::invalid_argument("Simulation speed cannot be negative");
    }
    simulationSpeed = speed_ms;
    std::cout << "Simulation speed set to " << speed_ms << "ms" << std::endl;
}