#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
//User includes
#include"Button.h"

typedef struct 
{
	bool show;
	Texture2D tex;
	Vector2 pos;
	Vector2 size;
	Rectangle SourceRect;

	Texture2D moneyicon;
	
	//The Build Button
	Button Build;
	//The Stats Button
	Button Stats;

	///ALL THE BUILDING BUTTONS
	//Destroy button 
	Button destroy;
	
	//The Basic Tower Button
	
	Button buildBasicTower;
	Button buildWall;
	Button buildSniper;


	//To decide which state we are in
	int state;

	//Build state
	int buildstate;

	//Array of textures of buildings during our build state
	Texture2D* build_tex;

	//This bool is to check if we have clicked a button in order to prevent accidental placement while clicking buttons
	bool click;
}HUD;

//Our HUD will have buttons, resource count etc.
void loadHUD(HUD *b,char* filename);

//it takes the number of resources we have and displays it for the user
void updateHud(HUD *b, Vector2 mpos,Vector2 campos,int money);
