#include "acc_str_bullet.h"

acc_str_bullet::acc_str_bullet(float x0,float y0,float angle,float speed,pic* image,
	                           bool aim,float acc,float vrot,
				               int _layer)
			   :straight_bullet(x0,y0,angle,speed,image,aim,_layer)
{
	_acc=acc/3600.0;
	_vrot=vrot/60.0;
	crot0=angle;
}

void acc_str_bullet::loop()
{
	x=age*_speed+0.5*age*age*_acc;
	crot=crot0+age*_vrot;
	rot=v2a(delta_x,delta_y)-crot;
}
