#ifndef CANNON_H
#define CANNON_H

#include <bullet.h>

class cannon : public ghost
{
public:
	float _vx,_vy,_g;
	cannon(float x0,float vx,float vy,float g);
	void loop();
};

class cartridge : public enemy_bullet
{
public:
	float _vx,_vy,_g;
	cartridge(int type,int delay,float x0,float y0,float vx,float vy,float g);
	void loop();
};

#endif
