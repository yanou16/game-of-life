#pragma once
#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class SFMLRender : public Render {
private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> cellShapes;
    float cellSize;

public:
    SFMLRender(int width, int height);
    void render(const Grid& grid) override;
    bool isOpen() const override;
    void handleEvents() override;
private:
    void updateCellShapes(const Grid& grid);
};