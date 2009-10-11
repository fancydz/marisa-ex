#ifndef BUBBLE_H
#define BUBBLE_H
#include <bullet.h>

class bubble : public ghost
{
public:
	bubble(float x0,float y0,pic* image,int life_time,float start_size,float end_size,DWORD start_color,DWORD end_color,int _layer=MASK_LAYER);
	void loop();
	void draw();
	int life;
	float s1,s2;
	DWORD c1,c2;
};

#endif
