// 2048-2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Game.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    Game game;
    game.GameLoop();


    return 0;
}

