//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

typedef struct 
{
	Texture2D tex;
	Rectangle SourceRect;//Defines the part of the texture we are going to use
	Vector2 pos;
	Vector2 size;


}Button;

//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadButton(Button *b, char* filename);

//The draw function
void draw(Button *b);