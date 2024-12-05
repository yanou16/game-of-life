#pragma once
#include "Grid.hpp"
#include <string>

class FileService {
public:
    static void saveToFile(const std::string& filename, const Grid& grid);
    static void loadFromFile(const std::string& filename, Grid& grid);
    static void saveGenerationState(const std::string& outputDir, int generation, const Grid& grid);
    static std::string createOutputDirectory(const std::string& baseFilename);

private:
    static void ensureDirectoryExists(const std::string& path);
};
