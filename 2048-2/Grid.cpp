#include "Grid.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

Grid::Grid()
{
    this->bIsFull = false;
    this->cGrid = (Case**) malloc(sizeof(Case*) * 16);
    this->iScore = 0;
}

int Grid::BiToMono(int x, int y)
{
    int result = y * 4 + x;
    return result;
}

int* Grid::MonoToBi(int i)
{
    int array[2] = { i % 4 ,i / 4 };
    return array;
}

int Grid::Rnd(int n)
{
    int iNumber = rand() % n;
    return iNumber;
}

void Grid::InitGrid() {
    for (int i = 0; i < 16; i++) {
        this->cGrid[i] = new Case();
    }
}

void Grid::DeleteGrid()
{
    for (int i = 0; i < 16; i++) {
        delete this->cGrid[i];
    }
    free(cGrid);

}

void Grid::PrintGrid()
{   // Method from the grid class which prints the grid in the console log
    int iCaseNb = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << "---------------------";
        }
        else
        {
            for (int j = 0; j < 9; j++)
            {
                if (j % 2 == 0)
                    std::cout << "|";
                else
                {
                    if (this->cGrid[iCaseNb]->iValue < 10 && this->cGrid[iCaseNb]->iValue > 0)
                    {
                        std::cout << "  " << this->cGrid[iCaseNb]->iValue << " ";
                    }
                    else if (this->cGrid[iCaseNb]->iValue < 100 && this->cGrid[iCaseNb]->iValue > 10)
                    {
                        std::cout << " " << this->cGrid[iCaseNb]->iValue << " ";
                    }
                    else if (this->cGrid[iCaseNb]->iValue > 100 && this->cGrid[iCaseNb]->iValue < 1000)
                    {
                        std::cout << " " << this->cGrid[iCaseNb]->iValue;
                    }
                    else if (this->cGrid[iCaseNb]->iValue > 1000)
                    {
                        std::cout << this->cGrid[iCaseNb]->iValue;
                    }
                    else if (this->cGrid[iCaseNb]->iValue == 0)
                    {
                        std::cout << "    ";
                    }

                    iCaseNb++;
                }
            }
        }
        std::cout << "\n";
    }
}


int Grid::Move(int x, int y, int xBase, int yBase, int directionX, int directionY)
{
    int iNewX = x + directionX;
    int iNewY = y + directionY;

    if (iNewX > 3 || iNewX < 0 || iNewY > 3 || iNewY < 0) {
        //Stop condition: if the tile targeted can't move because of a wall, we return
        return this->BiToMono(x, y);
    }
    else if (this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue == this->cGrid[this->BiToMono(xBase, yBase)]->iValue && this->cGrid[this->BiToMono(iNewX, iNewY)]->bMergable == false )
    {
        //Stop condition: if the tile can be merged, we merge and return
        this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue *= 2;
        this->cGrid[this->BiToMono(iNewX, iNewY)]->bMergable = true;
        this->cGrid[this->BiToMono(xBase, yBase)]->iValue = 0;
        this->iScore += this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue;
        return this->BiToMono(xBase, yBase);
    }
    else if (this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue != 0)
    {
        //Stop condition: if the tile targeted cant move because of another tile, we return
        return this->BiToMono(x, y);
    }
    else
    {
        //Recursion
        return this->Move(iNewX, iNewY, xBase, yBase, directionX, directionY);
    }
}

vector<int> Grid::ListEmptyCases()
{
    //Renvoie la liste des indices dont les valeurs sont 0
    vector<int> vAray;

    for (int i = 0; i < 16; i++)
    {
        if (this->cGrid[i]->iValue == 0) {
            vAray.push_back(i);
        }
    }

    return vAray;
}

void Grid::RandNumber()
{
    //Return a random number between 2 and 4
    vector<int> iTab = this->ListEmptyCases();
    int iSize = iTab.size();
    int iRandomNumber = iTab[this->Rnd(iSize)];

    this->cGrid[iRandomNumber]->iValue = this->Rand2or4();
}

Case& Grid::operator[](int index)
{
    //Operetor which replace this->Gamegrid->grid[] by this->Gamegrid[]
    return *cGrid[index];
}

bool Grid::isFull() 
{
    //Return true if the grid is full
    for (int i = 0; i < 16; i++) {
        if (this->cGrid[i]->iValue == 0) {
            return false;
        }
    }
    return true;
}

void Grid::SwapCases(int i, int j)
{
    //Swap the position of i and j in the grid
    Case* temp = this->cGrid[i];
    this->cGrid[i] = this->cGrid[j];
    this->cGrid[j] = temp;
}

void Grid::MergeFalse()
{
    //Reset all the tiles as bMergable false
    for (int i = 0; i < 16; i++)
    {
        this->cGrid[i]->bMergable = false;
    }
}

bool Grid::noPossibility()
{   // Method from the grid class to check if there is still a movement possibility in the actual grid, returns true or false

    int iCoo;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            iCoo = this->BiToMono(i, j);
            
            if (j-1 >= 0)
            {
                if (j >= 0 && this->cGrid[iCoo]->iValue == this->cGrid[this->BiToMono(i , j - 1)]->iValue) {
                    return false;
                }
            }
            if (j+1 < 4)
            {
                if (j < 4 && this->cGrid[iCoo]->iValue == this->cGrid[this->BiToMono(i , j + 1)]->iValue) {
                    return false;
                }
            }
            if (i - 1 >= 0)
            {
                if (i >= 0 && this->cGrid[iCoo]->iValue == this->cGrid[this->BiToMono(i - 1, j )]->iValue) {
                    return false;
                }
            }
            if (i + 1 <  4)
            {
                if (i < 4 && this->cGrid[iCoo]->iValue == this->cGrid[this->BiToMono(i + 1, j )]->iValue) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Grid::Win()
{
    for (int p = 0; p < 16; p++)
    {
        if (this->cGrid[p]->iValue == 2048)
        {
            return true;
        }
    }
    return false;
}

int Grid::Rand2or4()
{
    //Return 2 or 4, 70% of dropping 2
    int iNumber = rand() % 100;
    if (iNumber < 70)
        return 2;
    return 4;
}