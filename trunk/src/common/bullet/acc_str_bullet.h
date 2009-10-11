#ifndef ACC_STR_BULLET_H
#define ACC_STR_BULLET_H

#include <bullet.h>
#include "straight_bullet.h"

class acc_str_bullet : public straight_bullet
{
public:
	acc_str_bullet(float x0,float y0,float angle,float speed,pic* image,
	               bool aim,float acc,float vrot=0,
				   int _layer=ENEMY_BULLET_LAYER);
	void loop();
	float _acc,_vrot,crot0;
};

#endif
