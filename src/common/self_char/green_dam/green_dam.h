#ifndef GREEN_DAM_H
#define GREEN_DAM_H

#include "..\\self_char.h"
#include "..\\straight_self_bullet.h"

#define GREEN_DAM 0

class green_dam : public self_char
{
public:
	green_dam();
	~green_dam();
	float minion_x,minion_y;
	void fire();
	void draw();
	void bomb();
	void loop();
};

class green_dam_bullet : public straight_self_bullet
{
public:
	green_dam_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic* image,float delay=0.0);
	void collide(bullet* sufferer);
};

class green_dam_bomb : public ether
{
public:
	green_dam_bomb();
	float clear_r;
	void loop();
};

class green_dam_bomb_bullet : public green_dam_bullet
{
public:
	green_dam_bomb_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic* image,float delay=0.0);
	void loop();
};

#endif
