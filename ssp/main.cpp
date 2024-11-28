#include "GameOfLife.hpp"
#include <iostream>

void displayUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <input_file> [mode] [generations] [speed]" << std::endl;
    std::cout << "Modes:" << std::endl;
    std::cout << "  1 - Console mode (saves states to files)" << std::endl;
    std::cout << "  2 - Graphical mode (SFML window)" << std::endl;
    std::cout << "generations: number of generations to simulate (default: 100, -1 for infinite in graphical mode)" << std::endl;
    std::cout << "speed: delay between generations in ms (default: 500)" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        displayUsage(argv[0]);
        return 1;
    }

    try {
        // Demander le mode si non spécifié
        int modeChoice = 1;
        if (argc < 3) {
            std::cout << "Choose mode:" << std::endl;
            std::cout << "1. Console mode (saves states to files)" << std::endl;
            std::cout << "2. Graphical mode (SFML window)" << std::endl;
            std::cout << "Enter choice (1 or 2): ";
            std::cin >> modeChoice;
        }
        else {
            modeChoice = std::stoi(argv[2]);
        }

        GameMode mode = (modeChoice == 2) ? GameMode::GRAPHICAL : GameMode::CONSOLE;

        // Nombre de générations
        int generations = 100;
        if (argc >= 4) {
            generations = std::stoi(argv[3]);
        }
        else if (mode == GameMode::CONSOLE) {
            std::cout << "Enter number of generations: ";
            std::cin >> generations;
        }

        // Vitesse de simulation
        int speed = 500;
        if (argc >= 5) {
            speed = std::stoi(argv[4]);
        }
        else if (mode == GameMode::GRAPHICAL) {
            std::cout << "Enter simulation speed (ms): ";
            std::cin >> speed;
        }

        // Créer et exécuter le jeu
        GameOfLife game(argv[1], mode);
        game.setSimulationSpeed(speed);

        if (mode == GameMode::CONSOLE) {
            std::cout << "Running console mode for " << generations << " generations..." << std::endl;
        }
        else {
            std::cout << "Running graphical mode. Close window to stop." << std::endl;
            std::cout << "Speed: " << speed << "ms between generations" << std::endl;
        }

        game.run(generations);

        if (mode == GameMode::CONSOLE) {
            std::cout << "Simulation completed. Check the output directory." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}