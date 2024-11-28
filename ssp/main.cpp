#include "GameOfLife.hpp"
#include <iostream>

void displayUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <input_file> [mode] [generations] [speed]" << std::endl;
    std::cout << "Modes:" << std::endl;
    std::cout << "  1 - Console mode (saves states to files)" << std::endl;
    std::cout << "  2 - Graphical mode (SFML window)" << std::endl;
    std::cout << "generations: number of generations to simulate (default: 100, -1 for infinite in graphical mode)" << std::endl;
    std::cout << "speed: delay between generations in ms (50-1000, default: 500)" << std::endl;
}

void displayGraphicalControls() {
    std::cout << "\nGraphical Mode Controls:" << std::endl;
    std::cout << "Left Click  - Add cell" << std::endl;
    std::cout << "Right Click - Remove cell" << std::endl;
    std::cout << "Space      - Pause/Resume simulation" << std::endl;
    std::cout << "+/-        - Adjust simulation speed" << std::endl;
    std::cout << "G          - Place Glider pattern" << std::endl;
    std::cout << "B          - Place Block pattern" << std::endl;
    std::cout << "L          - Place Blinker pattern" << std::endl;
    std::cout << "C          - Clear grid" << std::endl;
    std::cout << "R          - Random fill" << std::endl;
    std::cout << "H          - Show this help" << std::endl;
    std::cout << "Escape     - Exit" << std::endl;
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
            while (modeChoice != 1 && modeChoice != 2) {
                std::cout << "Invalid choice. Please enter 1 or 2: ";
                std::cin >> modeChoice;
            }
        }
        else {
            modeChoice = std::stoi(argv[2]);
            if (modeChoice != 1 && modeChoice != 2) {
                std::cout << "Invalid mode. Using console mode (1)." << std::endl;
                modeChoice = 1;
            }
        }

        GameMode mode = (modeChoice == 2) ? GameMode::GRAPHICAL : GameMode::CONSOLE;

        // Nombre de générations
        int generations = 100;
        if (argc >= 4) {
            generations = std::stoi(argv[3]);
        }
        else if (mode == GameMode::CONSOLE) {
            std::cout << "Enter number of generations (1-1000, -1 for infinite in graphical mode): ";
            std::cin >> generations;
            if (generations < 1 && generations != -1) generations = 100;
            if (generations > 1000) generations = 1000;
        }

        // Vitesse de simulation
        int speed = 500;
        if (argc >= 5) {
            speed = std::stoi(argv[4]);
        }
        else {
            do {
                std::cout << "Enter simulation speed (50-1000 ms): ";
                std::cin >> speed;
                if (speed < 50) {
                    std::cout << "Speed too fast. Minimum is 50ms." << std::endl;
                }
                if (speed > 1000) {
                    std::cout << "Speed too slow. Maximum is 1000ms." << std::endl;
                }
            } while (speed < 50 || speed > 1000);
        }

        // Ajuster la vitesse dans les limites
        speed = std::max(50, std::min(1000, speed));

        // Créer et exécuter le jeu
        GameOfLife game(argv[1], mode);
        game.setSimulationSpeed(speed);
        game.setMaxGenerations(generations);

        if (mode == GameMode::CONSOLE) {
            std::cout << "\nRunning console mode for " << generations << " generations..." << std::endl;
            std::cout << "Speed: " << speed << "ms between generations" << std::endl;
        }
        else {
            std::cout << "\nRunning graphical mode." << std::endl;
            std::cout << "Initial speed: " << speed << "ms between generations" << std::endl;
            displayGraphicalControls();
        }

        game.run();

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