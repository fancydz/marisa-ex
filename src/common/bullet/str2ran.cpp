#include "str2ran.h"

str2ran::str2ran(float x0,float y0,float angle,float speed,pic* image,bool aim,float trans_time,int _layer)
:straight_bullet(x0,y0,angle,speed,image,aim,_layer)
{
	trans=(int)trans_time;
	trans_flag=false;
}

void str2ran::loop()
{
	if(age==trans&&(!trans_flag))
	{
		trans_flag=true;
		crot=hge->Random_Float(0,4.0);
		cx=real_x;
		cy=real_y;
		x=y=rot=0;
		age=1;
	}
	straight_bullet::loop();
}
