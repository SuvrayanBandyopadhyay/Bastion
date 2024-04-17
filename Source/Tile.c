//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Including header files

#include"Tile.h"
//Definition of Tile functions
void loadTile(Tile* b, char* filename)
{
	
	b->tex = LoadTexture(filename);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	//Initial source is the entire texture... One can modify this later if there are multiple sprites in the spritesheet
	b->SourceRect.x = 0;
	b->SourceRect.y = 0;
	b->SourceRect.width = b->tex.width;
	b->SourceRect.height = b->tex.height;

	//Setting (initial) size of the button
	b->scale = 1.0;

}
//Loading an existing texture
void loadTileTex(Tile* b, Texture2D t)
{
	b->tex = t;
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	//Initial source is the entire texture... One can modify this later if there are multiple sprites in the spritesheet
	b->SourceRect.x = 0;
	b->SourceRect.y = 0;
	b->SourceRect.width = b->tex.width;
	b->SourceRect.height = b->tex.height;

	//Setting (initial) size of the button
	b->scale = 1.0;
}

//The draw funciton
void drawTile(Tile b)
{


	//Just draw the button

	DrawTextureEx(b.tex, b.pos, 0, b.scale, WHITE);
}
//The draw function with a tint
void drawTileTint(Tile b, Color c)
{

	//Just draw the button

	DrawTextureEx(b.tex, b.pos, 0, b.scale, c);//With a tint as well
}
//Changing coords
void setTexCoords(Tile* b, int x1, int y1, int x2, int y2)
{
	//Setting a new source rectangle
	b->SourceRect.x = x1;
	b->SourceRect.y = y1;
	b->SourceRect.width = x2;
	b->SourceRect.height = y2;

}

//is hover function 

bool ishoverTile(Tile* b, Vector2 m)
{

	//Mouse hover change
	m.y -= 10;
	b->hover = 0;
	//Initially assume mouse is not hovering on the button
	Rectangle bb;
	bb.x = b->pos.x - (b->tex.width / 2.0*b->scale);
	bb.y = b->pos.y - (b->tex.height*b->scale);
	bb.width = b->tex.width*b->scale;
	bb.height = b->tex.height*b->scale;

	bool collide = CheckCollisionPointRec(m, bb);

	if (collide)
	{
		b->hover = 1;
		return true;
	}

	return false;

}

//TileManager Functions
void pushTileManager(Tilemanager* tileman, Tile t)
{
	//We append the size of our manager by 1 if there is something already
	if (tileman->n > 0)
	{
		tileman->n += 1;

		//We allocate excess memory
		tileman->tiles = (Tile*)realloc(tileman->tiles, tileman->n * sizeof(Tile));

		//We set the new element to t
		tileman->tiles[tileman->n - 1] = t;
	}
	//else define a new pointer
	else
	{
		tileman->n += 1;

		//We allocate excess memory
		tileman->tiles = (Tile*)malloc(tileman->n * sizeof(Tile));

		//We set the new element to t
		tileman->tiles[tileman->n - 1] = t;
	}
}

