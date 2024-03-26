//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//User defined headers
#include"Button.h"
#include"Tile.h"
#include"HUD.h"

//Global variables

//The list of tiles
Tilemanager tilelist;

//The game camera
Camera2D gamecam;
//The HUD camera
Camera2D hudcam;
//The speed of our gamecamera
float gamecamspeed;
float maxzoom;
float minzoom;
//The HUD
HUD hud;
//Loading function
void loadGame();



//The update function
int updateGame();
