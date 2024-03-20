//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Including header files

#include"Tile.h"
//Definition of button functions
void loadTile(Tile* b, char* filename)
{
	Texture2D temp = LoadTexture(filename);

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
	b->size.x = (float)b->tex.width;
	b->size.y = (float)b->tex.height;

}


//The draw funciton
void drawTile(Tile b)
{
	Rectangle rect;
	rect.x = b.pos.x;
	rect.y = b.pos.y;
	rect.width = b.size.x;
	rect.height = b.size.y;
	//Defining the origin
	Vector2 origin;
	origin.x = b.size.x / 2;
	origin.y = b.size.y / 2;

	//Just draw the button

	DrawTexturePro(b.tex, b.SourceRect, rect, origin, 0, WHITE);//White for no tint
}
//The draw function with a tint
void drawTileTint(Tile* b, Color c)
{
	Rectangle rect;
	rect.x = b->pos.x;
	rect.y = b->pos.y;
	rect.width = b->size.x;
	rect.height = b->size.y;
	//Defining the origin
	Vector2 origin;
	origin.x = b->size.x / 2;
	origin.y = b->size.y / 2;

	//Just draw the button

	DrawTexturePro(b->tex, b->SourceRect, rect, origin, 0, c);//With a tint as well
}
//Changing coords
/*void setTexCoords(Tile* b, int x1, int y1, int x2, int y2)
{
	//Setting a new source rectangle
	b->SourceRect.x = x1;
	b->SourceRect.y = y1;
	b->SourceRect.width = x2;
	b->SourceRect.height = y2;

	b->size.x = mod(x2 - x1);
	b->size.y = mod(y2 - y1);
}
*/
//is hover function 

bool ishover(Tile* b, Vector2 m)
{
	b->hover = 0;
	//Initially assume mouse is not hovering on the button
	Rectangle bb;
	bb.x = b->pos.x - (b->size.x / 2.0);
	bb.y = b->pos.y - (b->size.y);
	bb.width = b->size.x;
	bb.height = b->size.y;;

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
