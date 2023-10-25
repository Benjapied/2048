#include "Case.h"
#include <vector>

using namespace std;

class Grid
{
public:
    bool bIsFull;
    Case* cGrid;


    Grid();
    

    int BiToMono(int x, int y);
    
    int* MonoToBi(int i);
    
    int Rnd(int n);
    
    void InitiateGrid();
    
    //void DeleteGrid();
   
    void PrintGrid();

    int MoveLeft(int iIndex);

    vector<int> ListEmptyCases();

    void RandNumber();

    Case& operator[](int index);

    bool isFull(); 
};
