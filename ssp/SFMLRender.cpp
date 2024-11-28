#include "SFMLRender.hpp"

SFMLRender::SFMLRender(int width, int height) : cellSize(20.0f) {
    window.create(sf::VideoMode(width * cellSize, height * cellSize), "Game of Life");
    window.setFramerateLimit(10);
}

void SFMLRender::render(const Grid& grid) {
    window.clear(sf::Color::Black);
    updateCellShapes(grid);
    for (const auto& shape : cellShapes) {
        window.draw(shape);
    }
    window.display();
}

void SFMLRender::updateCellShapes(const Grid& grid) {
    cellShapes.clear();
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            if (grid.getCellState(x, y)) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::White);
                cellShapes.push_back(cell);
            }
        }
    }
}

bool SFMLRender::isOpen() const {
    return window.isOpen();
}

void SFMLRender::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}