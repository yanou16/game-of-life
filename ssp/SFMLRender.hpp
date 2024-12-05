#pragma once
#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>

class SFMLRender : public Render {
private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> cellShapes;
    float cellSize;
    sf::Vector2i mousePosition;

    // Constantes et variables pour la vitesse de simulation
    static constexpr float MIN_SPEED = 50.0f;      // Vitesse minimale
    static constexpr float MAX_SPEED = 1000.0f;    // Vitesse maximale
    float simulationSpeed = 1000.0f;               // Vitesse initiale

    // Membres pour le bouton Info
    sf::RectangleShape infoButton;
    sf::Text infoButtonText;
    sf::Text infoText;
    sf::Font font;
    bool showInfo;
    bool isPaused;

    // Méthodes privées
    void updateCellShapes(const Grid& grid);
    sf::Vector2i getGridCoordinates(int mouseX, int mouseY, const Grid& grid) const;
    void placeGlider(Grid& grid, int x, int y);
    void placeBlock(Grid& grid, int x, int y);
    void placeBlinker(Grid& grid, int x, int y);
    void initializeInfoButton();
    void updateInfoText(const Grid& grid);
    bool isMouseOverButton(const sf::Vector2i& mousePos) const;

public:
    SFMLRender(int width, int height);
    void render(const Grid& grid) override;
    bool isOpen() const override;
    void handleEvents(Grid* grid = nullptr) override;
    bool isPauseActive() const;
    float getSimulationSpeed() const;
};