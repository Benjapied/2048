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
    int iAsciiValue;
    char sKey;
    bool bIsGame = true;
    bool isWin = false;

    this->gGameGrid.RandNumber();

    while (bIsGame) {

        std::cout << "Score :" << this->gGameGrid.iScore << "\n";

        this->gGameGrid.PrintGrid();

        if (this->gGameGrid.isFull() == true && this->gGameGrid.noPossibility() == true)
        {
            isWin = false;
            break;
        }

        if (this->gGameGrid.Win() == true)
        {
            isWin = true;
            break;
        }

        sKey = _getch();
        iAsciiValue = sKey;

        if (iAsciiValue == 75)
        {
            //Left
            for (int i = 0; i <= 3; i++) {
                for (int j = 0; j < 4; j ++) {
                    CheckCases(i, j, -1, 0);
                }
            }
            this->gGameGrid.RandNumber();
        }

        else if (iAsciiValue == 77) 
        {
            //Right
            for (int i = 3; i >= 0; i--) {
                for (int j = 0; j < 4; j++) {
                    CheckCases(i, j, 1, 0);
                }
            }
            this->gGameGrid.RandNumber();
        }
            
        else if (iAsciiValue == 80)
        {
            //Down
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    CheckCases(i, j, 0, 1);
                }
            }
            this->gGameGrid.RandNumber();
        }
           
        else if (iAsciiValue == 72)
        {
            //Up
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    CheckCases(i, j, 0, -1);
                }
            }
            this->gGameGrid.RandNumber();
        }
        
        this->gGameGrid.MergeFalse();

        system("cls");
        
        if (iAsciiValue == 27)
            bIsGame = false;

    }
    if (isWin == false)
    {
        cout << "You loose";
    }
    else
    {
        std::cout << "You won !";
    }
    
};

void Game::CheckCases(int i, int j, int iDirectionX, int iDirectionY)
{
    int iNewIndex;
    int iTemp;
    if (this->gGameGrid.cGrid[this->gGameGrid.BiToMono(i, j)]->iValue != 0)
    {
        iNewIndex = this->gGameGrid.Move(i, j, i, j, iDirectionX, iDirectionY);
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