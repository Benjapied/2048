#include "Test.h"
#include <windows.h>
#include <iostream>

Test::Test()
{
	this->gTestGrid.InitGrid();
	this->gEndGrid.InitGrid();
}

bool Test::CheckGrid(Grid grid1, Grid grid2)
{
	//Function which compare 2 grid, return true if they are the same
	for (int q = 0; q < 16; q++)
	{
		if (grid1[q].iValue != grid2[q].iValue)
		{
			return false;
		}
	}
	return true;
}

void Test::LunchTests() {
	this->IntegrationTest1();
	this->IntegrationTest2();
	this->IntegrationTest3();
	this->IntegrationTest4();
	this->IntegrationTest5();
}

void Test::IntegrationTest1()
{

	int iNewIndex, iTemp;
	for (int k = 0; k < 16; k++)
	{
		this->gTestGrid[k].iValue = 2;
		this->gTestGrid[k].bMergable = false;
	}
	this->gTestGrid.PrintGrid();
	for (int i = 15; i > -1; i--)
	{
		int* coo = this->gTestGrid.MonoToBi(i);
		iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], 0, 1);
		iTemp = this->gTestGrid.cGrid[i]->iValue;
		this->gTestGrid.cGrid[i]->iValue = 0;
		this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;
		if (iNewIndex < 12 && this->gTestGrid.cGrid[iNewIndex + 4]->iValue == this->gTestGrid.cGrid[iNewIndex]->iValue && this->gTestGrid.cGrid[iNewIndex + 4]->bMergable == false) // We check if the case downward the selected one has the same value
		{ // If indeed they're equal, we merge them and increment the score
			this->gTestGrid.cGrid[iNewIndex + 4]->iValue *= 2;
			this->gTestGrid.cGrid[iNewIndex]->iValue = 0;
			this->gTestGrid.cGrid[iNewIndex + 4]->bMergable = true;
		}
	}
	Sleep(2000);
	system("cls");
	this->gTestGrid.PrintGrid();
	for (int l = 0; l < 16; l++)
	{
		this->gTestGrid[l].bMergable = false;
	}
	for (int j = 15; j > -1; j--)
	{
		int* coo = this->gTestGrid.MonoToBi(j);
		iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], 0, 1);
		iTemp = this->gTestGrid.cGrid[j]->iValue;
		this->gTestGrid.cGrid[j]->iValue = 0;
		this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;
		if (iNewIndex < 12 && this->gTestGrid.cGrid[iNewIndex + 4]->iValue == this->gTestGrid.cGrid[iNewIndex]->iValue && this->gTestGrid.cGrid[iNewIndex + 4]->bMergable == false) // We check if the case downward the selected one has the same value
		{ // If indeed they're equal, we merge them and increment the score
			this->gTestGrid.cGrid[iNewIndex + 4]->iValue *= 2;
			this->gTestGrid.cGrid[iNewIndex]->iValue = 0;
			this->gTestGrid.cGrid[iNewIndex + 4]->bMergable = true;
		}
	}
	Sleep(2000);
	system("cls");
	this->gTestGrid.PrintGrid();
}

void Test::IntegrationTest2()
{
	int iNewIndex, iTemp;
	this->gTestGrid[0].iValue = 4;
	this->gTestGrid[1].iValue = 2;
	this->gTestGrid[3].iValue = 2;
	this->gTestGrid[5].iValue = 4;
	this->gTestGrid[7].iValue = 8;
	this->gTestGrid[13].iValue = 8;
	this->gTestGrid[15].iValue = 8;

	this->gTestGrid.PrintGrid();
	for (int l = 0; l < 16; l++)
	{
		this->gTestGrid[l].bMergable = false;
	}
	for (int i = 0; i < 16; i++)
	{
		int* coo = this->gTestGrid.MonoToBi(i);
		iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], -1, 0);
		iTemp = this->gTestGrid.cGrid[i]->iValue;
		this->gTestGrid.cGrid[i]->iValue = 0;
		this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;
		if (iNewIndex % 4 != 0 && this->gTestGrid.cGrid[iNewIndex - 1]->iValue == this->gTestGrid.cGrid[iNewIndex]->iValue && this->gTestGrid.cGrid[iNewIndex - 1]->bMergable == false) // We check if the case downward the selected one has the same value
		{ // If indeed they're equal, we merge them and increment the score
			this->gTestGrid.cGrid[iNewIndex - 1]->iValue *= 2;
			this->gTestGrid.cGrid[iNewIndex]->iValue = 0;
			this->gTestGrid.cGrid[iNewIndex - 1]->bMergable = true;
		}
	}
	Sleep(2000);
	system("cls");
	this->gTestGrid.PrintGrid();
}

void Test::IntegrationTest3()
{
	//We have a grid of test and a grid of reference
	//We want to know is the merge feature happens once by round for one tile

	int config[4][4] =
	{
		{2, 4, 2, 2},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	int config2[4][4] =
	{
		{0, 2, 4, 4},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	//Init of both grid
	bool bVerified;
	int iNewIndex, iTemp;
	for (int n = 0; n < 4; n++)
	{
		for (int m = 0; m < 4; m++)
		{
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].iValue = config[n][m];
			this->gEndGrid[this->gEndGrid.BiToMono(n, m)].iValue = config2[n][m];
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].bMergable = false;
		}
	}

	//Movement of all tiles
	for (int i = 15; i > -1; i--)
	{
		int* coo = this->gTestGrid.MonoToBi(i);
		iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], 0, 1);
		iTemp = this->gTestGrid.cGrid[i]->iValue;
		this->gTestGrid.cGrid[i]->iValue = 0;
		this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;
	}
	bVerified = this->CheckGrid(this->gTestGrid, this->gEndGrid);

	if (bVerified == true)
		std::cout << "Test 3 is a success \n";
	else
		std::cout << "Test 3 is a failure \n";
}

void Test::IntegrationTest4()
{
	//We want to know if the event of loose happen when we have no possibility anymore
	int config[4][4] =
	{
		{2, 2, 8, 16},
		{4, 8, 16, 4},
		{8, 16, 4, 8},
		{16, 32, 64, 128}
	};

	//Init of the grid
	bool bVerified;
	int iNewIndex, iTemp;
	for (int n = 0; n < 4; n++)
	{
		for (int m = 0; m < 4; m++)
		{
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].iValue = config[n][m];
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].bMergable = false;
		}
	}

	for (int i = 15; i > -1; i--)
	{
		int* coo = this->gTestGrid.MonoToBi(i);
		iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], 1, 0);
		iTemp = this->gTestGrid.cGrid[i]->iValue;
		this->gTestGrid.cGrid[i]->iValue = 0;
		this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;
		
	}
	this->gTestGrid[0].iValue = 8;

	if (this->gTestGrid.isFull() == true && this->gTestGrid.noPossibility() == true)
		std::cout << "Test 4 is a success \n";
	else
		std::cout << "Test 4 is a failure \n";
}

void Test::IntegrationTest5()
{
	//we check is the win condition is working by making a grid with 2 1024 and merge them 
	int config[4][4] =
	{
		{512, 64, 64, 1024},
		{0, 8, 32, 0},
		{128, 8, 16, 1024},
		{0, 2, 4, 8}
	};

	bool bVerified;
	int iNewIndex, iTemp;
	for (int n = 0; n < 4; n++)
	{
		for (int m = 0; m < 4; m++)
		{
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].iValue = config[n][m];
			this->gTestGrid[this->gTestGrid.BiToMono(n, m)].bMergable = false;
		}
	}

	for (int i = 0; i < 16; i++) // We go through our array the same way we did to go left, from top left to bottom right
	{
		if (i >= 4 && this->gTestGrid.cGrid[i]->iValue != 0) // We check if we're not on the 1st line by seeing if the index is at least 4, and if the actual case is also not 0, we can move up
		{
			int* coo = this->gTestGrid.MonoToBi(i);
			iNewIndex = this->gTestGrid.Move(coo[0], coo[1], coo[0], coo[1], 1, 0);
			iTemp = this->gTestGrid.cGrid[i]->iValue;
			this->gTestGrid.cGrid[i]->iValue = 0;
			this->gTestGrid.cGrid[iNewIndex]->iValue = iTemp;

		}
	}

	if (this->gTestGrid.Win())
		std::cout << "Test 5 is a success \n";
	else
		std::cout << "Test 5 is a failure \n";
}