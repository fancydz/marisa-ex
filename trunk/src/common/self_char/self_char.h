#ifndef SELF_CHAR_H
#define SELF_CHAR_H

#include <bullet.h>

#define SELF_STARTX 0.0
#define SELF_STARTY -0.4

#define SELF_X_BORDER 0.46
#define SELF_Y_BORDER 0.54

#define AURA1_ROT_SPEED -0.1
#define AURA2_ROT_SPEED 0.05

#define LH_TRANSITION_TIME 12

class self_char : public bullet
{
public:
	self_char();
	~self_char();
	bool slow;
	bool no_bomb;
	int inv_sts;
	void inv(int t=60);
	int cd;
	int current_cd; 
	virtual void fire()=0;
	virtual void bomb()=0;
	virtual void miss();
	void act();
	void find_tar();
	float high_speed,low_speed;
	int lr_status,lh_status;
	float aura1_rot,aura2_rot;
	float sts;
	pic* aura1_img;
	pic* aura2_img;
	pic* f1[4][2];
	pic* f2[2];
	pic* f3[2];
	pic* f4[2];
	pic* f5[4][2];
	HTEXTURE char_tex;
	void draw();
	resource sres;
};

#endif
