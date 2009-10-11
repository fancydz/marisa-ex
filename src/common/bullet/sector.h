#ifndef SECTOR_H
#define SECTOR_H

#include <bullet.h>
#include <ESTG.h>
#include "straight_bullet.h"

#include <iostream>
using namespace std;

template <class T=straight_bullet>
class sector : public ether
{
public:
	sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	       int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
		   float p1,float h_p1,float v_p1,
		   float p2,float h_p2,float v_p2,
		   float p3,float h_p3,float v_p3,
		   int _layer=ENEMY_BULLET_LAYER);
	sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	       int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
		   float p1,float h_p1,float v_p1,
		   float p2,float h_p2,float v_p2,
		   int _layer=ENEMY_BULLET_LAYER);
	sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	       int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
		   float p1,float h_p1,float v_p1,
		   int _layer=ENEMY_BULLET_LAYER);
	sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	       int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
		   int _layer=ENEMY_BULLET_LAYER);
};

//T with 3 addtional parameters.
template <class T>
sector<T>::sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	              int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
				  float p1,float h_p1,float v_p1,
				  float p2,float h_p2,float v_p2,
				  float p3,float h_p3,float v_p3,
				  int _layer)
{
	if(fabs(angle)>MAX_ANGLE) angle=hge->Random_Float(0.0,4.0);
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	angle-=((hor-1)*h_angle/2+(ver-1)*v_angle/2);
	speed-=((hor-1)*h_speed/2+(ver-1)*v_speed/2);
	p1-=((hor-1)*h_p1/2+(ver-1)*v_p1/2);
	p2-=((hor-1)*h_p2/2+(ver-1)*v_p2/2);
	p3-=((hor-1)*h_p3/2+(ver-1)*v_p3/2);
	int i,j;
	for(i=0;i<hor;i++)
		for(j=0;j<ver;j++)
			estg->add(new T(x0,y0,angle+i*h_angle+j*v_angle,speed+i*h_speed+j*v_speed,image,false,
			p1+i*h_p1+j*v_p1,p2+i*h_p2+j*v_p2,p3+i*h_p3+j*v_p3,_layer));
	dead=true;
}

//T with 2 addtional parameters.
template <class T>
sector<T>::sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	              int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
				  float p1,float h_p1,float v_p1,
				  float p2,float h_p2,float v_p2,
				  int _layer)
{
	if(fabs(angle)>MAX_ANGLE) angle=hge->Random_Float(0.0,4.0);
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	angle-=((hor-1)*h_angle/2+(ver-1)*v_angle/2);
	speed-=((hor-1)*h_speed/2+(ver-1)*v_speed/2);
	p1-=((hor-1)*h_p1/2+(ver-1)*v_p1/2);
	p2-=((hor-1)*h_p2/2+(ver-1)*v_p2/2);
	int i,j;
	for(i=0;i<hor;i++)
		for(j=0;j<ver;j++)
			estg->add(new T(x0,y0,angle+i*h_angle+j*v_angle,speed+i*h_speed+j*v_speed,image,false,
			p1+i*h_p1+j*v_p1,p2+i*h_p2+j*v_p2,_layer));
	dead=true;
}

//T with 1 addtional parameter.
template <class T>
sector<T>::sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	              int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
				  float p1,float h_p1,float v_p1,
				  int _layer)
{
	if(fabs(angle)>MAX_ANGLE) angle=hge->Random_Float(0.0,4.0);
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	angle-=((hor-1)*h_angle/2+(ver-1)*v_angle/2);
	speed-=((hor-1)*h_speed/2+(ver-1)*v_speed/2);
	p1-=((hor-1)*h_p1/2+(ver-1)*v_p1/2);
	int i,j;
	for(i=0;i<hor;i++)
		for(j=0;j<ver;j++)
			estg->add(new T(x0,y0,angle+i*h_angle+j*v_angle,speed+i*h_speed+j*v_speed,image,false,
			p1+i*h_p1+j*v_p1,_layer));
	dead=true;
}

//T without any addtional parameters.
template <class T>
sector<T>::sector(float x0,float y0,float angle,float speed,pic* image,bool aim,
	              int hor,int ver,float h_angle,float v_angle,float h_speed,float v_speed,
				  int _layer)
{
	if(fabs(angle)>MAX_ANGLE) angle=hge->Random_Float(0.0,4.0);
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	angle-=((hor-1)*h_angle/2+(ver-1)*v_angle/2);
	speed-=((hor-1)*h_speed/2+(ver-1)*v_speed/2);
	int i,j;
	for(i=0;i<hor;i++)
		for(j=0;j<ver;j++)
			estg->add(new T(x0,y0,angle+i*h_angle+j*v_angle,speed+i*h_speed+j*v_speed,image,false,
			_layer));
	dead=true;
}

/*sector::sector(float x0,float y0,float angle,float speed,pic* image,
	           int hor,float hor_int,int ver,float ver_int,
		       bool aim,float tilt,float spin,int _layer)
{
	if(aim) angle+=v2a(estg->self->x-x0,estg->self->y-y0);
	angle-=((hor-1)*hor_int/2);
	speed-=((ver-1)*ver_int/2+(hor-1)*tilt/2);
	int i,j;
	for(i=0;i<hor;i++)
		for(j=0;j<ver;j++)
			estg->add(new straight_bullet(x0,y0,angle+i*hor_int,speed+j*ver_int+i*tilt,image,false,0,spin,_layer));
	dead=true;
}*/
#endif
