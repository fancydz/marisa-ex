#ifndef GRAV_BULLET_H
#define GRAV_BULLET_H

#include<bullet.h>

class grav_bullet : public enemy_bullet
{
public:
	grav_bullet(float x0,float y0,float vx0,float vy0,pic* image,float g=-0.3);
	float _vx,_vy,_g;
	void loop();
};

#endif
