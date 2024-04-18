//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Including header files
#include"Building.h"
#include"Enemy.h"
#include"Game.h"


//Definition of Tile functions
void loadBuilding(Building* b, char* filename)
{

	b->tex = LoadTexture(filename);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;

	b->scale = 1.0;
	

}
//Loading an existing texture
void loadBuildingTex(Building* b, Texture2D t)
{
	b->tex = t;
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	b->scale = 1.0;
}

//The draw funciton
void drawBuilding(Building b)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, WHITE);
}
//The draw function with a tint
void drawBuildingTint(Building b, Color c)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, c);
}

bool ishoverBuilding(Building* b, Vector2 m)
{
	m.y-=15;
	b->hover = 0;
	//Initially assume mouse is not hovering on the button
	Rectangle bb;
	bb.x = b->pos.x;
	bb.y = b->pos.y - (b->tex.width * b->scale)/2.0;
	bb.width = b->tex.width*b->scale;
	bb.height = b->tex.height*b->scale;

	bool collide = CheckCollisionCircleRec(m,1,bb);

	if (collide)
	{
		b->hover = 1;
		return true;
	}

	return false;

}


//Push function for the Buildingmanager
//TileManager Functions
void pushBuildingManager(Buildingmanager* buildman, Building t)
{
	//We append the size of our manager by 1 if there is something already
	if (buildman->n > 0)
	{
		buildman->n += 1;

		//We allocate excess memory
		buildman->Buildings = (Buildingmanager*)realloc(buildman->Buildings, buildman->n * sizeof(Building));

		//We set the new element to t
		buildman->Buildings[buildman->n - 1] = t;
	}
	//else define a new pointer
	else
	{
		buildman->n += 1;

		//We allocate a new pointer
		buildman->Buildings = (Buildingmanager*)malloc(buildman->n * sizeof(Building));

		//We set the new element to t
		buildman->Buildings[buildman->n - 1] = t;
	}
}

//Delete function
void deleteindexBuildingManager(Buildingmanager* t, int i)
{
	
	for (int j = i+1; j < t->n; j++) 
	{
		t->Buildings[j-1]= t->Buildings[j];

	}

	t->n -= 1;
	//We reduce memory
	t->Buildings = (Buildingmanager*)realloc(t->Buildings, t->n * sizeof(Building));

}

//Is projectile colliding
bool isCollideBuilding(Building b, Vector2 o,float radius)
{
	Rectangle r;
	r.x = b.pos.x;
	r.y = b.pos.y;
	r.width = b.tex.width;
	r.height = b.tex.height;
	

	
	return CheckCollisionCircleRec(o, radius, r);

}

//Update all buildings
void destroy2(int** map, int* original, int x, int y, int width, int height, int mapwidth)
{
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{

			(*map)[i * mapwidth + j] = original[i * mapwidth + j];//
		}
	}
}

//Find distance
float dist(float x1, float y1, float x2, float y2)
{

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//Update all buildings
void updateBuildings(Buildingmanager* buildman, Bulletmanager* enembullman,Bulletmanager* allbullman, int** map, int* original_map, int mapwidth,Enemymanager eneman,float deltatime,float tilesize,float* income)
{

	int id = 0;
	while (id < buildman->n)
	{
		*income += buildman->Buildings[id].income;

		int j = 0;
		//Checking damage for every bullet
		while (j < enembullman->n)
		{
			if (isCollideBuilding(buildman->Buildings[id], enembullman->Bullets[j].pos, 5))
			{
				buildman->Buildings[id].health -= enembullman->Bullets[j].dmg;
				deleteindexBulletManager(enembullman, j);;
			}

			else
			{
				j++;
			}
		}

		//Firing at enemies which are in range
		if (buildman->Buildings[id].range>0&&buildman->Buildings[id].reload_time_left <= 0)
		{
			for (int k = 0; k < eneman.n; k++)
			{
				//Predefining a bullet here
				Bullet p;
				//Pos is same as current pos
				p.pos = buildman->Buildings[id].pos;
				//A small offset
				p.pos.x += buildman->Buildings[id].tex.width / 2.0 * buildman->Buildings[id].scale;
				p.pos.y += buildman->Buildings[id].tex.height / 2.0 * buildman->Buildings[id].scale;


				p.dmg = buildman->Buildings[id].dmg;
				p.scale = 1.0;
				p.velocity = 2500;
				p.tex = BulletTexture;
				p.range = buildman->Buildings[id].range + 0.5;
				p.trace = 0;
				//If in range
				if (dist(eneman.Enemies[k].pos.x, eneman.Enemies[k].pos.y, buildman->Buildings[id].pos.x, buildman->Buildings[id].pos.y) < buildman->Buildings[id].range * tilesize) 
				{
			
					//Shoot at the base
					p.dir = unit(p.pos, eneman.Enemies[k].pos);
					pushBulletManager(allbullman, p);
					buildman->Buildings[id].reload_time_left = buildman->Buildings[id].reload;
					break;
				}
			}
		}
		else 
		{
			buildman->Buildings[id].reload_time_left -= deltatime;
		}

		//Destroying buildings with 0 health
		if (buildman->Buildings[id].health <= 0)
		{
			destroy2(map, original_map, buildman->Buildings[id].ix, buildman->Buildings[id].iy, buildman->Buildings[id].width, buildman->Buildings[id].height, mapwidth);
			deleteindexBuildingManager(buildman, id);
		}
		else
		{
			id++;
		}

	}
}