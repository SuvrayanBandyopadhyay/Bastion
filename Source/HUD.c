#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"HUD.h"


//The Load Function
void loadHUD(HUD* b,char* filename,char* moneyname) 
{
	//Load the texture
	b->tex = LoadTexture(filename);
	b->moneyicon = LoadTexture(moneyname);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	//Initial source is the entire texture... One can modify this later if there are multiple sprites in the spritesheet
	b->SourceRect.x = 0;
	b->SourceRect.y = 0;
	b->SourceRect.width = b->tex.width;
	b->SourceRect.height = b->tex.height;

	//Setting (initial) size of the button
	b->size.x = (float)b->tex.width;
	b->size.y = (float)b->tex.height;

	//Setting state
	b->state = 1;
	b->buildstate = 0;//Nothing selected

	//Loading buttons
	//Build Button
	loadButton(&b->Build, "Resources/hammer.png");
	//Stats Button
	loadButton(&b->Stats, "Resources/Stats.png");

	//Load the build basic tower button
	loadButton(&b->buildBasicTower, "Resources/Basic_Tower_Button.png");
	
	//Loading textures for placing when we are building
	b->build_tex = malloc(1 * sizeof(Texture2D));
	b->build_tex[0]= LoadTexture("Resources/Basic_Tower.png");

}



//The Draw Function (Also contains HUD login)
void updateHud(HUD *b, Vector2 mpos,Vector2 campos,int money)
{
	if (b->show == 1)
	{
		//Defining the area to draw in 
		Rectangle rect;
		rect.x = b->pos.x + campos.x;
		rect.y = b->pos.y + campos.y;
		rect.width = b->size.x;
		rect.height = b->size.y;
		//Defining the origin
		Vector2 origin;
		origin.x = b->size.x / 2;
		origin.y = b->size.y / 2;

		//Basic HUD drawing (Common for all states)
		Color c = { 255,255,255,200 };
		DrawTexturePro(b->tex, b->SourceRect, rect, origin, 0, c);//With a tint as well
		//We draw the build button

		//Now for the build button
		b->Build.pos.x = rect.x + 542;
		b->Build.pos.y = rect.y - 135;
		isHoverButton(&b->Build, mpos);
		if (b->Build.hover == 0)
			drawButton(b->Build);
		else
		{
			drawButtonTint(b->Build, GRAY);

			//If Button is clicked
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				b->state = 2;
			}
		}

		//Now for the stats button
		b->Stats.pos.x = rect.x + 542;
		b->Stats.pos.y = rect.y - 7;
		isHoverButton(&b->Stats, mpos);
		if (b->Stats.hover == 0)
			drawButton(b->Stats);
		else
		{
			drawButtonTint(b->Stats, GRAY);

			//If Button is clicked
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				b->state = 1;
				//Reset the build state
				b->buildstate = 0;
			}
		}


		//If we are in the stats state
		if (b->state == 1)
		{
			//Now we draw the money we have 
			DrawTexture(b->moneyicon, rect.x - 450, rect.y - 170, WHITE);
			char moneystr[1000];
			sprintf(moneystr, "%d", money);
			DrawText(moneystr, rect.x - 300, rect.y - 150, 75, BLACK);



		}


		//If we are in the build state
		if (b->state == 2)
		{
			//Build Button logic 
			b->buildBasicTower.pos.x = rect.x - 250;
			b->buildBasicTower.pos.y = rect.y - 90;
			isHoverButton(&b->buildBasicTower, mpos);
			if (b->buildBasicTower.hover == 0)
				drawButton(b->buildBasicTower);
			else
			{
				drawButtonTint(b->buildBasicTower, GRAY);

				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->buildstate = 1;
				}
			}

		}
	}

	//Now for build state logic (In case something is selected)
	if (b->buildstate != 0) 
	{
		//To leave build mode 
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) 
		{
			b->buildstate = 0;
		}

	}

}
