#ifndef STR2RAN_H
#define STR2RAN_H

#include "straight_bullet.h"

class str2ran : public straight_bullet
{
public:
	str2ran(float x0,float y0,float angle,float speed,pic* image,bool aim,float trans_time,int _layer=ENEMY_BULLET_LAYER);
	int trans;
	bool trans_flag;
	void loop();
};

#endif
