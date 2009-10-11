#ifndef MARISA_BG_H
#define MARISA_BG_H

#include <bullet.h>
#include <list>
#include <ESTG.h>

class marisa_bg : public back_ground
{
public:
	marisa_bg();
	pic* img2;
	int p;
	void draw(float fade);
};

class tree_c
{
public:
	tree_c(int _type,float _x,float _y,float _z,float _rot);
	float x,y,z,rot;
	int type;// 0 for trunk,1,2 for left leaf, 3,4 for right leaf.
};

class road_bg : public back_ground
{
public:
	road_bg();
	~road_bg();
	float speed;
	float s;
	float fog_a;
	float fog_b;
	void loop();
	pic* img_trunk;
	pic* img_leaf_1;
	pic* img_leaf_2;
	pic* img_ground[2][2];
	float ground;
	int ground_flag;
	list<tree_c*> tree;
	inline float conv_x(float x3d,float y3d,float z3d){return x2scr(s*((x3d+cx)/z3d+x));}
	inline float conv_y(float x3d,float y3d,float z3d){return y2scr(s*((y3d+cy)/z3d+y));}
	inline int z2alpha(float z3d)
	{
		int alpha;
		alpha=(int)(255.0/exp(fog_a*z3d+fog_b));
		if(alpha>255) alpha=255;
		return (0xFF000000)|(alpha)|(alpha<<8)|(alpha<<16);
	}
	void draw(float fade);
	void draw_ground(int i,int j);
};

#endif
