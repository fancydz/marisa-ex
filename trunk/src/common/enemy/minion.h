#ifndef MINION_H
#define MINION_H

#include <bullet.h>

class minion : public enemy
{
public:
	minion(bullet* _master);
	void loop();
};

#endif
