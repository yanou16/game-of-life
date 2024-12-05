#include "ConsoleRender.hpp"
#include "FileService.hpp"
#include <iostream>

ConsoleRender::ConsoleRender(const std::string& baseFilename)
    : outputDir(baseFilename + "_out"), iterationCount(0) {
}

void ConsoleRender::render(const Grid& grid) {
    std::cout << "\nIteration " << iterationCount << ":\n";
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            std::cout << (grid.getCellState(x, y) ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    FileService::saveGenerationState(outputDir, iterationCount, grid);
    std::cout << "Etat sauvegarde dans le fichier: iteration_" << iterationCount << ".txt" << std::endl;
    iterationCount++;
}

bool ConsoleRender::isOpen() const {
    return true;
}

void ConsoleRender::handleEvents(Grid* grid) {
    // Rien à faire pour le rendu console
}
