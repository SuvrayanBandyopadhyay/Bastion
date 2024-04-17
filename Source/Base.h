//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>

/*
	The building codes are as follows
	1 - Basic Tower
	2 - Wall
	3 - Base
*/


typedef struct
{
	Texture2D tex;
	Vector2 pos;
	float scale;
	bool hover;//Checks if mouse is on the button or not


	float health;
	float cost;


	//The index positions example (0,0) (2,3) ... this is for easy acess on the map array
	int ix;
	int iy;
	//Width and height
	int width;
	int height;
	bool isbuilt;

	//Money per second
	float income;
}Base;


//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadBase(Base* b, char* filename);
//TO copy an existing texture
void loadBaseTex(Base* b, Texture2D t);

//The draw function
void drawBase(Base b);
//With a tint
void drawBaseTint(Base b, Color c);

//The function to check if mouse is hovering on it or not
bool ishoverBase(Base* b, Vector2 m);

//Function to check collision
bool isCollideBase(Base b, Vector2 o, float radius);

