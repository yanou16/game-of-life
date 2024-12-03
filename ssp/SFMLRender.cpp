#include "SFMLRender.hpp"
#include <sstream>

SFMLRender::SFMLRender(int width, int height)
    : Render(),
    window(sf::VideoMode(800, 600), "Game of Life - Press H for Help"),
    showInfo(false)
{
    window.setFramerateLimit(60);

    // Utiliser OpenSans du dossier font
    std::string fontPath = "font/Open_Sans/OpenSans-VariableFont_wdth.wght";

    if (!font.loadFromFile(fontPath)) {
        std::cout << "ERREUR: Impossible de charger la police avec le chemin relatif: " << fontPath << std::endl;
        // Essayer avec le chemin absolu
        std::string absolutePath = "C:/Users/Lenovo/source/repos/ssp/ssp/font/Open_Sans/OpenSans-VariableFont_wdth.wght";
        if (!font.loadFromFile(absolutePath)) {
            std::cout << "ERREUR: Impossible de charger la police m�me avec le chemin absolu!" << std::endl;
        }
        else {
            std::cout << "Police OpenSans charg�e avec succ�s via chemin absolu!" << std::endl;
        }
    }
    else {
        std::cout << "Police OpenSans charg�e avec succ�s!" << std::endl;
    }

    float cellWidth = static_cast<float>(800) / width;
    float cellHeight = static_cast<float>(600) / height;
    cellSize = std::min(cellWidth, cellHeight);

    cellShapes.resize(width * height);
    for (auto& shape : cellShapes) {
        shape.setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color(50, 50, 50));
    }

    initializeInfoButton();
}

void SFMLRender::initializeInfoButton() {
    // Configurer le bouton
    infoButton.setSize(sf::Vector2f(100, 30));
    infoButton.setPosition(10, 10);
    infoButton.setFillColor(sf::Color(80, 80, 200));
    infoButton.setOutlineThickness(2);
    infoButton.setOutlineColor(sf::Color::White);

    // Configurer le texte du bouton avec une taille plus grande
    infoButtonText.setFont(font);
    infoButtonText.setString("Info");
    infoButtonText.setCharacterSize(16);  // Taille r�duite
    infoButtonText.setFillColor(sf::Color::White);

    // Centrer le texte dans le bouton
    sf::FloatRect textBounds = infoButtonText.getLocalBounds();
    float xPos = infoButton.getPosition().x + (infoButton.getSize().x - textBounds.width) / 2.0f;
    float yPos = infoButton.getPosition().y + (infoButton.getSize().y - textBounds.height) / 2.0f - textBounds.top;
    infoButtonText.setPosition(xPos, yPos);

    // Configurer le texte d'information
    infoText.setFont(font);
    infoText.setCharacterSize(14);  // Taille r�duite
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(10, 50);
}


void SFMLRender::updateInfoText(const Grid& grid) {
    std::stringstream ss;

    int livingCells = grid.getLivingCellsCount();
    int userCells = grid.getUserCreatedCellsCount();


    ss << "Cellules vivantes: " << grid.getLivingCellsCount() << "\n";
    ss << "Cellules cr��es par l'utilisateur: " << grid.getUserCreatedCellsCount() << "\n";
    infoText.setString(ss.str());

    std::cout << "Mise � jour des infos - Vivantes: " << livingCells
        << ", Utilisateur: " << userCells << std::endl;

}

bool SFMLRender::isMouseOverButton(const sf::Vector2i& mousePos) const {
    return infoButton.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void SFMLRender::handleEvents(Grid* grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (!grid) return;

        // Gestion du bouton Info
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isMouseOverButton(mousePos)) {
                    showInfo = !showInfo;
                    std::cout << "Bouton Info " << (showInfo ? "activ�" : "d�sactiv�") << std::endl;
                    return;  // Pour �viter d'activer une cellule sous le bouton
                }
            }
        }

        // Gestion de la souris pour les cellules
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto gridPos = getGridCoordinates(mousePos.x, mousePos.y, *grid);

            if (gridPos.x >= 0 && gridPos.x < grid->getWidth() &&
                gridPos.y >= 0 && gridPos.y < grid->getHeight()) {
                grid->setCellState(gridPos.x, gridPos.y,
                    sf::Mouse::isButtonPressed(sf::Mouse::Left),
                    true);  // true pour indiquer que c'est cr�� par l'utilisateur
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
                    std::cout << "Grille effac�e" << std::endl;
                }
                break;

            case sf::Keyboard::R:
                if (grid) {
                    for (int y = 0; y < grid->getHeight(); y++) {
                        for (int x = 0; x < grid->getWidth(); x++) {
                            grid->setCellState(x, y, rand() % 2 == 1, false);
                        }
                    }
                    std::cout << "Remplissage al�atoire" << std::endl;
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
                    << "Clic droit - D�sactiver une cellule\n"
                    << "Espace - Pause/Reprise\n"
                    << "+/- - Ajuster la vitesse\n"
                    << "C - Effacer la grille\n"
                    << "R - Remplissage al�atoire\n"
                    << "G - Placer un planeur\n"
                    << "B - Placer un bloc\n"
                    << "L - Placer un clignotant\n"
                    << "H - Afficher l'aide\n"
                    << "�chap - Quitter\n";
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

    // Dessiner les cellules
    updateCellShapes(grid);
    for (const auto& shape : cellShapes) {
        window.draw(shape);
    }

    // Dessiner le bouton (m�me sans police)
    window.draw(infoButton);

    // Si la police est charg�e, dessiner le texte du bouton
    if (font.getInfo().family != "") {
        window.draw(infoButtonText);
    }

    // Afficher les infos seulement si le bouton est activ�
    if (showInfo) {
        // Cr�er un rectangle de fond pour le texte
        sf::RectangleShape infoBg;
        infoBg.setSize(sf::Vector2f(200, 60));
        infoBg.setPosition(10, 50);
        infoBg.setFillColor(sf::Color(0, 0, 0, 200));
        infoBg.setOutlineThickness(1);
        infoBg.setOutlineColor(sf::Color::White);
        window.draw(infoBg);

        // M�me sans police, afficher au moins les statistiques dans la console
        std::cout << "Cellules vivantes: " << grid.getLivingCellsCount()
            << ", Cr��es par l'utilisateur: " << grid.getUserCreatedCellsCount() << std::endl;
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
                        cellShapes[index].setFillColor(sf::Color::Blue);
                    }
                    else {
                        cellShapes[index].setFillColor(sf::Color::Green);
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