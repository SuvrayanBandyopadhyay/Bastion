//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"raylib.h"
#include<stdio.h>
//Custom Headers
#include"GameTitle.h"
#include"Game.h"
#include"GameOver.h"
#include"Credits.h"
#include"Button.h"


int main()
{
    //Blank map 
    int mapsize = 60;
    int* blank_map = malloc(mapsize*mapsize*sizeof(int*));
    
    //Row
    for (int i = 0; i < mapsize; i++) 
    {
        //Column
        for (int j = 0; j < mapsize; j++) 
        {
            blank_map[i*mapsize+j] = 0;
        }
    }
   
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Game");
    //No escape key
    //SetExitKey(0);

    SetTargetFPS(60);

    load_Credits();
    loadGameTitle();
    loadGame(blank_map,mapsize,mapsize);
    int a = 0;
    while(!WindowShouldClose())
    {
        //Title
        if (a == 0)
            a = updateGameTitle();

        //Gameplay
        else if (a == 1)
            a = updateGame();

        else if (a == 2) 
        {
            a = updateGameOver();
        }

        else if (a == 3) 
        {
            a = update_Credits();
        }


        else
            break;
     
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
   

    return 0;
}
