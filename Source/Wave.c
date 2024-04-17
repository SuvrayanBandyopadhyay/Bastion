//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS
#include"raylib.h"
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include"Bullet.h"
#include"Enemy.h"
#include<time.h>
#include<stdlib.h>

/*loadEnemy(&e, "Resources/Basic_Enemy.png");
	e.pos.x = (mapwidth-1) * tilesize;
	e.pos.y = (mapheight-1) * tilesize;

	e.scale = 1;
	e.dest.x = base.pos.x;
	e.dest.y = base.pos.y ;
	e.health = 25;
	e.dmg = 5;
	e.reload = 0.5;
	e.velocity = 250;
	e.psize = 0;
	e.ix = (mapwidth - 1);
	e.iy = (mapheight - 1);
	e.range = 15;//In tiles
	e.time_to_reload = e.reload;
	
	e.pos.x = e.ix * tilesize;
	e.pos.y = e.iy*tilesize;*/

int NoOfEnemies(int wave) 
{
	//It should increase using a formula
	float n = 4.0 + 2.0 * sqrt((float)wave) + 1.5 * log((float)wave) + ((float)wave / 2.5);
	return (int)n;
}

float EnemeyHealth(int wave) 
{
	//A formula for calculating enemy health with wave
	float n = 20.0 + 3.5*wave + 2.5 * log(wave);
	return n;
};

float dmgEnemy(int wave) 
{
	//For calculating damage
	float n = 8.0 + 2.5* wave + 0.5 * log(wave);
	return n;
}

void create_Wave(Enemymanager* eman, int wave, int width, int height,float tilesize,Texture2D t) 
{
	
	//Initializing randomness
	
	
	
	int enemy_no = NoOfEnemies(wave);

	//Adding all the enemies
	for (int i = 0; i < enemy_no; i++) 
	{
		//A generic enemy depending on wave
		Enemy e;
		e.tex = t;
		e.scale = 1;

		e.health = EnemeyHealth(wave);
		e.dmg = dmgEnemy(wave);
		e.reload = 0.5;
		e.velocity = 125;
		e.psize = 0;
		e.ix = (width - 1);
		e.iy = (height - 1);
		e.range = 15;//In tiles
		e.time_to_reload = e.reload;
		e.scale = 1.0;
		e.path = NULL;



		printf("%d\n",i);
		//Adding new enemies to the wave
		
		//Adding some randomness so each enemy is unique
		//10% randomness
		;
		e.velocity *= (1.0f + ((float)(rand()) / (float)(RAND_MAX)) * 0.1f);
		e.reload *= (1.0f + ((float)(rand()) / (float)(RAND_MAX)) * 0.1f);
		e.health *= (1.0f + ((float)(rand()) / (float)(RAND_MAX)) * 0.1f);
		e.dmg *= (1.0f + ((float)(rand()) / (float)(RAND_MAX)) * 0.1f);
		
		//Now adding pos
		int pos = rand() % 4;

		//Left
		if (pos == 0) 
		{
			e.ix = 0;
			e.iy = rand() % height;
		}

		//Up
		else if (pos == 1)
		{
			e.ix = rand()%width;
			e.iy = 0;
		}
		//Right
		else if (pos == 2)
		{
			e.ix = width-1;
			e.iy = rand() % height;
		}

		//Down
		else if (pos == 3)
		{
			e.ix = rand() % width;
			e.iy = height-1;
		}

		e.pos.x = e.ix * tilesize;
		e.pos.y = e.iy * tilesize;
		//Push this back
		pushEnemyManager(eman, e);
	}

	printf("OUT");
}