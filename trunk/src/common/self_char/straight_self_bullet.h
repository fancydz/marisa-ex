#ifndef STRAIGHT_SELF_BULLET
#define STRAIGHT_SELF_BULLET

#include <bullet.h>

class straight_self_bullet : public self_bullet
{
public:
	float _speed,startx,starty;
	int _type;
	straight_self_bullet(int type,float dmg,float x0,float y0,float angle,float speed,pic* image,float delay=0.0);
	void loop();
	void aim();
};

#endif
