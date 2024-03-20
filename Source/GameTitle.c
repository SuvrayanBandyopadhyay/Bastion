#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//Custom-defined headers
#include"GameTitle.h"
#include"Button.h"
#include"Tile.h"


// Load game title
void loadGameTitle() 
{
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 1000, 1000 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    loadButton(&start, "Start_Button.png");
    int xoff = -650;
    printf("%f", start.size.y);
    start.pos.x = xoff;
    start.pos.y = -600;
    start.size.x *= 6;
    start.size.y *= 7;
    //Settings Button

    loadButton(&settings, "Settings.png");
    settings.pos.x = xoff;
    settings.pos.y = -450;
    settings.size.x *= 6;
    settings.size.y *= 7;
    //Credits button

    loadButton(&credits, "Credits.png");


    credits.pos.x = xoff;
    credits.pos.y = -300;
    credits.size.x *= 6;
    credits.size.y *= 7;

}


//Update title screen it return the next state
int updateGameTitle()
{
    int retval = 0;
    ClearBackground(RAYWHITE);
    BeginDrawing();
    //Get mouse position
    Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(), camera);
    //Offset for cursor size
    mousepos.y -= 10;
    //Checking if mouse hovers for all buttons
    isHoverButton(&start, mousepos);
    isHoverButton(&settings, mousepos);
    isHoverButton(&credits, mousepos);

    //Checking if buttons have been clicked and doing the corresponding actions
    //For start
    if (start.hover == 1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        retval= 1;//Start the game
    }
    //For settings
    if (settings.hover == 1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        retval= 2;//Go to settings
    }
    //For credits
    if (credits.hover == 1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        retval= 3; // Show the credits
    }


    //The Drawing part
    BeginMode2D(camera);
    //A gray screen for effect
    DrawRectangle(-1000, -1000, 750, 1500, LIGHTGRAY);

    //Drawing the start button normally if no hover is there
    if (start.hover == 0)
        drawButton(start);
    //Else add a tint
    else
        drawButtonTint(start, GRAY);

    //Drawing the start button normally if no hover is there
    if (settings.hover == 0)
        drawButton(settings);
    //Else add a tint
    else
        drawButtonTint(settings, GRAY);

    //Drawing the start button normally if no hover is there
    if (credits.hover == 0)
        drawButton(credits);
    //Else add a tint
    else
        drawButtonTint(credits, GRAY);


    //Define the name of our game
    DrawText("BASTION", 425, -950, 100, DARKGRAY);
    //Version name as well;
    DrawText("Version 1.0", 425, -850, 30, DARKGRAY);

    //End drawing and refresh the screen

    EndDrawing();
   
    return retval;
  
}
