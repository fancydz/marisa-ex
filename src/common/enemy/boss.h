#ifndef BOSS_H
#define BOSS_H

#include <bullet.h>

#define SC_OS 10000

class boss : public enemy
{
public:
	boss(float x0,float y0);
	~boss();
	pic* stay_img[4];
	pic* move_img[4];
	pic* cast_img[4];
	int lr_status;
	int cast_status;
	int move_status;
	float x1,x2,y1,y2;
	int _time_spend;
	int draw_age;
	void draw();
	void loop();
	void cast();
	void move_to(float des_x,float des_y,int time_spend=60);
};

#endif
