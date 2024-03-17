//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//User defined headers
#include"Button.h"


//This defines the gamestate

enum GameState{ Title,Loading,Playing };

//The Title Screen
void GameTitle() ;