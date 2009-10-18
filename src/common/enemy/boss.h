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
	void kill();
	bool hide_info;
	struct sc_info_t
	{
		float max_hp;
		float time_1;
		float time_2;
		float time_3;
	} sc_info;
	void move_to(float des_x,float des_y,int time_spend=60);
	bool time_warner_created;
	int score_save;
	void start_card();
	void end_card();
};

class time_warner : public ether
{
public:
	time_warner();
	void loop();
};

#endif
