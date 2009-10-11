#ifndef CIRCLE_H
#define CIRCLE_H

#include <bullet.h>

class circle : public ether
{
public:
	circle(float x0,float y0,float angle,float speed,pic* image,
	       int num,bool aim=false,int _layer=ENEMY_BULLET_LAYER);
};

#endif
