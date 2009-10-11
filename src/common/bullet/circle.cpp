#include "circle.h"
#include "straight_bullet.h"
#include <estg_math.h>
#include <ESTG.h>

circle::circle(float x0,float y0,float angle,float speed,pic* image,int num,bool aim,int _layer)
{
	int i;
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	if(num%2==0) angle+=2.0/num;
	for(i=0;i<num;i++)
		estg->add(new straight_bullet(x0,y0,angle+4.0/num*i,speed,image,false,0.0,0.0,0.0,_layer));
	dead=true;
}
