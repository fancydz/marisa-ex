#include "marisa.h"
#include <ESTG.h>

marisa::marisa(float x0,float y0):boss(x0,y0)
{
	int i;
	for(i=0;i<4;i++)
	{
		stay_img[i]=new pic(estg->sres.TEX["marisa_boss"],64*i,0,64,80);
		move_img[i]=new pic(estg->sres.TEX["marisa_boss"],64*i,80,64,80);
		cast_img[i]=new pic(estg->sres.TEX["marisa_boss"],64*i,160,64,80);
	}
}

marisa::~marisa()
{
	int i;
	for(i=0;i<4;i++)
	{
		delete stay_img[i];
		delete move_img[i];
		delete cast_img[i];
	}
}
