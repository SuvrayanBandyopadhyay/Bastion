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
    Button start;
    loadButton(&start, "Start_Button2.png");
    int xoff = -650;
    printf("%f", start.size.y);
    start.pos.x = xoff;
    start.pos.y = -600;
    start.size.x *= 6;
    start.size.y *= 7;
    //Settings Button
    Button settings;
    loadButton(&settings, "Settings.png");
    settings.pos.x = xoff;
    settings.pos.y = -450;
    settings.size.x *= 6;
    settings.size.y *= 7;
    //Credits button
    Button credits;
    loadButton(&credits, "Credits.png");

    
    credits.pos.x = xoff;
    credits.pos.y = -300;
    credits.size.x *= 6;
    credits.size.y *= 7;


    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        BeginDrawing();
        //Get mouse position
        Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(), camera);
        //Offset for cursor size
        mousepos.y -= 10;
        BeginMode2D(camera);
        //A gray screen for effect
        DrawRectangle(-1000, -1000, 750, 1500, LIGHTGRAY);

        //Drawing the start button
        draw(&start);
        //Drawing the settings button
        draw(&settings);
        //Draw the credits button
        draw(&credits);
        //Checking for hover for the various buttons
        ishover(&start,mousepos);
        ishover(&settings, mousepos);
        ishover(&credits, mousepos);
        if (credits.hover == 1)
            printf("%d\n", credits.hover);
        else
            printf("%d\n", 0);
        
       
        //Define the name of our game
        DrawText("BASTION",  425, - 950, 100, DARKGRAY);
        //Version name as well;
        DrawText("Version 1.0", 425,- 850, 30, DARKGRAY);

        //End drawing and refresh the screen

        EndDrawing();
    }
	


	
}
