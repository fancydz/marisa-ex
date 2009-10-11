#ifndef MARISA_1_H
#define MARISA_1_H

#include "marisa.h"
#include <common\enemy\minion.h>
#include "..\stage_marisa_enemy.h"

class marisa_1 : public marisa
{
public:
	marisa_1(float x0,float y0);
	void loop();
	void sc_1(int t);
	void sc_2(int t);
	void sc_3(int t);
	void escape(int t);
	~marisa_1();
	void kill();
};

class marisa_1_2_minion : public enemy
{
public:
	marisa_1_2_minion(int index);
	void loop();
	int img_index;
	float vita;
};

class marisa_1_2_bullet : public stage_marisa_wave_4_bullet
{
public:
	marisa_1_2_bullet(float x0,float y0,float angle,float v0,float v1,float t0,pic* image,float av=0.03);
	float _av;
	void loop();
};

class marisa_1_3_minion : public enemy_bullet
{
public:
	marisa_1_3_minion(int index,bool aim);
	void loop();
	int img_index;
	float x0,x1;
};

#endif
