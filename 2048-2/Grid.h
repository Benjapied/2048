#include "Case.h"
#include <vector>
#include <string>

class Grid
{
public:
    bool bIsFull;
    Case** cGrid;
    int iScore;

    Grid();

    int BiToMono(int x, int y);
    
    int* MonoToBi(int i);
    
    int Rnd(int n);

    void InitGrid();
    
    void DeleteGrid();
   
    void PrintGrid();

    int Move(int x, int y, int xBase, int yBase, int directionX, int directionY);

    std::vector<int> ListEmptyCases();

    void RandNumber();

    Case& operator[](int index);

    bool isFull(); 

    void SwapCases(int i, int j);

    void MergeFalse();

    bool noPossibility();

    bool Win();

    int Rand2or4();
};
