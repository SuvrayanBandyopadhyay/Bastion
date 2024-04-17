//Just to ensure no errors
#pragma once
//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include"Base.h"

typedef struct
{
	Texture2D tex;
	Vector2 pos;
	Vector2 dir;
	float trace;
	float range;

	float scale;

	float velocity;
	float dmg;

}Bullet;

//The Bullet texture
Texture2D BulletTexture;

//This loads the texture (Assuming there is only one sprite in the spritesheet for the button
extern void loadBullet(Bullet* b, char* filename);
//TO copy an existing texture
extern void loadBulletTex(Bullet* b, Texture2D t);


extern void drawBullet(Bullet b);


//Just for moving nothing more
extern void moveBullet(Bullet* b, float deltatime, float tilesize);

//NOW FOR THE BULLET MANAGER CLASS
//Enemy list class
typedef struct
{
	Bullet* Bullets;
	int n;
}Bulletmanager;

//Now these are my functions for the bullet manager
extern void pushBulletManager(Bulletmanager* bullman, Bullet b);
//To destroy
extern void deleteindexBulletManager(Bulletmanager* t, int i);
//Update bullet manager function
void updateBulletManager(Bulletmanager* t, float deltatime, float tilesize);

//To find the normalized vector

extern Vector2 unit(Vector2 start, Vector2 end);