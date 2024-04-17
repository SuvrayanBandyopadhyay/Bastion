//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include"Bullet.h"
#include"Base.h"


typedef struct
{
	Texture2D tex;
	Vector2 pos;
	Vector2 dest;

	float scale;
	bool hover;//Checks if mouse is on the button or not
	
	float velocity;
	float health;
	float dmg;
	float range;
	float reload;
	float time_to_reload;


	//The index positions example (0,0) (2,3) ... this is for easy acess on the map array
	int ix;
	int iy;

	//The path of our enemy
	Vector2* path;
	int psize;

	//TO check if your char is stuck
	bool stuck;

}Enemy;



//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
void loadEnemy(Enemy* b, char* filename);
//TO copy an existing texture
void loadEnemyTex(Enemy* b, Texture2D t);


void drawEnemy(Enemy b);


//Just for moving nothing more
int moveEnemy(Enemy* b,float deltatime,float tilesize);

//Find path
//Vector2* path(int x, int y, int dx, int dy, int* map, int mapwidth, int mapheight, int limit);
void updatepath(Enemy* b, int dx, int dy, int* map,int mapwidth,int mapheight,int limit);


//Enemy list class
typedef struct
{
	Enemy* Enemies;
	int n;
}Enemymanager;

//Now these are my functions for the Enemy manager
void pushEnemyManager(Enemymanager* buildman, Enemy t);
//To destroy
void deleteindexEnemyManager(Enemymanager* t, int i);
//Check collision

//Function to check collision
bool isCollideEnemy(Enemy b, Vector2 o, float radius);


//The main function to update the enemy

void updateEnemies(Enemymanager* enemman, Base base, int* map, int mapwidth, int mapheight, int limit, int tilesize, float deltatime, Bulletmanager* bullman, Bulletmanager* allybullman);
