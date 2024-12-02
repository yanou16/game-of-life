#pragma once
#include "Render.hpp"
#include <string>

class ConsoleRender : public Render {
private:
    std::string outputDir;
    int iterationCount;

public:
    ConsoleRender(const std::string& baseFilename);
    void render(const Grid& grid) override;
    bool isOpen() const override;
    void handleEvents(Grid* grid = nullptr) override;

private:
    void saveToFile(const Grid& grid);
};