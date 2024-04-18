//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//User defined headers
#include"Button.h"
#include"Tile.h"
#include"Building.h"
#include"HUD.h"
#include"Base.h"
#include"Enemy.h"
#include"Bullet.h"

//Global variables

//The list of tiles
Tilemanager tilelist;
//A list of Buildings
Buildingmanager buildman;

//The game camera
Camera2D gamecam;
//The HUD camera
Camera2D hudcam;
//The speed of our gamecamera
float gamecamspeed;
float maxzoom;
float minzoom;
//%Recovery on destroying a building
float rec;
//Total time
double tot_time;
//Wave number
int wave;

//Money
float m;

//The HUD
HUD hud;
//The size of our tiles
int tilesize;

//The Map
int* map;
int mapwidth;
int mapheight;
//The original map
int* original_map;

//Definitions of certain Buildings (Used to avoid changing a lot of data values in different places);
Building Basic_Tower;
Building Wall;//Walls are Buildings with 0 range and 0 damage and with comparatively more health;
Building Sniper;
Building Mine;

Base base;

//Enemy variables 

Enemymanager enemman;
Texture2D Enemy_Texture;

//Enemy Bullet Manager
Bulletmanager enembullman;
//Friendly Bullet Manager
Bulletmanager allybullman;

//Loading function
void loadGame(int* gamemap,unsigned int width,unsigned int height);



//The update function
int updateGame();
