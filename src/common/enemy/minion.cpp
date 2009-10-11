#include "minion.h"

minion::minion(bullet* _master)
{
	master=_master;
}

void minion::loop()
{
	if(master==0)
	{
		destroy();
		return; 
	}
	if(master==(bullet*)(1))
	{
		kill();
		return; 
	}
}
