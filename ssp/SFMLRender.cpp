#include "SFMLRender.hpp"

 SFMLRender::SFMLRender(int width, int height)
    : window(sf::VideoMode(800, 600), "Game of Life - Press H for Help"),
    isPaused(false),
    simulationSpeed(100.0f) {  // Valeur par défaut qui sera mise à jour
    window.setFramerateLimit(60);

    float cellWidth = static_cast<float>(800) / width;
    float cellHeight = static_cast<float>(600) / height;
    cellSize = std::min(cellWidth, cellHeight);

    cellShapes.resize(width * height);
    for (auto& shape : cellShapes) {
        shape.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color(50, 50, 50));
    }
}


void SFMLRender::setSimulationSpeed(float speed) {
    simulationSpeed = speed;
}

void SFMLRender::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

// Dans SFMLRender.cpp, modifiez handleEvents :
void SFMLRender::handleEvents(Grid& grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Gestion de la souris pour dessiner/effacer des cellules
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, grid);

            if (gridPos.x >= 0 && gridPos.x < grid.getWidth() &&
                gridPos.y >= 0 && gridPos.y < grid.getHeight()) {
                // Clic gauche pour activer, droit pour désactiver
                grid.setCellState(gridPos.x, gridPos.y,
                    sf::Mouse::isButtonPressed(sf::Mouse::Left));
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            auto gridPos = getGridCoordinates(mousePosition.x, mousePosition.y, grid);

            switch (event.key.code) {
            case sf::Keyboard::Space:  // Pause/Reprise
                isPaused = !isPaused;
                std::cout << (isPaused ? "Pause" : "Reprise") << std::endl;
                break;

            case sf::Keyboard::Add:    // Accélérer
            case sf::Keyboard::Equal:  // Touche + sur les claviers US
                simulationSpeed = std::max(50.0f, simulationSpeed - 50.0f);
                std::cout << "Vitesse: " << simulationSpeed << "ms" << std::endl;
                break;

            case sf::Keyboard::Subtract: // Ralentir
            case sf::Keyboard::Dash:     // Touche - sur les claviers US
                simulationSpeed = std::min(1000.0f, simulationSpeed + 50.0f);
                std::cout << "Vitesse: " << simulationSpeed << "ms" << std::endl;
                break;

            case sf::Keyboard::C:  // Effacer la grille
                for (int y = 0; y < grid.getHeight(); y++) {
                    for (int x = 0; x < grid.getWidth(); x++) {
                        grid.setCellState(x, y, false);
                    }
                }
                std::cout << "Grille effacée" << std::endl;
                break;

            case sf::Keyboard::R:  // Remplissage aléatoire
                for (int y = 0; y < grid.getHeight(); y++) {
                    for (int x = 0; x < grid.getWidth(); x++) {
                        grid.setCellState(x, y, rand() % 2 == 1);
                    }
                }
                std::cout << "Remplissage aléatoire" << std::endl;
                break;

                // ... autres touches existantes (G, B, L, etc.) ...

            case sf::Keyboard::H:
                std::cout << "\nControls:\n"
                    << "Clic gauche - Activer une cellule\n"
                    << "Clic droit - Désactiver une cellule\n"
                    << "Espace - Pause/Reprise\n"
                    << "+/- - Ajuster la vitesse\n"
                    << "C - Effacer la grille\n"
                    << "R - Remplissage aléatoire\n"
                    << "G - Placer un planeur\n"
                    << "B - Placer un bloc\n"
                    << "L - Placer un clignotant\n"
                    << "H - Afficher l'aide\n"
                    << "Échap - Quitter\n";
                break;
            }
        }
    }
}

void SFMLRender::placeGlider(Grid& grid, int x, int y) {
    if (x >= 0 && x + 2 < grid.getWidth() && y >= 0 && y + 2 < grid.getHeight()) {
        grid.setCellState(x + 1, y, true);
        grid.setCellState(x + 2, y + 1, true);
        grid.setCellState(x, y + 2, true);
        grid.setCellState(x + 1, y + 2, true);
        grid.setCellState(x + 2, y + 2, true);
    }
}

void SFMLRender::placeBlock(Grid& grid, int x, int y) {
    if (x >= 0 && x + 1 < grid.getWidth() && y >= 0 && y + 1 < grid.getHeight()) {
        grid.setCellState(x, y, true);
        grid.setCellState(x + 1, y, true);
        grid.setCellState(x, y + 1, true);
        grid.setCellState(x + 1, y + 1, true);
    }
}

void SFMLRender::placeBlinker(Grid& grid, int x, int y) {
    if (x >= 0 && x + 2 < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
        grid.setCellState(x, y, true);
        grid.setCellState(x + 1, y, true);
        grid.setCellState(x + 2, y, true);
    }
}

sf::Vector2i SFMLRender::getGridCoordinates(int mouseX, int mouseY, const Grid& grid) const {
    float offsetX = (800 - (grid.getWidth() * cellSize)) / 2;
    float offsetY = (600 - (grid.getHeight() * cellSize)) / 2;

    int gridX = static_cast<int>((mouseX - offsetX) / cellSize);
    int gridY = static_cast<int>((mouseY - offsetY) / cellSize);

    return sf::Vector2i(gridX, gridY);
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
    float offsetX = (800 - (grid.getWidth() * cellSize)) / 2;
    float offsetY = (600 - (grid.getHeight() * cellSize)) / 2;

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            int index = y * grid.getWidth() + x;
            if (index < cellShapes.size()) {
                cellShapes[index].setPosition(
                    offsetX + x * cellSize + 1,
                    offsetY + y * cellSize + 1
                );

                if (grid.getCellState(x, y)) {
                    cellShapes[index].setFillColor(sf::Color::Green);
                }
                else {
                    cellShapes[index].setFillColor(sf::Color::Black);
                }
            }
        }
    }
}

bool SFMLRender::isOpen() const {
    return window.isOpen();
}