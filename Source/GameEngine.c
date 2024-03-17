#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//Custom-defined headers
#include"GameEngine.h"
#include"Button.h"


void GameTitle()
{
    //Temporary Camera defintion 

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 1000, 1000 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
	
    //Start Button Defintion
    Button b;
    loadButton(&b, "Start_Button.png");
    b.pos.x = -850;
    b.pos.y = -640;
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();
       


        BeginMode2D(camera);
        draw(&b);

        //Define the name of our game
        DrawText("BASTION",  425, - 950, 100, DARKGRAY);
        //Version name as well;
        DrawText("Version 1.0", 425,- 850, 30, DARKGRAY);

        //End drawing and refresh the screen

        EndDrawing();
    }
	


	
}
