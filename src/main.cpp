#include <cstdlib>
#include <iostream>
#include <fstream>
#include "game.h"
#include <stage_marisa\stage_marisa.h>

using namespace std;



 
//int main(int argc, char *argv[])
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
	hge_init();
	ifstream test_rep("rep\\replay",ifstream::binary);
	if(test_rep)
	{
		test_rep.close();
		estg=new ESTG("rep\\replay");
	}
	else
	{
		estg=new ESTG();
	}
	estg->add_self(GREEN_DAM);
	estg->add(new stage_marisa());
	hge->System_Start();
	estg->quit();
	hge->System_Shutdown();
	hge->Release();
    return 0;
}
