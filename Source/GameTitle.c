#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//Custom-defined headers
#include"GameTitle.h"
#include"Button.h"
#include"Tile.h"

//Since all dimesnsions are with regards to my screen
int screen_height = 1200;
int screen_width = 1920;
//To convert the screen
int conv_height(int y,int act_height) 
{
    return(int)(((float)y / (float)screen_height) * (float)act_height);
}
int conv_width(int x,int act_width)
{
    return(int)(((float)x / (float)screen_width) * (float)act_width);
}


// Load game title
void loadGameTitle() 
{
    printf("%d,%d\n", GetScreenWidth(), GetScreenHeight());
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 1000, 1000 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //To avoid resolution problems
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    loadButton(&start, "Resources/Start_Button.png");
    int xoff = -650;
 
    start.pos.x = conv_width(xoff,w);
    start.pos.y = conv_height(-600,h);
    start.size.x *= 6;
    start.size.y *= 7;
    //Settings Button

    loadButton(&settings, "Resources/Settings.png");
    settings.pos.x = conv_width(xoff, w);
    settings.pos.y = conv_height( - 450,h);
    settings.size.x *= 6;
    settings.size.y *= 7;
    //Credits button

    loadButton(&credits, "Resources/Credits.png");


    credits.pos.x = conv_width(xoff,w);
    credits.pos.y = conv_height(- 300,h);
    credits.size.x *= 6;
    credits.size.y *= 7;

}


//Update title screen it return the next state
int updateGameTitle()
{
   
    //To avoid resolution problems
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    int retval = 0;
    ClearBackground(RAYWHITE);
    BeginDrawing();
    //Get mouse position
    Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(), camera);
    //Offset for cursor size

    //Checking if mouse hovers for all buttons\]
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
        retval= 4;//Go to settings
    }
    //For credits
    if (credits.hover == 1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        retval= 3; // Show the credits
    }


    //The Drawing part
    BeginMode2D(camera);
    //A gray screen for effect
    DrawRectangle(conv_width( - 1000,w), conv_height( - 1000,h), conv_width(750,w), conv_height(1500,h), LIGHTGRAY);

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
    DrawText("BASTION", conv_width(425,w), conv_height(- 950,h), conv_height(100,h), DARKGRAY);
    //Version name as well;
    DrawText("Version 1.0", conv_width(425,w), conv_height(- 850,h), conv_height(50,h), DARKGRAY);

    //End drawing and refresh the screen

    EndDrawing();
   
    return retval;
  
}
