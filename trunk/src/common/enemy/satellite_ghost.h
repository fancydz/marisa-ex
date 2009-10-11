#ifndef SATELLITE_GHOST_H
#define SATELLITE_GHOST_H

#include <bullet.h>
#include "minion.h"

class satellite_ghost : public minion
{
public:
	satellite_ghost(bullet* _master,float start_rot=0.0,float r=0.1,float av=4.0,pic* image=0);
	float _av,crot0;
	void loop();
};

#endif
