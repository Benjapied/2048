#include "Game.h"
#include "Grid.h"
#include <conio.h>
#include <iostream>

using namespace std;

Game::Game()
{
    this->iPoints = 0;
    this->gGameGrid.InitiateGrid();
}

void Game::GameLoop()
{
    int iNewIndex;
    char sKey;
    int iAsciiValue;
    bool bIsGame = true;
    while (bIsGame) {

        this->gGameGrid.RandNumber();

        this->gGameGrid.PrintGrid();

        sKey = _getch();
        iAsciiValue = sKey;

        if (iAsciiValue == 75)
        {
            for (int i = 0; i < 16; i++)
            {
                if (i % 4 != 0 && this->gGameGrid.cGrid[i].iValue != 0)
                {
                    iNewIndex = this->gGameGrid.MoveLeft(i);
                    this->gGameGrid.cGrid[iNewIndex].iValue = this->gGameGrid.cGrid[i].iValue;
                    this->gGameGrid.cGrid[i].iValue = 0;
                    if (iNewIndex % 4 != 0 && this->gGameGrid.cGrid[iNewIndex - 1].iValue == this->gGameGrid.cGrid[iNewIndex].iValue)
                    {
                        this->gGameGrid.cGrid[iNewIndex - 1].iValue *= 2;
                        this->gGameGrid.cGrid[iNewIndex].iValue = 0;
                    }
                }
            }
        }

        else if (iAsciiValue == 77)
            std::cout << "Pressed right \n";

        else if (iAsciiValue == 80)
            std::cout << "Pressed down \n";

        else if (iAsciiValue == 72)
            std::cout << "Pressed up \n";

        if (iAsciiValue == 27)
            bIsGame = false;

        system("cls");

        if (this->gGameGrid.isFull() == true) {
            break;
        }

    }
    cout << "You loose";
    //this->gGameGrid.DeleteGrid();
}
