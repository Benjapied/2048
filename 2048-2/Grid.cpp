#include "Grid.h"
#include <vector>
#include <iostream>

using namespace std;

Grid::Grid()
{
    this->bIsFull = false;
    this->cGrid = (Case**) malloc(sizeof(Case*) * 16);
}

int Grid::BiToMono(int x, int y)
{
    int result = x * 4 + y;
    return result;
}

int* Grid::MonoToBi(int i)
{
    int array[2] = { i / 4,i % 4 };
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

int Grid::MoveLeft(int iIndex)
{

    if (this->cGrid[iIndex - 1]->iValue == 0 && iIndex % 4 != 0)
    {
        return this->MoveLeft(iIndex - 1);
    }
    else
    {
        return iIndex;
    }
}

vector<int> Grid::ListEmptyCases()
{
    //Renvoie la liste des indices dont les valeurs sont 0
    vector<int> vAray;

    for (int i = 0; i < 16; i++)
    {
        std::cout << this->cGrid[i]->iValue;
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