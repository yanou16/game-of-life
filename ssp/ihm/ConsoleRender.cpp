#include "ConsoleRender.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

ConsoleRender::ConsoleRender(const std::string& baseFilename)
    : outputDir(baseFilename + "_out"), iterationCount(0) {
    std::filesystem::create_directory(outputDir);
}

void ConsoleRender::render(const Grid& grid) {
    // Afficher dans le terminal
    std::cout << "\nIteration " << iterationCount << ":\n";
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            std::cout << (grid.getCellState(x, y) ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Sauvegarder dans le fichier
    saveToFile(grid);
    std::cout << "Etat sauvegarde dans le fichier: iteration_" << iterationCount << ".txt" << std::endl;
    iterationCount++;
}

void ConsoleRender::saveToFile(const Grid& grid) {
    std::string filename = outputDir + "/iteration_" + std::to_string(iterationCount) + ".txt";
    std::ofstream file(filename);

    file << grid.getHeight() << " " << grid.getWidth() << std::endl;
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            file << (grid.getCellState(x, y) ? "1" : "0");
            if (x < grid.getWidth() - 1) file << " ";
        }
        file << std::endl;
    }
}

bool ConsoleRender::isOpen() const {
    return true;
}

void ConsoleRender::handleEvents(Grid* grid) {
    // Rien à faire pour le rendu console
}
