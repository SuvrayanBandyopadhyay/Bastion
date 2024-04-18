
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"HUD.h"

//Since all dimesnsions are with regards to my screen
int screen_height_hud = 1200;
int screen_width_hud = 1920;
//To convert the screen



//The Load Function
void loadHUD(HUD* b,char* filename) 
{
	//Load the texture
	b->tex = LoadTexture(filename);
	b->moneyicon = LoadTexture("Resources/Money.png");
	b->healthicon = LoadTexture("Resources/Health.png");

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
	//Wall Button
	loadButton(&b->buildWall, "Resources/Wall_Button.png");
	//Load Sniper Tower
	loadButton(&b->buildSniper, "Resources/Sniper_Button.png");
	//Load Mine Button
	loadButton(&b->buildMine, "Resources/Mine_Button.png");


	//Load destroy button
	loadButton(&b->destroy, "Resources/Destroy.png");
	
	

	//Loading textures for placing when we are building
	b->build_tex = malloc(4 * sizeof(Texture2D));
	b->build_tex[0]= LoadTexture("Resources/Basic_Tower.png");
	//Now For wall textures
	b->build_tex[1] = LoadTexture("Resources/Wall.png");
	//Sniper textures
	b->build_tex[2] = LoadTexture("Resources/Sniper_Tower.png");
	//Mine Textures
	b->build_tex[3] = LoadTexture("Resources/Mine.png");

	b->click = 0;
}


//DONT USE CONV ON XOFF AND B.POS
//The Draw Function (Also contains HUD login)
void updateHud(HUD *b, Vector2 mpos,Vector2 campos,int money,int health)
{
	int w = GetScreenWidth();
	int h = GetScreenHeight();

	b->click = 0;
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
		//Check colisition 

		if (CheckCollisionCircleRec(mpos, 10, rect)) 
		{
	
			b->click = 1;
		}

		DrawTexturePro(b->tex, b->SourceRect, rect, origin, 0, c);//With a tint as well
		//We draw the build button

		//Now for the build button
		b->Build.pos.x = rect.x + conv_width(542,w);
		b->Build.pos.y = rect.y - conv_height(135,h);
		isHoverButton(&b->Build, mpos);
		if (b->Build.hover == 0)
			drawButton(b->Build);
		else
		{
			drawButtonTint(b->Build, GRAY);

			//If Button is clicked
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				b->click = 1;
				b->state = 2;
			}
		}

		//Now for the stats button
		b->Stats.pos.x = rect.x + conv_width(542,w);
		b->Stats.pos.y = rect.y - conv_height(7,h);
		isHoverButton(&b->Stats, mpos);
		if (b->Stats.hover == 0)
			drawButton(b->Stats);
		else
		{
			drawButtonTint(b->Stats, GRAY);

			//If Button is clicked
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				b->click = 1;
				
				b->state = 1;
				//Reset the build state
				b->buildstate = 0;
			}
		}


		//If we are in the stats state
		if (b->state == 1)
		{
			//Now we draw the money we have 
			DrawTexture(b->moneyicon, rect.x - conv_width(450,w), rect.y - conv_height(170,h), WHITE);
			char moneystr[1000];
			sprintf(moneystr, "%d", money);
			DrawText(moneystr, rect.x - conv_width(300,w), rect.y - conv_height(150,h), 75, BLACK);

			//Now we draw the Health we have 
			DrawTexture(b->healthicon, rect.x - conv_width(450, w), rect.y - conv_height(40, h), WHITE);
			char healthstr[1000];
			sprintf(healthstr, "%d", health);
			DrawText(healthstr, rect.x - conv_width(300, w), rect.y - conv_height(-10, h), 75, BLACK);


		}


		//If we are in the build state
		if (b->state == 2)
		{
			//Build Button positioning  
			//Buld basic tower positioning
			float xoff = rect.x - conv_width(250,w);

			b->buildBasicTower.pos.x = xoff;
			b->buildBasicTower.pos.y = rect.y - conv_height(90,h);
			//Build Wall positioning
			b->buildWall.pos.x = xoff;
			b->buildWall.pos.y = rect.y;
			//Build Sniper positioning
			b->buildSniper.pos.x = xoff;
			b->buildSniper.pos.y = rect.y + conv_height(90, h);

			//Mine Position
			b->buildMine.pos.x = xoff+conv_width(400,w);
			b->buildMine.pos.y = rect.y - conv_height(90, h);


			//Destroy positioning
			b->destroy.pos.x = xoff + conv_width(750);
			b->destroy.pos.y = rect.y - conv_height(165);
		

			//Checking if the mouse is hovering on the buttons
			isHoverButton(&b->buildBasicTower, mpos);
			isHoverButton(&b->buildWall, mpos);
			isHoverButton(&b->buildSniper, mpos);
			isHoverButton(&b->buildMine, mpos);

			Vector2 despos = mpos;
			despos.y = mpos.y + b->destroy.size.y;
			isHoverButton(&b->destroy, despos);
			

			bool onehover = 0;//Only hovering on 1 is possible
			//Basic Tower
			if (b->buildBasicTower.hover == 0)
				drawButton(b->buildBasicTower);
			else
			{
				drawButtonTint(b->buildBasicTower, GRAY);
				onehover = 1;
				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->click = 1;
					b->buildstate = 1;
				}
			}

			//Wall
			if (b->buildWall.hover == 0|| onehover == 1)
				drawButton(b->buildWall);
			else 
			{
				drawButtonTint(b->buildWall, GRAY);
				onehover = 1;
				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->click = 1;
					b->buildstate = 2;
				}
			}
			//Sniper
			if (b->buildSniper.hover == 0 || onehover == 1)
				drawButton(b->buildSniper);
			else
			{
				drawButtonTint(b->buildSniper, GRAY);
				onehover = 1;
				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->click = 1;
					b->buildstate = 3;
				}
			}

			//Mine
			if (b->buildMine.hover == 0 || onehover == 1)
				drawButton(b->buildMine);
			else
			{
				drawButtonTint(b->buildMine, GRAY);
				onehover = 1;
				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->click = 1;
					b->buildstate = 4;
				}
			}


			//Build state -1 is for destroying
			if (b->destroy.hover == 0 || onehover == 1)
				drawButton(b->destroy);
			else
			{
				drawButtonTint(b->destroy, GRAY);
				onehover = 1;
				//If the key is selected set build state to 1 (basic tower)
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					b->click = 1;
					b->buildstate = -1;
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
