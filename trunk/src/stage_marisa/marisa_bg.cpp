#include "marisa_bg.h"
#include <ESTG.h>

#include <iostream>
using namespace std;

marisa_bg::marisa_bg()
{
	img =estg->sres.img["marisa_bg1"];
	img2=estg->sres.img["marisa_bg2"];
	p=90;
	layer=1;
}

void marisa_bg::draw(float fade)
{
	if(fade<1e-3) return;
	float t=-double(age%p)/p;
	img->SetColor(((int(fade*255))<<24)|0x00FFFFFF);
	img2->SetColor(((int(fade*255))<<24)|0x00FFFFFF);
	img->RenderStretch(0,0,400,480);
	img2->RenderStretch(0,t*256,256,256+t*256);
	img2->RenderStretch(256,t*256,512,256+t*256);
	img2->RenderStretch(0,256+t*256,256,512+t*256);
	img2->RenderStretch(256,256+t*256,512,512+t*256);
	img2->RenderStretch(0,512+t*256,256,768+t*256);
	img2->RenderStretch(256,512+t*256,512,768+t*256);
}

tree_c::tree_c(int _type,float _x,float _y,float _z,float _rot)
{
	x=_x;
	y=_y;
	z=_z;
	rot=_rot;
	type=_type;
}

road_bg::road_bg()
{
	layer=0;
	img_trunk=estg->sres.img["trunk"];
	img_leaf_1=estg->sres.img["leaf_1"];
	img_leaf_2=estg->sres.img["leaf_2"];
	img_ground[0][0]=estg->sres.img["ground0"];
	img_ground[0][1]=estg->sres.img["ground1"];
	img_ground[1][0]=estg->sres.img["ground2"];
	img_ground[1][1]=estg->sres.img["ground3"];
	s=2.0;
	x=0.0;
	y=0.25;
	cy=-2.0;
	fog_a=0.7;
	fog_b=-5.0;
	speed=0.05;
	ground=5.0;
	ground_flag=0;
	int i;
	for(i=0;i<900;i++)
	{
		loop();
		age++;
	}
}

road_bg::~road_bg()
{
	list<tree_c*>::iterator iter;
	for(iter=tree.begin();iter!=tree.end();)
	{
		delete (*iter);
		iter=tree.erase(iter);
	}
}


void road_bg::loop()
{
	//
	speed=estg->sres.val["bg_speed"];
	//
	x=0.05*sin(age/120.0);
	cx=0.1*cos(age/120.0);
	/*
	if(hge->Input_GetKeyState(HGEK_1)) y+=0.01;
	if(hge->Input_GetKeyState(HGEK_2)) y-=0.01;
	if(hge->Input_GetKeyState(HGEK_3)) cy+=0.01;
	if(hge->Input_GetKeyState(HGEK_4)) cy-=0.01;
	cout<<"y="<<y<<" cy="<<cy<<endl;
	*/
	//cx=-0.4*estg->self->x;

	/*if(age%20==0)
		tree.push_front(new tree_c(0,hge->Random_Float(-1.2,-0.5),0.0,15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.2,0.0)));
	if(age%20==10)
		tree.push_front(new tree_c(0,hge->Random_Float(+0.5,+1.2),0.0,15+hge->Random_Float(-0.2,0.2),hge->Random_Float(0.0,+0.2)));
	if(age%20==0)
		tree.push_front(new tree_c(hge->Random_Int(1,2),hge->Random_Float(-1.5,-0.9),hge->Random_Float(1.0,2.0),15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.3,0.3)));
	if(age%20==10)
		tree.push_front(new tree_c(hge->Random_Int(3,4),hge->Random_Float(+0.9,+1.5),hge->Random_Float(1.0,2.0),15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.3,0.3)));
	*/

	if(age%(int(1/speed))==0)
	{
		tree.push_front(new tree_c(0,hge->Random_Float(-1.2,-0.5),0.0,15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.2,0.0)));
		tree.push_front(new tree_c(0,hge->Random_Float(+0.5,+1.2),0.0,15+hge->Random_Float(-0.2,0.2),hge->Random_Float(0.0,+0.2)));
		tree.push_front(new tree_c(hge->Random_Int(1,2),hge->Random_Float(-1.5,-0.9),hge->Random_Float(1.0,2.0),15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.3,0.3)));
		tree.push_front(new tree_c(hge->Random_Int(3,4),hge->Random_Float(+0.9,+1.5),hge->Random_Float(1.0,2.0),15+hge->Random_Float(-0.2,0.2),hge->Random_Float(-0.3,0.3)));
	}
	list<tree_c*>::iterator iter;
	for(iter=tree.begin();iter!=tree.end();)
	{
		(*iter)->z-=speed;
		if((*iter)->z<0.5)
		{
			delete (*iter);
			iter=tree.erase(iter);
			continue;
		}
		iter++;
	}
	ground-=speed;
	if(ground<3.0)
	{
		ground+=1.5;
		ground_flag++;
	}
}

void road_bg::draw_ground(int i,int j)
{
	img_ground[(i+10)%2][(j+ground_flag)%2]->SetColor(z2alpha(ground+j*1.5),0);
	img_ground[(i+10)%2][(j+ground_flag)%2]->SetColor(z2alpha(ground+j*1.5),1);
	img_ground[(i+10)%2][(j+ground_flag)%2]->SetColor(z2alpha(ground+j*1.5-1.5),2);
	img_ground[(i+10)%2][(j+ground_flag)%2]->SetColor(z2alpha(ground+j*1.5-1.5),3);
	
	img_ground[(i+10)%2][(j+ground_flag)%2]->Render4V(
	conv_x(-0.5+i,0,ground+j*1.5),conv_y(-0.5+i,0,ground+j*1.5),
	conv_x(+0.5+i,0,ground+j*1.5),conv_y(+0.5+i,0,ground+j*1.5),
	conv_x(+0.5+i,0,ground-2+j*1.5),conv_y(+0.5+i,0,ground-1.5+j*1.5),
	conv_x(-0.5+i,0,ground-2+j*1.5),conv_y(-0.5+i,0,ground-1.5+j*1.5)
	);
}

void road_bg::draw(float fade)
{
	if(fade<1e-3) return;
	hge->Gfx_Clear(0xFF000000);
	int i,j;
	for(i=-2;i<3;i++)
		for(j=0;j<6;j++)
			draw_ground(i,j);
	list<tree_c*>::iterator iter;
	for(iter=tree.begin();iter!=tree.end();iter++)
	{
		if((*iter)->type==0)
		{
			img_trunk->SetColor(z2alpha((*iter)->z));
			img_trunk->RenderEx(conv_x((*iter)->x,(*iter)->y,(*iter)->z),conv_y((*iter)->y,(*iter)->y,(*iter)->z),M_PI+(*iter)->rot,2.0*s/((*iter)->z));
		}
		if((*iter)->type==1)
		{
			img_leaf_1->SetFlip(false,false);
			img_leaf_1->SetColor(z2alpha((*iter)->z));
			img_leaf_1->RenderEx(conv_x((*iter)->x,(*iter)->y,(*iter)->z),conv_y((*iter)->y,(*iter)->y,(*iter)->z),(*iter)->rot,2.0*s/((*iter)->z));
		}
		if((*iter)->type==2)
		{
			img_leaf_2->SetFlip(true,false);
			img_leaf_2->SetColor(z2alpha((*iter)->z));
			img_leaf_2->RenderEx(conv_x((*iter)->x,(*iter)->y,(*iter)->z),conv_y((*iter)->y,(*iter)->y,(*iter)->z),(*iter)->rot,2.0*s/((*iter)->z));
		}
		if((*iter)->type==3)
		{
			img_leaf_2->SetFlip(false,false);
			img_leaf_2->SetColor(z2alpha((*iter)->z));
			img_leaf_2->RenderEx(conv_x((*iter)->x,(*iter)->y,(*iter)->z),conv_y((*iter)->y,(*iter)->y,(*iter)->z),(*iter)->rot,2.0*s/((*iter)->z));
		}
		if((*iter)->type==4)
		{
			img_leaf_1->SetFlip(true,false);
			img_leaf_1->SetColor(z2alpha((*iter)->z));
			img_leaf_1->RenderEx(conv_x((*iter)->x,(*iter)->y,(*iter)->z),conv_y((*iter)->y,(*iter)->y,(*iter)->z),(*iter)->rot,2.0*s/((*iter)->z));
		}
	}
}
