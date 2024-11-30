#include "GameOfLife.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdexcept>

GameOfLife::GameOfLife(const std::string& filename, GameMode mode)
    : grid(20, 20), simulationSpeed(100) {  // Grille par défaut 20x20

    std::ifstream file(filename);
    if (!file.is_open()) {
        // Créer un planeur au centre de la grille
        int centerX = 10;
        int centerY = 10;

        // Planeur
        grid.setCellState(centerX - 1, centerY, true);
        grid.setCellState(centerX, centerY + 1, true);
        grid.setCellState(centerX - 2, centerY + 2, true);
        grid.setCellState(centerX - 1, centerY + 2, true);
        grid.setCellState(centerX, centerY + 2, true);
    }
    else {
        int height, width;
        file >> height >> width;

        // Limiter la taille de la grille à des valeurs raisonnables
        height = std::min(std::max(height, 5), 50);  // Entre 10 et 50
        width = std::min(std::max(width, 5), 50);    // Entre 10 et 50

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

    if (mode == GameMode::CONSOLE) {
        renderer = std::make_unique<ConsoleRender>(filename);
    }
    else {
        renderer = std::make_unique<SFMLRender>(grid.getWidth(), grid.getHeight());
    }
    renderer->setSimulationSpeed(static_cast<float>(simulationSpeed));
}

void GameOfLife::run() {
    int generationCount = 0;

    if (auto* sfmlRenderer = dynamic_cast<SFMLRender*>(renderer.get())) {
        while (sfmlRenderer->isOpen() && generationCount < maxGenerations) {
            sfmlRenderer->handleEvents(&grid);  // Nouvelle version qui prend grid en paramètre
            sfmlRenderer->render(grid);

            // Mettre à jour seulement si pas en pause
            if (!sfmlRenderer->isPauseActive()) {
                // Vérifier si l'état est stable
                if (grid.isStable() && generationCount > 0) {
                    std::cout << "\n=== État stable détecté après " << generationCount << " générations ! ===\n";
                    break;
                }

                grid.update();
                generationCount++;

                if (generationCount % 10 == 0) {
                    std::cout << "Generation: " << generationCount << std::endl;
                }

                sf::sleep(sf::milliseconds(static_cast<int>(sfmlRenderer->getSimulationSpeed())));
            }
        }
    }
    else {
        // Mode console (inchangé)
        while (renderer->isOpen() && generationCount < maxGenerations) {
            renderer->handleEvents();

            if (grid.isStable() && generationCount > 0) {
                std::cout << "\n=== État stable détecté après " << generationCount << " générations ! ===\n";
                break;
            }

            grid.update();
            renderer->render(grid);

            generationCount++;
            if (generationCount % 10 == 0) {
                std::cout << "Generation: " << generationCount << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(simulationSpeed));
        }
    }

    std::cout << "\nSimulation terminée après " << generationCount << " générations.\n";
}

void GameOfLife::setSimulationSpeed(int speed) {
    simulationSpeed = speed;
    if (renderer) {
        renderer->setSimulationSpeed(static_cast<float>(speed));
    }
}