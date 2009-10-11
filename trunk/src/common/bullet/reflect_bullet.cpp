#include "reflect_bullet.h"

using namespace std;

reflect_bullet::reflect_bullet(float x0,float y0,float angle,float speed,pic* image,
                               int reflects,bool aim,float delay,float spin,float rot0,int _layer)
:straight_bullet(x0,y0,angle,speed,image,aim,delay,spin,rot0,_layer)
{
	_reflects=reflects;
}

void reflect_bullet::loop()
{
	straight_bullet::loop();
	if((_reflects&0xF000)&&(real_y > PLAY_AREA_Y)){crot= -crot;cy= 2*PLAY_AREA_Y-cy;reflect(0xF000);}
	if((_reflects&0x0F00)&&(real_y <-PLAY_AREA_Y)){crot= -crot;cy=-2*PLAY_AREA_Y-cy;reflect(0x0F00);}
	if((_reflects&0x00F0)&&(real_x <-PLAY_AREA_X)){crot=2-crot;cx=-2*PLAY_AREA_X-cx;reflect(0x00F0);}
	if((_reflects&0x000F)&&(real_x > PLAY_AREA_X)){crot=2-crot;cx= 2*PLAY_AREA_X-cx;reflect(0x000F);}
}

void reflect_bullet::reflect(int border)
{
	_reflects&=(~border);
}
