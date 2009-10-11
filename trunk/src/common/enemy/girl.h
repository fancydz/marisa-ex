#ifndef GIRL_H
#define GIRL_H

#include <bullet.h>
#include <vector>

#define SLOPE_SPEED 0.004

class girl : public enemy
{
public:
	int _type;
	bool _aura;
	girl(int type=0,bool aura=false);
	void draw();
};

#endif
