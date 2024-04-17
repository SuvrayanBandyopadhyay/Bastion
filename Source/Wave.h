//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include"Bullet.h"
#include"Enemy.h"


//Number of enemies function

int NoOfEnemies(int wave);
//Health of enemies
float EnemeyHealth(int wave);

//Damage of enemies
float dmgEnemy(int wave);

//Function to create a new wave
void create_Wave(Enemymanager* eman, int wave, int width, int height, float tilesize, Texture2D t);
