
#include "FileService.hpp"
#include <fstream>
#include <filesystem>
#include <stdexcept>


void FileService::saveToFile(const std::string& filename, const Grid& grid) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour la sauvegarde: " + filename);
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

void FileService::loadFromFile(const std::string& filename, Grid& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier: " + filename);
    }

    int height, width;
    file >> height >> width;

    // Pas besoin de min/max car on veut les dimensions exactes
    grid = Grid(height, width);  // Correction ici : height en premier

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int state;  // Changé de char à int
            file >> state;  // Lit directement le nombre
            grid.setCellState(x, y, state == 1);
        }
    }
}

void FileService::saveGenerationState(const std::string& outputDir, int generation, const Grid& grid) {
    if (outputDir.empty()) return;
    
    ensureDirectoryExists(outputDir);
    std::string filename = outputDir + "/generation_" + std::to_string(generation) + ".txt";
    saveToFile(filename, grid);
}

std::string FileService::createOutputDirectory(const std::string& baseFilename) {
    std::string outputDir = baseFilename + "_out";
    ensureDirectoryExists(outputDir);
    return outputDir;
}

void FileService::ensureDirectoryExists(const std::string& path) {
    std::filesystem::create_directories(path);
}
