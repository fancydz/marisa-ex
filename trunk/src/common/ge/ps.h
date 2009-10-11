#ifndef PS_H
#define PS_H

#include <bullet.h>

class ge_ps : public ghost
{
public:
	ge_ps(pic* image,float x0,float y0,int _layer=BG_LAYER,int life_time=120);
	int _life_time;
	void loop();
};

#endif
