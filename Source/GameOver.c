#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//Custom-defined headers
#include"GameTitle.h"
#include"Button.h"
#include"Tile.h"
#include"Game.h"
#include"GameTitle.h"
#include"Game.h"




//Update title screen it return the next state
int updateGameOver()
{
    ShowCursor();
    //To avoid resolution problems
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    int retval = 2;
    ClearBackground(RAYWHITE);
    BeginDrawing();
    
    DrawText("GAME OVER", conv_width(550, w), conv_height(450, h), 125, BLACK);
    
    char s[100];
    sprintf(s, "Waves Defeated %d", wave-1);
    DrawText(s, conv_width(600, w), conv_height(600, h), 75, BLACK);
    
    DrawText("PRESS SPACE TO RETURN", conv_width(600, w), conv_height(700, h), 50, BLACK);

    if (IsKeyPressed(KEY_SPACE)) 
    {
        loadGameTitle();
        
        //Blank map (Temporary)
        int mapsize = 80;
        int* blank_map = malloc(mapsize * mapsize * sizeof(int*));

        //Row
        for (int i = 0; i < mapsize; i++)
        {
            //Column
            for (int j = 0; j < mapsize; j++)
            {
                blank_map[i * mapsize + j] = 0;
            }
        }
        
        loadGame(blank_map,mapsize,mapsize);
        


        return 0;
    }

    EndDrawing();

    return retval;

}
