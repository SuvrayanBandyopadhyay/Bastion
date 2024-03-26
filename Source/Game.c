//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//User defined headers
#include"Button.h"
#include"Tile.h"
#include"Game.h"
#include"HUD.h"

//Loading function
void loadGame()
{
	
	
	//Generating the tiles
	Texture2D tiletex = LoadTexture("Resources/Tile.png");
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			Tile t;
			loadTileTex(&t, tiletex);
			t.pos.x = j * 64;
			t.pos.y = i * 64;
			pushTileManager(&tilelist, t);
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

	loadHUD(&hud, "Resources/HUD.png","Resources/Money.png");
	//Setting the position of our HUD
	hud.pos.x = GetScreenWidth() / 2.0;
	hud.pos.y = GetScreenHeight() * 2.5 / 3.0;

	hud.size.x = GetScreenWidth()/ 2.0;
	hud.show = 1;

	maxzoom = 2.0f;
	minzoom = 0.8f;
}
float m=0;
int updateGame() 
{
	//The return value
	int retval = 1;

	//Refresh screen
	ClearBackground(RAYWHITE);
	BeginDrawing();

	//Camera testing
	//We multiply GetFrameTime() in order to have uniform movement irrespect of frame rate
	if(IsKeyDown(KEY_D))
		gamecam.target.x = gamecam.target.x + gamecamspeed*GetFrameTime()*(1.0/gamecam.zoom);
	if (IsKeyDown(KEY_A))
		gamecam.target.x = gamecam.target.x - gamecamspeed*GetFrameTime()*(1.0/gamecam.zoom);
	if (IsKeyDown(KEY_W))
		gamecam.target.y = gamecam.target.y - gamecamspeed*GetFrameTime()*(1.0/gamecam.zoom);
	if (IsKeyDown(KEY_S))
		gamecam.target.y = gamecam.target.y + gamecamspeed*GetFrameTime()*(1.0/gamecam.zoom);
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
	
	
	
	//The Drawing part
	BeginMode2D(gamecam);
	//We do some drawing

	//We draw our tiles here
	for (int i = 0; i < tilelist.n; i++) 
	{
		drawTile(tilelist.tiles[i]);
	}
	m += GetFrameTime();

	//Logic for our build mode
	if (hud.buildstate != 0) 
	{
		Vector2 ppos = mpos;
		ppos.y += hud.build_tex[0].height/2.0;
		//A small offset to match with mouse position
		ppos.y -= 64;
	

		//Now we subtract the remainder from 64 to clamp it to the tiles
		ppos.y = (int)ppos.y - ((int)ppos.y % 64);
		ppos.x = (int)ppos.x - ((int)ppos.x % 64);
		printf("%f,%f\n", ppos.x, ppos.y);
		Color c = { 150,255,150,200 };

		//Now fo the drawing position(Just has a small offset)
		Vector2 dpos = ppos;
		dpos.x -= 32;
		dpos.y += 32;
		DrawTextureEx(hud.build_tex[0], dpos, 0, 1.0, c);
	
	}


	////HUD LOGIC HERE
	//Finally we draw our HUD
	hudcam = gamecam;//The HUD camera has const zoom

	//Getting mouse position wrt to Hud Camera
	hudcam.zoom = 1.0f;
	mpos = GetScreenToWorld2D(GetMousePosition(), hudcam);


	BeginMode2D(hudcam);

	updateHud(&hud,mpos,gamecam.target,(int)m);

	EndDrawing();
	return retval;
}