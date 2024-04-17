// This is to supress depreciation errors which might happen since we are working with C
#define _CRT_SECURE_NO_WARNINGS

#include"raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>

//Including header files
#include"Enemy.h"
#include"Bullet.h"
#include"Base.h"


//For Enemy class
//Bullet Manager functions


//Definition of Enemy functions
void loadEnemy(Enemy * b, char* filename)
{
	
	b->tex = LoadTexture(filename);
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;

	b->scale = 1.0;


}
//Loading an existing texture
void loadEnemyTex(Enemy* b, Texture2D t)
{
	b->tex = t;
	//Initial position is set to origin
	b->pos.x = 0;
	b->pos.y = 0;
	b->scale = 1.0;
}

//The draw funciton
void drawEnemy(Enemy b)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, WHITE);
}
//The draw function with a tint
void drawEnemyTint(Enemy b, Color c)
{
	DrawTextureEx(b.tex, b.pos, 0, b.scale, c);
}

bool ishoverEnemy(Enemy* b, Vector2 m)
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


int moveEnemy(Enemy* b,float deltatime,float tilesize) 
{
	float mindiff = 10;//If distance less than this value...

	Vector2 diff;
	diff.x = b->dest.x - b->pos.x;
	diff.y = b->dest.y - b->pos.y;

	float epsilon = 0.000001;

	float moddiff = sqrt(pow(diff.x, 2) + pow(diff.y, 2)) + epsilon;
	

	diff.x /= moddiff;
	diff.y /= moddiff;


	b->pos.x += diff.x * b->velocity*deltatime;
	b->pos.y += diff.y * b->velocity*deltatime;

	b->ix = (int)(b->pos.x / tilesize);
	b->iy = (int)(b->pos.y / tilesize);

	//If cant move
	if (moddiff < mindiff)
	{
	
		//too close Has reached
		return -1;
	}
	//Can still move
	return 0;
	
}


//PATHFINDING 
//Pathfinding the node struct is used to store the possible paths during pathfinding
struct node 
{
	int x;
	int y;
	float gcost;
	float hcost;
	int prev;//The previous node
};

typedef struct node node;

//We also define a list of nodes
struct nodelist 
{
	node* nodes;
	int n;
	
	
};
typedef struct nodelist nodelist;
//Pushback
void pushnodelist(nodelist* nlist, node newn)
{

	//Initializing a new node list
	if (nlist->n > 0)
	{
		
		nlist->n += 1;
		nlist->nodes = (node*)realloc(nlist->nodes, nlist->n * sizeof(node));
		nlist->nodes[nlist->n - 1] = newn;
	}


	//Using the previous node list
	else 
	{
		nlist->n += 1;
		nlist->nodes = malloc(nlist->n * sizeof(node));
		nlist->nodes[nlist->n - 1] = newn;
	}
}
//Delet
void deletefromnodelist(nodelist* nlist,int i) 
{
	for (int j = i + 1; j < nlist->n; j++)
	{
		nlist->nodes[j - 1] = nlist->nodes[j];

	}

	nlist->n -= 1;
	//We reduce memory
	nlist->nodes = (node*)realloc(nlist->nodes, nlist->n * sizeof(node));
}
//To get g cost increment
float getgcost(int mapcode) 
{
	
	if (mapcode == 0) 
	{
		return 1.0f;
	}

	else if (mapcode == 1) 
	{
		return 30.0f;
	}

	if (mapcode == 2) 
	{
		return 50.0f;
	}
	if (mapcode == 3) 
	{
		return 1.0f;
	}
}
//Function to get the heuristic
float getdist(int ix,int iy , int ex,int ey) 
{
	
	return (float)sqrt(pow((double)(ex-ix),2.0)+pow((double)(ey-iy),2.0));
}
//Get f value
float getf(node n) 
{
	return ((float)n.hcost + (float)n.gcost);
}

//Find the node with smallest cost
int smallestcost(nodelist nlist) 
{
	float val= getf(nlist.nodes[0]);
	int id=0;
	for (int i = 1; i < nlist.n; i++) 
	{
		float newval = getf(nlist.nodes[i]);
		if (newval < val) 
		{
			id = i;
			val = newval;
		}

	}

	return id;
}
//Check if it already exists in the path
bool hasbeenchecked(nodelist clist,nodelist olist, node n) 
{
	for (int i = 0; i < clist.n; i++) 
	{
		if (clist.nodes[i].x == n.x && clist.nodes[i].y == n.y) 
		{
			return 1;
		}
	}

	for (int i = 0; i < olist.n; i++)
	{
		if (olist.nodes[i].x == n.x && olist.nodes[i].y == n.y)
		{
			
			return 1;
		}
	}
	return 0;
}



//Update path function

void updatepath(Enemy* b, int dx, int dy, int* map, int mapwidth, int mapheight, int limit) 
{

	free(b->path);

	//The open list in A* pathfinding
	nodelist olist;
	olist.n = 0;
	//The closed list in A* pathfinding
	nodelist clist;
	clist.n = 0;
	//Now for the starting node
	node first;
	first.prev = -1;
	first.x = (int)b->ix;
	first.y = (int)b->iy;
	first.gcost = 0;
	first.hcost = getdist(b->ix, b->iy, (int)dx, (int)dy);

	pushnodelist(&olist, first);


	//Finding the path

	node curr;
	
	for (int i = 0; i < limit; i++)
	{
	
		if (olist.n == 0)
		{
			break;
		}
		int id = smallestcost(olist);
		curr = olist.nodes[id];

		if (curr.hcost == 0)//If distance from destination is 0
		{
			break;//Path found
		}
		//Else we find upto 4 adjucent paths
		//Right path
		if (curr.x + 1 < mapwidth)
		{

			node right;
			right.x = curr.x + 1;
			right.y = curr.y;


			right.hcost = getdist(right.x, right.y, dx, dy);

			right.gcost = getgcost(map[right.y * mapwidth + right.x]) + curr.gcost;

			right.prev = clist.n;//Because the current curr will be pushed to this position

			if (hasbeenchecked(clist, olist, right) == 0)
				pushnodelist(&olist, right);


		}
		//Left path
		if (curr.x - 1 >= 0)
		{
			node left;
			left.x = curr.x - 1;
			left.y = curr.y;

			left.hcost = getdist(left.x, left.y, dx, dy);
			left.gcost = getgcost(map[left.y * mapwidth + left.x]) + curr.gcost;
			left.prev = clist.n;
			if (hasbeenchecked(clist, olist, left) == 0)
				pushnodelist(&olist, left);

		}
		//Up path
		if (curr.y - 1 >= 0)
		{
			node up;
			up.x = curr.x;
			up.y = curr.y - 1;

			up.hcost = getdist(up.x, up.y, dx, dy);
			up.gcost = getgcost(map[up.y * mapwidth + up.x]) + curr.gcost;
			up.prev = clist.n;
			if (hasbeenchecked(clist, olist, up) == 0)
				pushnodelist(&olist, up);

		}
		//Down path
		if (curr.y + 1 < mapheight)
		{

			node down;
			down.x = curr.x;
			down.y = curr.y + 1;

			down.hcost = getdist(down.x, down.y, dx, dy);
			down.gcost = getgcost(map[down.y * mapwidth + down.x]) + curr.gcost;
			down.prev = clist.n;
			if (hasbeenchecked(clist, olist, down) == 0)
				pushnodelist(&olist, down);
		}

		
		pushnodelist(&clist, curr);
		deletefromnodelist(&olist, id);

	}

	node rev;
	rev = curr;
	int n = 1;
	Vector2* newpath = malloc(1 * sizeof(Vector2));
	Vector2 v;
	v.x = curr.x;
	v.y = curr.y;
	newpath[0] = v;


	while (rev.prev != -1)
	{

		n = n + 1;

		rev = clist.nodes[rev.prev];
		newpath = (Vector2*)realloc(newpath, (n) * sizeof(Vector2));
		Vector2 v;
		v.x = rev.x;
		v.y = rev.y;

		newpath[n - 1] = v;
	}
	//Reversing the list
	for (int i = 0; i < (n / 2); i++)
	{
		Vector2 temp = newpath[i];
		newpath[i] = newpath[n - 1 - i];
		newpath[n - 1 - i] = temp;
	}
	



	//0.0003s to 0.0004s 
	b->path = newpath;
	b->psize = n;
}
//Check collision 
bool isCollideEnemy(Enemy b, Vector2 o, float radius) 
{
	Rectangle r;
	r.x = b.pos.x;
	r.y = b.pos.y;
	r.width = b.tex.width;
	r.height = b.tex.height;



	return CheckCollisionCircleRec(o, radius, r);
}

void updateEnemies(Enemymanager *enemman,Base base , int* map, int mapwidth, int mapheight, int limit, int tilesize, float deltatime,Bulletmanager *bullman,Bulletmanager *allybullman)
{
	int moveret = 0;
	//Base rush logic
	int dx = base.ix;
	int dy = base.iy;
	int id = 0;
	
	while (id < enemman->n)
	{
	
		//enemman.Enemies[id];
		float diff = getdist(enemman->Enemies[id].pos.x, enemman->Enemies[id].pos.y, dx * tilesize, dy * tilesize);

		//MOVING PART
		//If distance is less than 0.1 tiles;
		if (diff > (0.1 * tilesize))
		{
		
			if (enemman->Enemies[id].psize == 0)
			{

				updatepath(&enemman->Enemies[id], dx, dy, map, mapwidth, mapheight, limit);
			
			}
			
			else if (map[(int)enemman->Enemies[id].path[0].y * mapwidth + (int)enemman->Enemies[id].path[0].x] != 0)
			{
				Vector2 oldpath = enemman->Enemies[id].path[0];

				if (enemman->Enemies[id].stuck <= 0)
				{
					updatepath(&enemman->Enemies[id], dx, dy, map, mapwidth, mapheight, limit);

					if (oldpath.x == enemman->Enemies[id].path[0].x && oldpath.y == enemman->Enemies[id].path[0].y)
					{
						enemman->Enemies[id].stuck = 100;
					}
				}
				//Wait for 100 frames before checking again
				enemman->Enemies[id].stuck -= 1;
			}


			else
			{
				enemman->Enemies[id].stuck = 0;
				enemman->Enemies[id].dest.x = tilesize * enemman->Enemies[id].path[0].x;
				enemman->Enemies[id].dest.y = tilesize * enemman->Enemies[id].path[0].y;
				moveret = moveEnemy(&enemman->Enemies[id], deltatime, tilesize);
			}

			if (moveret == -1)
			{
				for (int i = 1; i < enemman->Enemies[id].psize; i++)
				{
					enemman->Enemies[id].path[i - 1] = enemman->Enemies[id].path[i];
				}
				enemman->Enemies[id].psize -= 1;
				enemman->Enemies[id].path = realloc(enemman->Enemies[id].path, enemman->Enemies[id].psize * sizeof(Vector2));
			}
		}
		
		//SHOOTING PART

		if (enemman->Enemies[id].time_to_reload <= 0)
		{
			//Predefining a bullet here
			Bullet p;
			//Pos is same as current pos
			p.pos = enemman->Enemies[id].pos;
			//A small offset
			p.pos.x += enemman->Enemies[id].tex.width / 2.0 * enemman->Enemies[id].scale;
			p.pos.y += enemman->Enemies[id].tex.height / 2.0 * enemman->Enemies[id].scale;


			p.dmg = enemman->Enemies[id].dmg;
			p.scale = 1.0;
			p.velocity = 2500;
			p.tex = BulletTexture;
			p.range = enemman->Enemies[id].range + 0.5;
			p.trace = 0;
			//Shoot at base
			if (diff < enemman->Enemies[id].range * tilesize)
			{
				Vector2 shootpos;
				shootpos.x = base.pos.x + base.tex.width / 2;
				shootpos.y = base.pos.x + base.tex.height / 2;
				//Shoot at the base
				p.dir = unit(p.pos, shootpos);
				pushBulletManager(bullman, p);
				enemman->Enemies[id].time_to_reload = enemman->Enemies[id].reload;
			}

			//It is stuck
			else if (enemman->Enemies[id].stuck > 0)
			{
				//Shoot at next wall
				Vector2 wallclear;
				wallclear.x = enemman->Enemies[id].path[0].x * tilesize;
				wallclear.y = enemman->Enemies[id].path[0].y * tilesize;

				p.dir = unit(p.pos, wallclear);

				//Push Back
				pushBulletManager(bullman, p);
				enemman->Enemies[id].time_to_reload = enemman->Enemies[id].reload;
			}
		}
		else
		{
			enemman->Enemies[id].time_to_reload -= deltatime;
		}

		//Taking damage
		int j = 0;
		//Checking damage for every bullet
		while (j < allybullman->n)
		{
			if (isCollideEnemy(enemman->Enemies[id],allybullman->Bullets[j].pos,5))
			{
				enemman->Enemies[id].health -= allybullman->Bullets[j].dmg;
				deleteindexBulletManager(allybullman, j);;
			}

			else
			{
				j++;
			}
		}

		//Destroying enemies with <= 0 health
		if (enemman->Enemies[id].health <= 0)
		{
			deleteindexEnemyManager(enemman, id);
		}
		else
		{
			id++;
		}
	}
}

//Enemy list functions
//Push function for the Enemymanager
void pushEnemyManager(Enemymanager* enemman,Enemy t)
{
	//We append the size of our manager by 1 if there is something already
	if (enemman->n > 0)
	{
		enemman->n += 1;

		//We allocate excess memory
		enemman->Enemies = (Enemy*)realloc(enemman->Enemies, enemman->n * sizeof(Enemy));

		//We set the new element to t
		enemman->Enemies[enemman->n - 1] = t;
	}
	//else define a new pointer
	else
	{
		enemman->n += 1;

		//We allocate a new pointer
		enemman->Enemies = (Enemy*)malloc(enemman->n * sizeof(Enemy));

		//We set the new element to t
		enemman->Enemies[enemman->n - 1] = t;
	}
}

//Delete function
void deleteindexEnemyManager(Enemymanager* t, int i)
{

	for (int j = i + 1; j < t->n; j++)
	{
		t->Enemies[j - 1] = t->Enemies[j];

	}

	t->n -= 1;
	//We reduce memory
	t->Enemies = (Enemy*)realloc(t->Enemies, t->n * sizeof(Enemy));

}