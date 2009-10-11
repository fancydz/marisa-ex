#ifndef GREEN_DAM_BULLET_B_H
#define GREEN_DAM_BULLET_B_H

#include <bullet.h>

class green_dam_bullet_B : public self_bullet
{
public:
	double _speed,startx,starty;
	int _type;
	green_dam_bullet_B(int type,double dmg,double x0,double y0,double angle,double speed,pic* image,double delay=0.0);
	void loop();
	void aim();
};

#endif
