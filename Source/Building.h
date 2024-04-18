//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include"Bullet.h"
#include"Enemy.h"

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
	//Type is used for identification
	int type;

	float dmg;
	float range;
	float health;
	float cost;
	float reload;//Reload time

	float reload_time_left; //This is used while firing a shot

	//The index positions example (0,0) (2,3) ... this is for easy acess on the map array
	int ix;
	int iy;
	//Width and height
	int width;
	int height;
	bool isbuilt;

	float income;
}Building;


//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadBuilding(Building* b, char* filename);
//TO copy an existing texture
void loadBuildingTex(Building* b, Texture2D t);

//The draw function
void drawBuilding(Building b);
//With a tint
void drawBuildingTint(Building b, Color c);

//The function to check if mouse is hovering on it or not
bool ishoverBuilding(Building* b, Vector2 m);

//Now for the Building manager
typedef struct
{
	Building* Buildings;
	int n;
}Buildingmanager;

//Now these are my functions for the building manager
void pushBuildingManager(Buildingmanager* buildman, Building t);
//To destroy
void deleteindexBuildingManager(Buildingmanager* t, int i);

//Function to check collision
bool isCollideBuilding(Building b, Vector2 o,float radius);

//Update Enemy logic
//A copy of the destroy function
void updateBuildings(Buildingmanager* buildman, Bulletmanager* enembullman, Bulletmanager* allbullman, int** map, int* original_map, int mapwidth, Enemymanager eneman, float deltatime, float tilesize);
