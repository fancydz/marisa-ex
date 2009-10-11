#ifndef STAGE_MARISA_ENEMY_H
#define STAGE_MARISA_ENEMY_H

#include <bullet.h>
#include <common\enemy\girl.h>
#include <common\enemy\satellite_ghost.h>
#include <common\bullet\laser.h>

class stage_marisa_wave_0 : public girl
{
public:
	stage_marisa_wave_0(float xf,float yf,int stay=480,int fly_in=0,int fly_out=0);
	//fly in/out : 0 for horizontal, 1 for vertical
	float _stay;
	int in_mode,out_mode;
	void loop();
};

class stage_marisa_wave_1 : public girl
{
public:
	stage_marisa_wave_1(int delay,float fire_pos,int direction);
	void loop();
	int dir;
	float _fire_pos;
	bool fired;
	bool fired2;
};

class stage_marisa_wave_2 : public girl
{
public:
	stage_marisa_wave_2(int delay,int fire_time,int direction);
	void loop();
	int dir;
	int _fire_time;
	int fires;
};

class stage_marisa_wave_3_minion : public satellite_ghost
{
public:
	stage_marisa_wave_3_minion(bullet* master,int type,float start_angle);
	void loop();
	int _type;
};

class stage_marisa_wave_3 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_3(float xf,float yf);
	void loop();
};

class stage_marisa_wave_4_bullet : public enemy_bullet
{
public:
	stage_marisa_wave_4_bullet(float x0,float y0,float angle,float v0,float v1,float t0,pic* image);
	float _v0,_v1,_t0;
	void loop();
};

class  stage_marisa_wave_4 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_4(float xf,float yf);
	void loop(); 
};

class stage_marisa_wave_5_minion : public satellite_ghost
{
public:
	stage_marisa_wave_5_minion(bullet* master,float start_angle);
	void loop();
};

class stage_marisa_wave_5 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_5(float x0);
	void loop();
};

class stage_marisa_wave_6 : public girl
{
public:
	stage_marisa_wave_6(int type,int index);
	void loop();
	int _type;
	int _index;
};

class stage_marisa_wave_8 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_8(float xf,float yf,int stay=480);
	void loop();
};

class stage_marisa_wave_9 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_9(float xf,float yf,int stay=480);
	void loop();
};

class stage_marisa_wave_10 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_10(float xf,float yf,int stay=480);
	void loop();
};

class stage_marisa_wave_11 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_11(float xf,float yf,int stay=480);
	void loop();
};

class stage_marisa_wave_12 : public girl
{
public:
	stage_marisa_wave_12(int dir);
	int _dir;
	void loop();
};

class stage_marisa_wave_13 : public stage_marisa_wave_12
{
public:
	stage_marisa_wave_13(int dir,int fire);
	int _fire;
	void loop();
};

class  stage_marisa_wave_14 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_14(float xf,float yf,int stay=480);
	void loop(); 
};

class stage_marisa_wave_15_minion : public satellite_ghost
{
public:
	stage_marisa_wave_15_minion(bullet* master,float start_angle,float r,float av);
	void loop();
};

class stage_marisa_wave_15 : public stage_marisa_wave_0
{
public:
	stage_marisa_wave_15(float x0);
	void loop();
};

class test_laser : public laser
{
public:
	test_laser();
	void loop();
};

#endif
