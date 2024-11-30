#include "SFMLRender.hpp"

SFMLRender::SFMLRender(int width, int height)
    : Render(),  // Appel du constructeur de la classe de base
    window(sf::VideoMode(800, 600), "Game of Life - Press H for Help")
{
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

void SFMLRender::handleEvents(Grid* grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (!grid) return;

        // Gestion de la souris
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, *grid);

            if (gridPos.x >= 0 && gridPos.x < grid->getWidth() &&
                gridPos.y >= 0 && gridPos.y < grid->getHeight()) {
                grid->setCellState(gridPos.x, gridPos.y,
                    sf::Mouse::isButtonPressed(sf::Mouse::Left),
                    true);  // true pour indiquer que c'est créé par l'utilisateur
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Space:
                isPaused = !isPaused;
                std::cout << (isPaused ? "Pause" : "Reprise") << std::endl;
                break;

            case sf::Keyboard::Add:
            case sf::Keyboard::Equal:
                setSimulationSpeed(std::max(50.0f, getSimulationSpeed() - 50.0f));
                std::cout << "Vitesse: " << getSimulationSpeed() << "ms" << std::endl;
                break;

            case sf::Keyboard::Subtract:
            case sf::Keyboard::Dash:
                setSimulationSpeed(std::min(1000.0f, getSimulationSpeed() + 50.0f));
                std::cout << "Vitesse: " << getSimulationSpeed() << "ms" << std::endl;
                break;

            case sf::Keyboard::C:
                if (grid) {
                    for (int y = 0; y < grid->getHeight(); y++) {
                        for (int x = 0; x < grid->getWidth(); x++) {
                            grid->setCellState(x, y, false, false);
                        }
                    }
                    std::cout << "Grille effacée" << std::endl;
                }
                break;

            case sf::Keyboard::R:
                if (grid) {
                    for (int y = 0; y < grid->getHeight(); y++) {
                        for (int x = 0; x < grid->getWidth(); x++) {
                            grid->setCellState(x, y, rand() % 2 == 1, false);  // false car généré automatiquement
                        }
                    }
                    std::cout << "Remplissage aléatoire" << std::endl;
                }
                break;

            case sf::Keyboard::G:
                if (grid) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, *grid);
                    placeGlider(*grid, gridPos.x, gridPos.y);
                }
                break;

            case sf::Keyboard::B:
                if (grid) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, *grid);
                    placeBlock(*grid, gridPos.x, gridPos.y);
                }
                break;

            case sf::Keyboard::L:
                if (grid) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, *grid);
                    placeBlinker(*grid, gridPos.x, gridPos.y);
                }
                break;

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
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x + 2, y + 1, true, true);
        grid.setCellState(x, y + 2, true, true);
        grid.setCellState(x + 1, y + 2, true, true);
        grid.setCellState(x + 2, y + 2, true, true);
    }
}

void SFMLRender::placeBlock(Grid& grid, int x, int y) {
    if (x >= 0 && x + 1 < grid.getWidth() && y >= 0 && y + 1 < grid.getHeight()) {
        grid.setCellState(x, y, true, true);
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x, y + 1, true, true);
        grid.setCellState(x + 1, y + 1, true, true);
    }
}

void SFMLRender::placeBlinker(Grid& grid, int x, int y) {
    if (x >= 0 && x + 2 < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
        grid.setCellState(x, y, true, true);
        grid.setCellState(x + 1, y, true, true);
        grid.setCellState(x + 2, y, true, true);
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
                    if (grid.getCellUserCreated(x, y)) {
                        cellShapes[index].setFillColor(sf::Color::Blue);  // Cellules utilisateur
                    }
                    else {
                        cellShapes[index].setFillColor(sf::Color::Green); // Cellules automatiques
                    }
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