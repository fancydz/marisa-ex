#ifndef STRAIGHT_BULLET_H
#define STRAIGHT_BULLET_H
#include <bullet.h>

#define MAX_ANGLE 999.0

class straight_bullet : public enemy_bullet
{
public:
	float _speed,_spin,_rot;
	straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                bool aim,float delay,float spin,float rot0,
					int _layer=ENEMY_BULLET_LAYER);
	straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                bool aim,float delay,float spin,
					int _layer=ENEMY_BULLET_LAYER);
	straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                bool aim,float delay,
					int _layer=ENEMY_BULLET_LAYER);
	straight_bullet(float x0,float y0,float angle,float speed,pic* image,
	                bool aim,
					int _layer=ENEMY_BULLET_LAYER);
	straight_bullet(float x0,float y0,float angle,float speed,pic* image,
					int _layer=ENEMY_BULLET_LAYER);
	void loop();
};

#endif
