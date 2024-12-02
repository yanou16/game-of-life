#pragma once
#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class SFMLRender : public Render {
private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> cellShapes;
    float cellSize;
    sf::Vector2i mousePosition;

    void updateCellShapes(const Grid& grid);
    sf::Vector2i getGridCoordinates(int mouseX, int mouseY, const Grid& grid) const;
    void placeGlider(Grid& grid, int x, int y);
    void placeBlock(Grid& grid, int x, int y);
    void placeBlinker(Grid& grid, int x, int y);

public:
    SFMLRender(int width, int height);
    void render(const Grid& grid) override;
    bool isOpen() const override;
    void handleEvents(Grid* grid = nullptr) override;
};