#include "ESTG_img.h"
#include <estg_math.h>

pic::pic(HTEXTURE tex,float x,float y,float w,float h,float _a,float _b,bool _no_rot,bool _rect):hgeSprite(tex,x,y,w,h)
{
	SetHotSpot(w/2.0,h/2.0);
	a=_a/X_STRETCH;b=_b/X_STRETCH;rect=_rect;no_rot=_no_rot;
	r=sqrt(a*a+b*b)*1.1;
	ps=0;
}

pic::pic(HTEXTURE tex,float x,float y,float w,float h,char* pfile,float _a,float _b,bool _rect):hgeSprite(tex,x,y,w,h)
{
	SetHotSpot(w/2.0,h/2.0);
	a=_a/X_STRETCH;b=_b/X_STRETCH;rect=_rect;
	r=sqrt(a*a+b*b)*1.1;
	ps=0;
	ps=new hgeParticleSystem((hgeParticleSystemInfo*)hge->Resource_Load(pfile));
#pragma warning(disable:4311)
	SetBlendMode(((DWORD)(ps->info.sprite))>>16);
#pragma warning(default:4311)
	ps->info.sprite=this;
}

void pic::set_ab(float _a,float _b,bool _rect)
{
	a=_a/X_STRETCH;b=_b/X_STRETCH;rect=_rect;
	r=sqrt(a*a+b*b)*1.1;
}
