
#include "Test.h"

class Game
{
public:
    int iPoints;
    Grid gGameGrid;

    Game();

    void GameLoop();

    void CheckCases(int i, int j, int iDirectionX, int iDirectionY);

    void SwapCases(int i, int j);
};
