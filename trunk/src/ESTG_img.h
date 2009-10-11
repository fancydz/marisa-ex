#ifndef ESTG_IMG_H
#define ESTG_IMG_H

#pragma warning(disable:4305 4244)

#include <hge.h>
#include <hgefont.h>
#include <hgeparticle.h>

#define RESOLUTION_X 640
#define RESOLUTION_Y 480

#define X_STRETCH (RESOLUTION_Y*5/6.0)
#define Y_STRETCH (-RESOLUTION_Y*5/6.0)

class pic : public hgeSprite
{
public:
	float a,b;
	float r;
	bool rect;
	bool no_rot;
	hgeParticleSystem* ps;
	pic(HTEXTURE tex,float x,float y,float w,float h,float _a=0.0,float _b=0.0,bool _no_rot=false,bool _rect=false);
	pic(HTEXTURE tex,float x,float y,float w,float h,char* pfile,float _a=0.0,float _b=0.0,bool _rect=false);
	void set_ab(float _a,float _b,bool _rect=false);
};

extern HGE* hge;

#endif
