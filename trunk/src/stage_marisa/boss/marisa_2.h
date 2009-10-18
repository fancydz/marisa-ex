#ifndef MARISA_2_H
#define MARISA_2_H

#include "marisa.h"
#include <common\bullet\laser.h>
#include <common\bullet\acc_str_bullet.h>
#include "..\stage_marisa_enemy.h"

class marisa_2 : public marisa
{
public:
	marisa_2(float x0,float y0);
	void loop();
	void sc_1(int t);
	void sc_2(int t);
	void sc_3(int t);
	void sc_4(int t);
	void sc_5(int t);
	void sc_6(int t);
	void sc_7(int t);
	void sc_8(int t);
	void sc_9(int t);
	void sc_10(int t);
	void nm_1(int t);
	void nm_2(int t);
	void nm_3(int t);
	void nm_4(int t);
	void nm_5(int t);
	void nm_6(int t);
	void nm_7(int t);
	void nm_8(int t);
	void nm_9(int t);
	void escape(int t);
	~marisa_2();
	void kill();
};

class marisa_2_1_laser : public laser
{
public:
	marisa_2_1_laser(int index);
	float x0;
	void loop();
};

class marisa_2_2_minion : public minion
{
public:
	marisa_2_2_minion(bullet* _master,int index);
	void loop();
};

class marisa_2_2_laser : public laser
{
public:
	marisa_2_2_laser(float x0,float y0);
	float node0;
	void loop();
};

class marisa_2_3_laser : public laser
{
public:
	marisa_2_3_laser(float x0,float y0,float rot0,int type);
	void loop();
};

class marisa_2_3_minion : public minion
{
public:
	marisa_2_3_minion(bullet* _master,int index);
	void loop();
};

class marisa_2_4_laser : public laser
{
public:
	marisa_2_4_laser(int index);
	int _index;
	void loop();
};

class marisa_2_4_star : public enemy_bullet
{
public:
	marisa_2_4_star(float rot0,float speed);
	float _speed;
	void loop();
};

class marisa_2_5_comet : public enemy_bullet
{
public:
	marisa_2_5_comet();
	void loop();
};

class marisa_2_6_bullet : public enemy_bullet
{
public:
	marisa_2_6_bullet(int index,float x0,float y0);
	int _type;
	int _index;
	void loop();
	void draw();
};

class marisa_2_6_minion : public laser
{
public:
	marisa_2_6_minion(float x0,int index);
	int _index;
	void loop();
};

class marisa_2_6_laser : public laser
{
public:
	marisa_2_6_laser(float x0,float y0,int type);
	void loop();
};

class marisa_2_6_cannon : public laser
{
public:
	marisa_2_6_cannon();
	void loop();
};

class marisa_2_7_laser : public laser
{
public:
	marisa_2_7_laser(int index);
	float rot_dir,crot0;
	void loop();
};

class marisa_2_7_bullet : public acc_str_bullet
{
public:
	marisa_2_7_bullet(float x0,float y0,float angle,float speed,pic* image,
	               bool aim,float acc,float vrot=0,
				   int _layer=ENEMY_BULLET_LAYER);
	void loop();
	float spin;
};

class marisa_2_8_laser : public laser
{
public:
	marisa_2_8_laser(float x0,float y0);
	void loop();
};

class marisa_2_9_minion : public laser
{
public:
	marisa_2_9_minion(float x0,float y0);
	void loop();
};

class marisa_2_9_laser : public laser
{
public:
	marisa_2_9_laser(float x0,float y0);
	void loop();
};

class marisa_2_10_bullet : public enemy_bullet
{
public:
	marisa_2_10_bullet(float x0,float y0,float angle,float speed,pic* image);
	float _vx,_vy,vxf,vyf,spin;
	void loop();
};

#endif
