//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
//Custom Headers
#include"GameEngine.h"
#include"Button.h"

int main(void)
{
    
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Game");

    SetTargetFPS(120);

    GameTitle();
   

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}