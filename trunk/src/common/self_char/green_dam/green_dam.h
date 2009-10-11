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

#endif
