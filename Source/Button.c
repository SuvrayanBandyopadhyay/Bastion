//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
//Including header files
#include<stdlib.h>
#include"Button.h"


//Definition of button functions
void loadButton(Button *b, char* filename)
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

void draw(Button *b)
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

	DrawTexturePro(b->tex,b->SourceRect,rect,origin,0,WHITE);//White for no tint
}

//is hover function 

void ishover(Button* b,Vector2 m,Camera2D cam) 
{
	//Initially assume mouse is not hovering on the button
	b->hover = 0;
	Rectangle bb;
	bb.x = b->pos.x-(b->size.x/2.0);
	bb.y = b->pos.y - (b->size.y);
	bb.width = b->size.x;
	bb.height = b->size.y;;
	
	bool collide = CheckCollisionPointRec( m,bb);

	if (collide) 
	{
		b->hover = 1;
	}


}

