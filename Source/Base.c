//This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Including header files
#include"Base.h"



//Definition of Tile functions
void loadBase(Base* b, char* filename)
{

	b->tex = LoadTexture(filename);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;

	b->scale = 1.0;

	b->income = 1.5;//1.5 money per second
}
//Loading an existing texture
void loadBaseTex(Base* b, Texture2D t)
{
	b->tex = t;
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	b->scale = 1.0;
}

//The draw funciton
void drawBase(Base b)
{


	DrawTextureEx(b.tex, b.pos, 0, b.scale, WHITE);
}
//The draw function with a tint
void drawBaseTint(Base b, Color c)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, c);
}

bool ishoverBase(Base* b, Vector2 m)
{
	b->hover = 0;
	//Initially assume mouse is not hovering on the button
	Rectangle bb;
	bb.x = b->pos.x - (b->tex.width * b->scale / 2.0);
	bb.y = b->pos.y - (b->tex.height * b->scale);
	bb.width = b->tex.width * b->scale;
	bb.height = b->tex.height * b->scale;

	bool collide = CheckCollisionPointRec(m, bb);

	if (collide)
	{
		b->hover = 1;
		return true;
	}

	return false;

}


//Is projectile colliding
bool isCollideBase(Base b, Vector2 o,float radius)
{
	Rectangle r;
	r.x = b.pos.x;
	r.y = b.pos.y;
	r.width = b.tex.width;
	r.height = b.tex.height;

	return CheckCollisionCircleRec(o, radius,r);


}

