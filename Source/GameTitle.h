//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>

//User defined headers
#include"Button.h"


//Global variable
Camera2D camera;
//Start Button Defintion
Button start;
Button settings;
Button credits;

//Loading the title screen
void loadGameTitle();

//The Title Screen update
int updateGameTitle() ;

