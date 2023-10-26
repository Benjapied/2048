#include "Grid.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

Grid::Grid()
{
    this->bIsFull = false;
    this->cGrid = (Case**) malloc(sizeof(Case*) * 16);
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
{
    int iCaseNb = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i % 2 == 0)
            {
                if (j % 2 != 0)
                    std::cout << "-";
                else
                    std::cout << " ";
            }
            else
            {
                if (j % 2 == 0)
                    std::cout << "|";
                else
                {
                    std::cout << this->cGrid[iCaseNb]->iValue;
                    iCaseNb++;
                }
            }
        }
        std::cout << "\n";
    }
}


int Grid::Move(int x, int y, int directionX, int directionY)
{
    std::cout << "test" << std::endl;
    if (x + directionX > 3 || x + directionX <= 0 || y + directionY > 3 || y + directionY <= 0) {
        //Stop condition: if the tile targeted can't move because of a wall, we return
        return this->BiToMono(x, y);
    }
    int iNewX = x + directionX;
    int iNewY = y + directionY;
    std::cout << directionX << ' ' << directionY << std::endl;

    
    if (this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue == this->cGrid[this->BiToMono(x, y)]->iValue)
    {
        std::cout << "fusion" << std::endl;
        //Stop condition: if the tile can be merged, we merge and return
        this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue *= 2;
        this->cGrid[this->BiToMono(x, y)]->iValue = 0;
        return this->BiToMono(x, y);
    }
    else if (this->cGrid[this->BiToMono(iNewX, iNewY)]->iValue != 0)
    {
        std::cout << "tile blocks" << std::endl;
        //Stop condition: if the tile targeted cant move because of another tile, we return
        return this->BiToMono(x, y);
    }
    else
    {
        std::cout << "recursion" << std::endl;
        //Recursion
        return this->Move(iNewX, iNewY, directionX, directionY);
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
    vector<int> iTab = this->ListEmptyCases();
    int iSize = iTab.size();
    int iRandomNumber = iTab[this->Rnd(iSize)];

    this->cGrid[iRandomNumber]->iValue = 2;
}

Case& Grid::operator[](int index)
{
    return *cGrid[index];
}

bool Grid::isFull() {
    for (int i = 0; i < 16; i++) {
        if (this->cGrid[i]->iValue == 0) {
            return false;
        }
    }
    return true;
}