#include "satellite_ghost.h"

satellite_ghost::satellite_ghost(bullet* _master,float start_rot,float r,float av,pic* image):minion(_master)
{
	suffer=false;
	x=r;
	_av=av/60.0;
	crot0=start_rot;
	if(image==0) image=res->img["minion"];
	img=image;
	layer=ENEMY_LAYER+1;
}

void satellite_ghost::loop()
{
	minion::loop();
	if(dead) return;
	cx=master->real_x;
	cy=master->real_y;
	crot=crot0+_av*age;
}
