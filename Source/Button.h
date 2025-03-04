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

}Button;

//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadButton(Button *b, char* filename);

//The draw function
void drawButton(Button b);
//With a tint
void drawButtonTint(Button b, Color c);

//The function to check if mouse is hovering on it or not
bool isHoverButton(Button* b, Vector2 m);