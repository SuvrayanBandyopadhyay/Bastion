//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>


typedef struct
{
	Texture2D tex;
	Rectangle SourceRect;//Defines the part of the texture we are going to use
	Vector2 pos;
	Vector2 size;

	bool hover;//Checks if mouse is on the button or not

}Tile;

//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadTile(Tile* b, char* filename);

//The draw function
void drawTile(Tile b);
//With a tint
void drawTileTint(Tile* b, Color c);

//The function to check if mouse is hovering on it or not
bool ishover(Tile* b, Vector2 m);
//Function to change draw area
void setTexCoords(Tile* b, int x1, int y1, int x2, int y2);


//Now this is the definition for our tile array, which will be used to control our tiles

typedef struct
{
	Tile* tiles;
	int n;
}Tilemanager;

//Now these are my functions for the tile manager
void pushTileManager(Tilemanager* tileman, Tile t);