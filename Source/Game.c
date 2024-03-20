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

//Loading function
void loadGame()
{
	Tile t;
	loadTile(&t, (char*)"Tile.png");
	pushTileManager(&tilelist, t);

	//Loading the camera
	camera.target = (Vector2){ 0, 0 };
	camera.offset = (Vector2){ 1000, 1000 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

int updateGame() 
{
	//The return value
	int retval = 1;
	//Refresh screen
	ClearBackground(RAYWHITE);
	BeginDrawing();
	//The Drawing part
	BeginMode2D(camera);
	//We do some drawing
	for (int i = 0; i < tilelist.n; i++) 
	{
		drawTile(tilelist.tiles[i]);
	}


	EndDrawing();
	return retval;
}