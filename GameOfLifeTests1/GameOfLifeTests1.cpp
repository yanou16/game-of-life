#include "pch.h"
#include "CppUnitTest.h"
#include "../ssp/Grid.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameOfLifeTests
{
    TEST_CLASS(GridTests)
    {
    public:
        TEST_METHOD(TestGridValidityAtIterationT)
        {
            // Créer une grille 5x10
            Grid grid(10, 5);  // largeur=10, hauteur=5

            // Configuration initiale (t=0)
            // Essayons les deux ordres possibles des coordonnées
            Logger::WriteMessage("Configuration de l'état initial...");

            // Configuration du blinker
            grid.setCellState(2, 4, true);  // y=2, x=4
            grid.setCellState(2, 5, true);  // y=2, x=5
            grid.setCellState(2, 6, true);  // y=2, x=6

            // Vérification immédiate après configuration
            Logger::WriteMessage("Vérification de l'état initial...");

            // Vérifier l'état initial
            bool state1 = grid.getCellState(2, 4);
            bool state2 = grid.getCellState(2, 5);
            bool state3 = grid.getCellState(2, 6);

            std::string message = "États initiaux: (" +
                std::to_string(state1) + "," +
                std::to_string(state2) + "," +
                std::to_string(state3) + ")";
            Logger::WriteMessage(message.c_str());

            // Vérifications avec messages détaillés
            Assert::IsTrue(state1, L"t=0: Cellule (2,4) devrait être vivante");
            Assert::IsTrue(state2, L"t=0: Cellule (2,5) devrait être vivante");
            Assert::IsTrue(state3, L"t=0: Cellule (2,6) devrait être vivante");

            // Si ces tests passent, on continue avec l'update
            if (state1 && state2 && state3) {
                Logger::WriteMessage("État initial correct, exécution de update()...");
                grid.update();

                // Vérifier l'état après update
                Assert::IsTrue(grid.getCellState(1, 5), L"t=1: Cellule (1,5) devrait être vivante");
                Assert::IsTrue(grid.getCellState(2, 5), L"t=1: Cellule (2,5) devrait être vivante");
                Assert::IsTrue(grid.getCellState(3, 5), L"t=1: Cellule (3,5) devrait être vivante");
            }
        }
    };
}
