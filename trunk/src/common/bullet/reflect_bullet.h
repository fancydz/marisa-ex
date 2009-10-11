#ifndef REFLECT_BULLET_H
#define REFLECT_BULLET_H
#include "straight_bullet.h"

class reflect_bullet : public straight_bullet
{
public:
	reflect_bullet(float x0,float y0,float angle,float speed,pic* image,
	               int reflects=0xFFFF,bool aim=false,float delay=0,float spin=0,float rot0=0,
				   int _layer=ENEMY_BULLET_LAYER);
	virtual void reflect(int border);
	int _reflects;
	void loop();
};

#endif
