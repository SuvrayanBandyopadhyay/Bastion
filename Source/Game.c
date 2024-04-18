
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
//User defined headers
#include"Button.h"
#include"Tile.h"
#include"Game.h"
#include"HUD.h"
#include"Base.h"
#include"Building.h"
#include"Enemy.h"
#include"Wave.h"


//Function to check if the block can be placed or not
bool canBePlaced(int* map, int x, int y, int width, int height, int mapwidth, int mapheight)
{

	for (int i = y; i < height + y; i++)
	{
		for (int j = x; j < width + x; j++)
		{
			//Out of bounds
			if (i < 0 || j < 0)
			{
				return 0;
			}

			if (i >= mapheight || j >= mapwidth)
			{
				return 0;
			}

			if (map[i * mapwidth + j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
//Function to place the block
void place(int** map, int x, int y, int width, int height, int mapwidth, int code)
{
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
		
			(*map)[i * mapwidth + j] = code;//
		}
	}
}

//The function to destroy a building on the map
void destroy(int** map,int * original, int x, int y, int width, int height, int mapwidth)
{
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{

			(*map)[i * mapwidth + j] = original[i*mapwidth+j];
		}
	}
}


Enemy e;
//Loading function
void loadGame(int *gamemap,unsigned int width,unsigned int height)
{
	//Clearing previous iteration
	//free(enembullman.Bullets);
	//free(allybullman.Bullets);
	//free(enemman.Enemies);
	//free(buildman.Buildings);
	enembullman.n = 0;
	allybullman.n = 0;
	enemman.n = 0;
	buildman.n = 0;

	//Randomness
	srand(time(NULL));

	//Setting our map as the gamemap
	free(map);//To delete any existing map ///Just in case
	map = gamemap;
	
	
	tilesize = 64;
	//Generating the tiles
	mapwidth = width;
	mapheight = height;
	//Creating an original map to revert to whenever we destroy buildings
	
	original_map = malloc(mapwidth * mapheight * sizeof(int));
	memcpy(original_map, map, mapwidth * mapheight * sizeof(int));

	Texture2D tiletex = LoadTexture("Resources/Tile.png");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i * width + j] == 0)
			{
				Tile t;
				loadTileTex(&t, tiletex);
				t.pos.x = j * tilesize;
				t.pos.y = i * tilesize;
				pushTileManager(&tilelist, t);
			}
		}
	}
	

	//Loading the camera
	gamecam.target = (Vector2){ 0, 0 };
	gamecam.offset = (Vector2){ 0,0 };
	gamecam.rotation = 0.0f;
	gamecam.zoom = 1.0f;
	gamecamspeed = 1000;

	hudcam = gamecam;//The HUD camera has const zoom

	//Now we load the HUD

	loadHUD(&hud, "Resources/HUD.png");
	//Setting the position of our HUD
	hud.pos.x = GetScreenWidth() / 2.0;
	hud.pos.y = GetScreenHeight() * 2.5 / 3.0;

	hud.size.x = GetScreenWidth()/ 2.0;
	hud.show = 1;

	maxzoom = 2.0f;
	minzoom = 0.8f;

	//Defining the various Buildings
	//THE BASIC TOWER
	Basic_Tower.cost = 40.0;
	Basic_Tower.range = 8;
	Basic_Tower.health = 80;
	Basic_Tower.isbuilt = 0;//Default state
	Basic_Tower.scale = 1.0;
	Basic_Tower.dmg = 8;
	Basic_Tower.reload = 1;
	Basic_Tower.height = 2;
	Basic_Tower.width = 2;
	Basic_Tower.type = 1;
	Basic_Tower.income = 0;
	//THE WALL
	Wall.cost = 10;
	Wall.range = 0;
	Wall.health = 120;
	Wall.isbuilt = 0;//Default state
	Wall.scale = 1.0;
	Wall.dmg = 0;
	Wall.reload = 99999999999;
	Wall.height = 1;
	Wall.width = 1;
	Wall.type = 2;
	Wall.income = 0;
	//Sniper Definition
	Sniper.cost = 60.0;
	Sniper.range = 20;
	Sniper.health = 60;
	Sniper.isbuilt = 0;//Default state
	Sniper.scale = 1.0;
	Sniper.dmg = 20;
	Sniper.reload = 5;
	Sniper.height = 2;
	Sniper.width = 2;
	Sniper.type = 3;
	Sniper.income = 0;
	//THE WALL
	Mine.cost = 35;
	Mine.range = 0;
	Mine.health = 120;
	Mine.isbuilt = 0;//Default state
	Mine.scale = 1.0;
	Mine.dmg = 0;
	Mine.reload = 99999999999;
	Mine.height = 2;
	Mine.width = 2;
	Mine.type = 4;
	Mine.income = 0.6;



	//Loading base
	loadBase(&base, "Resources/Base.png");
	base.cost = 1000;
	base.health = 200;
	base.ix = mapwidth/2;
	base.iy = mapheight/2;
	base.pos.x = tilesize * base.ix;
	base.pos.y = tilesize * base.iy;
	base.scale = 1.0;
	base.width = 3;
	base.height = 3;
	place(&map,base.ix,base.iy,base.width,base.height,mapwidth,3);

	

	//Recovery money
	rec = 0.5;


	tot_time = 0;

	//Load the bullet Texture
	BulletTexture = LoadTexture("Resources/Bullet.png");
	//Load the enemy texture
	Enemy_Texture = LoadTexture("Resources/Basic_Enemy.png");

	//Wave Number
	wave = 0;

	//Initial Money
	m = 1000;

	//Initial Camera Position
	gamecam.target.x = (mapwidth / 2.75)*(tilesize);
	gamecam.target.y = (mapheight / 2.5)*(tilesize);

}




//The build state logic (The function to be used when we are building new buildings


void buildfunc(HUD h, Buildingmanager* buildman,Vector2 mpos,int** map,float *money ) 
{
	Vector2 ppos = mpos;
	//ppos.y += hud.build_tex[0].height / 2.0;
	//A small offset to match with mouse position
	//ppos.y -= tilesize;

	//Setting initial size of buildman

	//Now we subtract the remainder from tilesize to clamp it to the tiles
	ppos.y = (int)mpos.y - ((int)mpos.y % tilesize);
	ppos.x = (int)mpos.x - ((int)mpos.x % tilesize);

	//If it can be placed
	Color okc = { 150,255,150,200 };
	//If it cant be placed
	Color nokc = { 255,150,150,200 };

	//Now fo the drawing position(Just has a small offset)
	Vector2 dpos = ppos;


	//+5 is an offset to reduce errors
	int tilex = (int)(ppos.x) / tilesize;
	int tiley = (int)(ppos.y) / tilesize;

	//For basic Building
	
	if (hud.buildstate == 1)
	{

		if (canBePlaced(*map, tilex, tiley, Basic_Tower.width, Basic_Tower.height,mapwidth, mapheight)&&*money>=Basic_Tower.cost)
		{
			DrawTextureEx(hud.build_tex[0], dpos, 0, 1.0, okc);
			//If we press the build key

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				
				Building t;
				t = Basic_Tower;
				loadBuildingTex(&t, hud.build_tex[0]);
				t.pos = dpos;
				t.ix = tilex;
				t.iy = tiley;
				*money -= t.cost;
	
				//buildman is already a pointer
				pushBuildingManager(buildman, t);
				place(map, tilex, tiley, t.width, t.height,mapwidth,t.type);
			}

		}
		else
		{
			//Texture cant be drawn
			DrawTextureEx(hud.build_tex[0], dpos, 0, 1.0, nokc);
		
		}
	}

	//For Wall
	else if (hud.buildstate == 2)
	{
		//Here size is 1
		if (canBePlaced(*map, tilex, tiley, Wall.width, Wall.height, mapwidth, mapheight)&& *money >= Wall.cost)
		{
			DrawTextureEx(hud.build_tex[1], dpos, 0, 1.0, okc);
			//If we press the build key

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				Building t;
				t = Wall;
				loadBuildingTex(&t, hud.build_tex[1]);
				t.pos = dpos;
				t.ix = tilex;
				t.iy = tiley;
				//Subtracting the cost
				*money -= t.cost;

				//buildman is already a pointer
				pushBuildingManager(buildman, t);
				place(map, tilex, tiley, t.width, t.height, mapwidth, t.type);
			}

		}
		else
		{
			//Texture cant be drawn
			DrawTextureEx(hud.build_tex[1], dpos, 0, 1.0, nokc);
		}
	}

	//Fow Sniper Tower
	else if (hud.buildstate == 3)
	{
		//Here size is 1
		if (canBePlaced(*map, tilex, tiley, Sniper.width, Sniper.height, mapwidth, mapheight) && *money >= Sniper.cost)
		{
			DrawTextureEx(hud.build_tex[2], dpos, 0, 1.0, okc);
			//If we press the build key

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				Building t;
				t = Sniper;
				loadBuildingTex(&t, hud.build_tex[2]);
				t.pos = dpos;
				t.ix = tilex;
				t.iy = tiley;
				//Subtracting the cost
				*money -= t.cost;

				//buildman is already a pointer
				pushBuildingManager(buildman, t);
				place(map, tilex, tiley, t.width, t.height, mapwidth, t.type);
			}

		}
		else
		{
			//Texture cant be drawn
			DrawTextureEx(hud.build_tex[2], dpos, 0, 1.0, nokc);
		}
	}

	//Fow Mine
	else if (hud.buildstate == 4)
	{
		//Here size is 1
		if (canBePlaced(*map, tilex, tiley, Mine.width, Mine.height, mapwidth, mapheight) && *money >= Mine.cost)
		{
			DrawTextureEx(hud.build_tex[3], dpos, 0, 1.0, okc);
			//If we press the build key

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				Building t;
				t = Mine;
				loadBuildingTex(&t, hud.build_tex[3]);
				t.pos = dpos;
				t.ix = tilex;
				t.iy = tiley;
				//Subtracting the cost
				*money -= t.cost;

				//buildman is already a pointer
				pushBuildingManager(buildman, t);
				place(map, tilex, tiley, t.width, t.height, mapwidth, t.type);
			}

		}
		else
		{
			//Texture cant be drawn
			DrawTextureEx(hud.build_tex[3], dpos, 0, 1.0, nokc);
		}
	}


}
float nextwave = 0;

int updateGame()
{
	
	float income_per_sec = 0;
	tot_time += GetFrameTime();
	nextwave += GetFrameTime();
	//The return value
	int retval = 1;


	//Refresh screen
	ClearBackground(RAYWHITE);
	BeginDrawing();

	//Camera testing
	//We multiply GetFrameTime() in order to have uniform movement irrespect of frame rate
	if (IsKeyDown(KEY_D)&&gamecam.target.x<(mapwidth+-(30/gamecam.zoom))*tilesize)
		gamecam.target.x = gamecam.target.x + gamecamspeed * GetFrameTime() * (1.0 / gamecam.zoom);
	if (IsKeyDown(KEY_A) && gamecam.target.x >( - 1 * tilesize))
		gamecam.target.x = gamecam.target.x - gamecamspeed * GetFrameTime() * (1.0 / gamecam.zoom);
	if (IsKeyDown(KEY_W) && gamecam.target.y > (-1 * tilesize))
		gamecam.target.y = gamecam.target.y - gamecamspeed * GetFrameTime() * (1.0 / gamecam.zoom);
	if (IsKeyDown(KEY_S) && gamecam.target.y < (mapheight - (17 / gamecam.zoom)) * tilesize)
		gamecam.target.y = gamecam.target.y + gamecamspeed * GetFrameTime() * (1.0 / gamecam.zoom);



	//The Zoom logic
	float wheel = GetMouseWheelMove();
	float wheelconst = 0.1;

	gamecam.zoom += wheelconst * wheel;


	//Clamping the zoom values
	if (gamecam.zoom > maxzoom)
	{
		gamecam.zoom = maxzoom;
	}
	if (gamecam.zoom < minzoom)
	{
		gamecam.zoom = minzoom;
	}

	//The HUD show logic
	if (IsKeyReleased(KEY_TAB))
	{
		if (hud.show == 1)
			hud.show = 0;
		else if (hud.show == 0)
			hud.show = 1;
	}
	//Getting mouse position with respect to the screen
	Vector2 mpos = GetScreenToWorld2D(GetMousePosition(), gamecam);

	
	//Enemy logic
	updateEnemies(&enemman, base, map, mapwidth, mapheight, 10000, tilesize, GetFrameTime(), &enembullman, &allybullman);
	
	//The Building logic part
	//Here we update all the buildings
	updateBuildings(&buildman, &enembullman,&allybullman, &map, original_map, mapwidth,enemman,GetFrameTime(),tilesize,&income_per_sec);


	//For Base
	int id = 0;
	while (id < enembullman.n)
	{
		if (isCollideBase(base, enembullman.Bullets[id].pos, 5))
		{
			base.health -= enembullman.Bullets[id].dmg;
			deleteindexBulletManager(&enembullman, id);
			
		}

		else
		{
			id++;
		}
	}

	


	//The Drawing part
	BeginMode2D(gamecam);
	//We do some drawing

	//We draw our tiles here
	for (int i = 0; i < tilelist.n; i++)
	{
		drawTile(tilelist.tiles[i]);
	}

	//Add base
	income_per_sec += base.income;
	m += GetFrameTime() * income_per_sec;//Temporary


	//Variables to keep track of the buildings to destroy
	int dnum = -1;

	//Destroying Buildings logic
	//Now draw all the Buildings (including with red tint if player hovers on them while in destoy mode
	for (int i = 0; i < buildman.n; i++)
	{
		//When destroying buildings(buildstate is -1), draw them with a red tint
		if (hud.buildstate == -1 && ishoverBuilding(&buildman.Buildings[i], mpos))
		{
			Color c = { 255,200,200,255 };
			drawBuildingTint(buildman.Buildings[i], c);

			//To click and destroy
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				dnum = i;
			}
		}


		//Draw normally
		else
		{
			drawBuilding(buildman.Buildings[i]);
		}
	}
	//Deleting a Building
	if (dnum != -1)
	{
		Building t = buildman.Buildings[dnum];
		m += rec * t.cost;
		destroy(&map, original_map, t.ix, t.iy, t.width, t.height, mapwidth);
		deleteindexBuildingManager(&buildman, dnum);
	}
	// Draw the base
		drawBase(base);
	//DRAWING BULLETS
	updateBulletManager(&enembullman, GetFrameTime(), tilesize);
	//Draw Friendly Bullets
	updateBulletManager(&allybullman, GetFrameTime(), tilesize);

	
	//Draw enemies
	for (int i = 0; i < enemman.n; i++)
		drawEnemy(enemman.Enemies[i]);


	//Next wave
	if (nextwave>45)
	{
		nextwave = 0;
		wave++;

		//Base Health increases every wave (Covers for repairs and upgrades)
		if (wave != 0)
		{
			base.health += 20;
		}
		create_Wave(&enemman, wave, mapwidth, mapheight, tilesize, Enemy_Texture);
	
	}

	

	////HUD LOGIC HERE
	//Finally we draw our HUD
	hudcam = gamecam;//The HUD camera has const zoom

	//Getting mouse position wrt to Hud Camera
	hudcam.zoom = 1.0f;
	mpos = GetScreenToWorld2D(GetMousePosition(), hudcam);

	Vector2 ppos = GetScreenToWorld2D(GetMousePosition(), gamecam);
	
	
	BeginMode2D(hudcam);

	//Update the HUD
	updateHud(&hud, mpos, gamecam.target, (int)m,(int)base.health);
	
	//Shifting back to the game camera
	BeginMode2D(gamecam);
	//Logic for our build mode
	//It should activate when we have selected a building and we havent clicked anything else this frame
	if (hud.buildstate > 0 && hud.click == 0)
	{
		HideCursor();
		buildfunc(hud, &buildman, ppos, &map,&m);
	}
	else
	{
		ShowCursor();
	}

	//End condition 
	if (base.health < 0) 
	{
		return 2;
	}

	EndDrawing();
	return retval;
}
