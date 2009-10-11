#ifndef ITEM_H
#define ITEM_H

#include <bullet.h>

class item : public enemy_bullet
{
public:
	item(bullet* p);
	float _v0,_v1,_t0;
	bool attracted;
	float track_speed;
	void loop();
	void collide(bullet* sufferer);
};

class bullet_bonus : public item
{
public:
	int type;
	bullet_bonus(bullet* p);
	void collide(bullet* sufferer);
};

class bullet_corpse : public item
{
public:
	bullet_corpse(bullet* p);
	void collide(bullet* sufferer);
};

class point : public item
{
public:
	int type;
	point(bullet* p);
	void collide(bullet* sufferer);
	void loop();
};

#endif