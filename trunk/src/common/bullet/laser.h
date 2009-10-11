#ifndef LASER_H
#define LASER_H

#include <bullet.h>

class laser : public ghost
{
public:
	laser(int type=0);
	void loop();
	void turn_on(int t=30);
	void turn_off(int t=30);
	float l1,l2,r,r0,node,aura_spin;
	DWORD c;
	int _type,turn_on_sts,turn_on_time,turn_off_sts,turn_off_time;
	void draw();
	bool has_aura;
};

#endif