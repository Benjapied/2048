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
    int iAsciiValue, iScore = 0;
    char sKey;
    bool bIsGame = true;

    this->gGameGrid.RandNumber();

    while (bIsGame) {

        this->gGameGrid.PrintGrid();

        std::cout << "Score :" << iScore << "\n";
        

        sKey = _getch();
        iAsciiValue = sKey;

        if (iAsciiValue == 75)
        {
            for (int i = 0; i <= 3; i++) {
                for (int j = 0; j < 4; j ++) {
                    CheckCases(i, j, -1, 0);
                }
            }
        }

        else if (iAsciiValue == 77) 
        {
            for (int i = 3; i >= 0; i--) {
                for (int j = 0; j < 4; j++) {
                    CheckCases(i, j, 1, 0);
                }
            }
        }
            
        else if (iAsciiValue == 80)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    CheckCases(i, j, 0, 1);
                }
            }
        }
           
        else if (iAsciiValue == 72)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    CheckCases(i, j, 0, -1);
                }
            }
        }
           
        system("cls");
        
        if (iAsciiValue == 27)
            bIsGame = false;

        if (this->gGameGrid.isFull() == true) {
            break;
        }

    }
    cout << "You loose";
    //this->gGameGrid.DeleteGrid();
};

void Game::CheckCases(int i, int j, int iDirectionX, int iDirectionY)
{
    int iNewIndex;
    int iTemp;
    if (this->gGameGrid.cGrid[this->gGameGrid.BiToMono(i, j)]->iValue != 0)
    {
        iNewIndex = this->gGameGrid.Move(i, j,  iDirectionX, iDirectionY);
        iTemp = this->gGameGrid.BiToMono(i, j);
        SwapCases(iTemp, iNewIndex);
    }
}

void Game::SwapCases(int i, int j)
{
    Case* temp = this->gGameGrid.cGrid[i];
    this->gGameGrid.cGrid[i] = this->gGameGrid.cGrid[j];
    this->gGameGrid.cGrid[j] = temp;
}