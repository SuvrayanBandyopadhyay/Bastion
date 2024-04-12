#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    bool clickedOnTexture = false;
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Credits");
    SetTargetFPS(60);
    const int w=GetScreenWidth();
    const int h=GetScreenHeight();
    Texture2D home_tex=LoadTexture("Home.png");
    Rectangle textureRect = { 10, 10, 192, 192 };

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(0, 0, w/3, h, LIGHTGRAY);
            DrawText("BASTION", w-470, 10, 100, DARKGRAY);
            DrawText("Version 1.0", w-470, 100, 30, DARKGRAY);
            DrawText("Credits", w/12, h/2-100, 70, DARKGRAY);
            DrawText("Shivani", w/2, h/2-280, 40, DARKGRAY);
            DrawText("2301PH28", 4*w/5, h/2-280, 40, DARKGRAY);
            DrawText("Rajit Anand", w/2, h/2-210, 40, DARKGRAY);
            DrawText("2301MC22", 4*w/5, h/2-210, 40, DARKGRAY);
            DrawText("Jatin Aggarwal", w/2, h/2-140, 40, DARKGRAY);
            DrawText("2301ME23", 4*w/5, h/2-140, 40, DARKGRAY);
            DrawText("Priyanshi Agrawal", w/2, h/2-70, 40, DARKGRAY);
            DrawText("2301ME40", 4*w/5, h/2-70, 40, DARKGRAY);
            DrawText("Rishav Anand", w/2, h/2, 40, DARKGRAY);
            DrawText("2301MM34", 4*w/5, h/2, 40, DARKGRAY);
            DrawText("Shefali Bishnoi", w/2, h/2+70, 40, DARKGRAY);
            DrawText("2301ME76", 4*w/5, h/2+70, 40, DARKGRAY);
            DrawText("Ajay Ajay", w/2, h/2+140, 40, DARKGRAY);
            DrawText("2302VL02", 4*w/5, h/2+140, 40, DARKGRAY);
            DrawText("Yagyesh Anshul", w/2, h/2+210, 40, DARKGRAY);
            DrawText("2302PC05", 4*w/5, h/2+210, 40, DARKGRAY);
            DrawText("Suvrayan Bandyopadhyay", w/2, h/2+280, 40, DARKGRAY);
            DrawText("2301AI27",4*w/5, h/2+280, 40, DARKGRAY);
            DrawText("Shakib Akhtar", w/2, h/2+350, 40, DARKGRAY);
            DrawText("2301MC49", 4*w/5, h/2+350, 40, DARKGRAY);
            //home

             if (CheckCollisionPointRec(GetMousePosition(), textureRect))
            {

                DrawTexture(home_tex, 10, 10, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    clickedOnTexture = true;
                }
            }
            else
            {

                DrawTexture(home_tex, 10, 10, WHITE);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

