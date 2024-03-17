//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

//Including header files
#include"raylib.h"
#include"Button.h"
#include<stdio.h>

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
	//Just draw the button
	DrawTextureEx(b->tex,b->pos,0,1.0,WHITE);//White for no tint
}
