#include "Game.h"
#include <conio.h>
#include <iostream>

using namespace std;

Game::Game()
{
    this->iPoints = 0;
    this->gGameGrid.InitGrid();
}

void Game::GameLoop()
{
    int iNewIndex, iTemp, iAsciiValue, iScore = 0;
    char sKey;
    bool bIsGame = true;
    int direction[2];

    this->gGameGrid.RandNumber();
    this->gGameGrid.PrintGrid();

    while (bIsGame) {

        direction[0] = 0;
        direction[1] = 0;


        std::cout << "Score :" << iScore << "\n";
        

        sKey = _getch();
        iAsciiValue = sKey;

        if (iAsciiValue == 75)
        {
            direction[0] = -1;
            direction[1] = 0;
        }

        else if (iAsciiValue == 77) 
        {
            direction[0] = 1;
            direction[1] = 0;
        }
            
        else if (iAsciiValue == 80)
        {
            direction[0] = 0;
            direction[1] = 1;
        }
           
        else if (iAsciiValue == 72)
        {
            direction[0] = 0;
            direction[1] = -1;
        }
           
        if (iAsciiValue == 72 || iAsciiValue == 77 || iAsciiValue == 75 || iAsciiValue == 80) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (this->gGameGrid.cGrid[this->gGameGrid.BiToMono(i,j)]->iValue != 0)
                    {
                        iNewIndex = this->gGameGrid.Move(i, j, direction[0], direction[1]);
                        iTemp = this->gGameGrid.cGrid[this->gGameGrid.BiToMono(i, j)]->iValue;
                        this->gGameGrid.cGrid[this->gGameGrid.BiToMono(i, j)]->iValue = 0;
                        this->gGameGrid.cGrid[iNewIndex]->iValue = iTemp;
                    }
                }
            }
            system("cls");
            this->gGameGrid.PrintGrid();
        }
        
        if (iAsciiValue == 27)
            bIsGame = false;

        if (this->gGameGrid.isFull() == true) {
            break;
        }

    }
    cout << "You loose";
    //this->gGameGrid.DeleteGrid();
};
