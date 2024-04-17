// This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<time.h>

//Including header files


#include"Bullet.h"
//Definition of Bullet functions

void loadBullet(Bullet* b, char* filename)
{

	b->tex = LoadTexture(filename);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;

	b->scale = 1.0;


}
//Loading an existing texture
void loadBulletTex(Bullet* b, Texture2D t)
{
	b->tex = t;
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	b->scale = 1.0;
}

//The draw funciton
void drawBullet(Bullet b)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, WHITE);
}
//The draw function with a tint
void drawBulletTint(Bullet b, Color c)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, c);
}


void moveBullet(Bullet* b, float deltatime, float tilesize)
{
	b->pos.x += b->dir.x * b->velocity*deltatime;
	b->pos.y += b->dir.y * b->velocity*deltatime;

	b->trace += b->velocity * deltatime;
	
	

}



//Bullet Manager functions
void pushBulletManager(Bulletmanager * bullman, Bullet t)
{
	//We append the size of our manager by 1 if there is something already
	if (bullman->n > 0)
	{
		bullman->n += 1;

		//We allocate excess memory
		bullman->Bullets = (Bullet*)realloc(bullman->Bullets, bullman->n * sizeof(Bullet));

		//We set the new element to t
		bullman->Bullets[bullman->n - 1] = t;
	}
	//else define a new pointer
	else
	{
		bullman->n += 1;

		//We allocate a new pointer
		bullman->Bullets = (Bullet*)malloc(bullman->n * sizeof(Bullet));

		//We set the new element to t
		bullman->Bullets[bullman->n - 1] = t;
	}
}

//Delete function
void deleteindexBulletManager(Bulletmanager* t, int i)
{

	for (int j = i + 1; j < t->n; j++)
	{
		t->Bullets[j - 1] = t->Bullets[j];

	}

	t->n -= 1;
	//We reduce memory
	t->Bullets= (Bullet*)realloc(t->Bullets, t->n * sizeof(Bullet));

}

//UpdateBulletManager function
void updateBulletManager(Bulletmanager* t,float deltatime,float tilesize) 
{	
	int i = 0;
	while(i<t->n)
	{
		moveBullet(&t->Bullets[i], deltatime, tilesize);
		drawBullet(t->Bullets[i]);
		if (t->Bullets[i].trace > 1.1*t->Bullets[i].range * tilesize) 
		{
			
			deleteindexBulletManager(t, i);
		}
		else 
		{
			i++;
		}
	}
}


Vector2 unit(Vector2 start, Vector2 end)
{
	Vector2 ret;
	ret.x = end.x - start.x;
	ret.y = end.y - start.y;
	float mod = sqrt(pow(ret.x, 2) + pow(ret.y, 2));
	ret.x /= mod;
	ret.y /= mod;
	return ret;
}