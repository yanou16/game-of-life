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
            // Cr�er une grille 5x10
            Grid grid(10, 5);  // largeur=10, hauteur=5

            // Configuration initiale (t=0)
            // Essayons les deux ordres possibles des coordonn�es
            Logger::WriteMessage("Configuration de l'�tat initial...");

            // Configuration du blinker
            grid.setCellState(2, 4, true);  // y=2, x=4
            grid.setCellState(2, 5, true);  // y=2, x=5
            grid.setCellState(2, 6, true);  // y=2, x=6

            // V�rification imm�diate apr�s configuration
            Logger::WriteMessage("V�rification de l'�tat initial...");

            // V�rifier l'�tat initial
            bool state1 = grid.getCellState(2, 4);
            bool state2 = grid.getCellState(2, 5);
            bool state3 = grid.getCellState(2, 6);

            std::string message = "�tats initiaux: (" +
                std::to_string(state1) + "," +
                std::to_string(state2) + "," +
                std::to_string(state3) + ")";
            Logger::WriteMessage(message.c_str());

            // V�rifications avec messages d�taill�s
            Assert::IsTrue(state1, L"t=0: Cellule (2,4) devrait �tre vivante");
            Assert::IsTrue(state2, L"t=0: Cellule (2,5) devrait �tre vivante");
            Assert::IsTrue(state3, L"t=0: Cellule (2,6) devrait �tre vivante");

            // Si ces tests passent, on continue avec l'update
            if (state1 && state2 && state3) {
                Logger::WriteMessage("�tat initial correct, ex�cution de update()...");
                grid.update();

                // V�rifier l'�tat apr�s update
                Assert::IsTrue(grid.getCellState(1, 5), L"t=1: Cellule (1,5) devrait �tre vivante");
                Assert::IsTrue(grid.getCellState(2, 5), L"t=1: Cellule (2,5) devrait �tre vivante");
                Assert::IsTrue(grid.getCellState(3, 5), L"t=1: Cellule (3,5) devrait �tre vivante");
            }
        }
    };
}