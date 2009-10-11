#ifndef BULLET_H
#define BULLET_H

#pragma warning(disable:4305 4244)

#include <hge.h>
#include <hgefont.h>

#include <list>
#include <estg_math.h>

#include <common\common_res.h>

#define PLAY_AREA_X 0.5
#define PLAY_AREA_Y 0.6

#define OUTER_PLAY_AREA_X 0.6
#define OUTER_PLAY_AREA_Y 0.7

#define MAX_LAYER 16
#define BG_LAYER 1
#define ENEMY_LAYER 4
#define SELF_LAYER 7
#define SELF_BULLET_LAYER 10
#define ENEMY_BULLET_LAYER 13
#define MASK_LAYER 15

#define ENEMY_BULLET 3
#define ENEMY 1
#define SELF_BULLET 2
#define SELF 0
#define GHOST 4
#define MAX_ATTR 5

#define MAX_HP 9999.9

using namespace std;

class bullet
{
public:
	pic* img;
	hgeParticleSystem* ps;
	int age;
	bool hide;
	bool dead;
	bool attack;
	bool suffer;
	bool hostile;
	int attr;
	int layer;
	float x,y,rot;
	float cx,cy,crot;
	float scale;
	float real_x,real_y;
	float delta_x,delta_y;
	float hp;
	float dmg_factor;
	int drop_num;
	bool auto_clear;
	char* label;
	bool grazed;
	list<bullet*>::iterator it;
	bullet* master;
	bullet();
	void update_xy();
	virtual void destroy();
	virtual void kill();
	virtual void draw();
	virtual void loop();
	virtual void collide(bullet* sufferer);
	virtual ~bullet()=0;
};

class ghost : public bullet
{
public:
	ghost();
};

class ether : public ghost
{
public:
	ether();
};

class self_bullet : public bullet
{
public:
	self_bullet();
	void collide(bullet* sufferer);
};

class enemy_bullet : public bullet
{
public:
	enemy_bullet();
	void collide(bullet* sufferer);
	void kill();
};

class enemy : public bullet
{
public:
	enemy();
	void kill();
	void drop_point(int num);
};

class back_ground : public ether
{
public:
	virtual void draw(float fade)=0;
};

extern cres* res;

class ps_agent : public ether
{
public:
	ps_agent(bullet* principal);
	void draw();
	void loop();
};

#endif
