#include <cstdlib>
#include <iostream>
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
	estg=new ESTG();
	estg->reset(GREEN_DAM);
	estg->add(new stage_marisa());
	hge->System_Start();
	hge->System_Shutdown();
	hge->Release();
    return 0;
}
