#include"raylib.h"
#include"Credits.h"
#include<stdio.h>
#include<stdlib.h>
void load_Credits()
{
    home_tex = LoadTexture("Resources/Home.png");
}

int update_Credits()
{
    bool clickedOnTexture = false;
    SetTargetFPS(60);
    const int w=GetScreenWidth();
    const int h=GetScreenHeight();
    
    Rectangle textureRect = { 5, 5, 192, 124 };

    //Drawinf stuff
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, w / 3, h, LIGHTGRAY);
    DrawText("BASTION", w - conv_width(470,w), conv_height(45,h), 100, DARKGRAY);
    DrawText("Version 1.0", w - conv_width(470), conv_height(130,h), 30, DARKGRAY);
    DrawText("Credits", w / 12, h / 2 - conv_height(100,h), 70, DARKGRAY);
    DrawText("Shivani", w / 2, h / 2 -  conv_height(280,h), 40, DARKGRAY);
    DrawText("2301PH28", 4 * w / 5, h / 2 - conv_height(280,h), 40, DARKGRAY);
    DrawText("Rajit Anand", w / 2, h / 2 - conv_height(210,h), 40, DARKGRAY);
    DrawText("2301MC22", 4 * w / 5, h / 2 - conv_height(210,h), 40, DARKGRAY);
    DrawText("Jatin Aggarwal", w / 2, h / 2 - conv_height(140,h), 40, DARKGRAY);
    DrawText("2301ME23", 4 * w / 5, h / 2 - conv_height(140,h), 40, DARKGRAY);
    DrawText("Priyanshi Agrawal", w / 2, h / 2 - conv_height(70,h), 40, DARKGRAY);
    DrawText("2301ME40", 4 * w / 5, h / 2 - conv_height(70,h), 40, DARKGRAY);
    DrawText("Rishav Anand", w / 2, h / 2, 40, DARKGRAY);
    DrawText("2301MM34", 4 * w / 5, h / 2, 40, DARKGRAY);
    DrawText("Shefali Bishnoi", w / 2, h / 2 + conv_height(70,h), 40, DARKGRAY);
    DrawText("2301ME76", 4 * w / 5, h / 2 + conv_height(70,h), 40, DARKGRAY);
    DrawText("Ajay Ajay", w / 2, h / 2 + conv_height(140,h), 40, DARKGRAY);
    DrawText("2302VL02", 4 * w / 5, h / 2 + conv_height(140,h), 40, DARKGRAY);
    DrawText("Yagyesh Anshul", w / 2, h / 2 + conv_height(210,h), 40, DARKGRAY);
    DrawText("2302PC05", 4 * w / 5, h / 2 + conv_height(210,h), 40, DARKGRAY);
    DrawText("Suvrayan Bandyopadhyay", w / 2, h / 2 + conv_height(280,h), 40, DARKGRAY);
    DrawText("2301AI27", 4 * w / 5, h / 2 + conv_height(280,h), 40, DARKGRAY);
    DrawText("Shakib Akhtar", w / 2, h / 2 + conv_height(350,h), 40, DARKGRAY);
    DrawText("2301MC49", 4 * w / 5, h / 2 + conv_height(350,h), 40, DARKGRAY);
    //home

    if (CheckCollisionPointRec(GetMousePosition(), textureRect))
    {

        DrawTexture(home_tex, 10, 10, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            clickedOnTexture = true;
            return 0;
        }
    }
    else
    {

        DrawTexture(home_tex, 10, 10, WHITE);
    }
    EndDrawing();
       
   
    return 3;
}

