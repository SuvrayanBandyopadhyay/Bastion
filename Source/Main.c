//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
//Custom Headers
#include"GameTitle.h"
#include"Game.h"
#include"Button.h"

int main(void)
{
    
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Game");

    SetTargetFPS(60);

    loadGameTitle();
    loadGame();
    int a = 0;
    while(!WindowShouldClose())
    {
        //Title
        if (a == 0)
            a = updateGameTitle();

        //Gamepaly
        else if (a == 1)
            a = updateGame();
        else
            break;
  
    }
   

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}