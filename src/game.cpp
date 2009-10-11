#include "game.h"

inline void get_control_keys()
{
	estg->control.up=hge->Input_GetKeyState(HGEK_UP)||hge->Input_GetKeyState(HGEK_W);
	estg->control.down=hge->Input_GetKeyState(HGEK_DOWN)||hge->Input_GetKeyState(HGEK_S);
	estg->control.left=hge->Input_GetKeyState(HGEK_LEFT)||hge->Input_GetKeyState(HGEK_A);
	estg->control.right=hge->Input_GetKeyState(HGEK_RIGHT)||hge->Input_GetKeyState(HGEK_D);
	estg->control.slow=hge->Input_GetKeyState(HGEK_SHIFT)||hge->Input_GetKeyState(HGEK_NUMPAD4);
	estg->control.fire=hge->Input_GetKeyState(HGEK_Z)||hge->Input_GetKeyState(HGEK_NUMPAD5);
	estg->control.bomb=hge->Input_GetKeyState(HGEK_X)||hge->Input_GetKeyState(HGEK_NUMPAD6);
}

void hge_init(void)
{
	hge=hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_LOGFILE, "ESTG.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	hge->System_SetState(HGE_TITLE, "ESTG");
	hge->System_SetState(HGE_ICON,"img\\ESTG.ico");
	hge->System_SetState(HGE_DONTSUSPEND,true);
	hge->System_SetState(HGE_FOCUSLOSTFUNC,tab_out);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_WINDOWED, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_SCREENWIDTH, RESOLUTION_X);
	hge->System_SetState(HGE_SCREENHEIGHT, RESOLUTION_Y);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_Initiate();
}

bool FrameFunc()
{
	get_control_keys();
	estg->loop();
	switch(hge->Input_GetKey())
	{
		case HGEK_ESCAPE: return true;
		case HGEK_SPACE: estg->pause=!(estg->pause);
	}
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	//UI
	hge->Gfx_SetClipping();
	res->img["ui_bg_1"]->RenderStretch(0,0,8,480);
	res->img["ui_bg_2"]->RenderStretch(392,0,640,480);
	res->img["ui_bg_3"]->RenderStretch(8,0,392,8);
	res->img["ui_bg_4"]->RenderStretch(8,472,392,480);
	//bg
	hge->Gfx_SetClipping(8,8,384,464);
	//if(estg->bg1!=0&&(estg->bg_trans_status!=0||estg->bg2==0)) estg->bg1->draw(1.0);
	//if(estg->bg2!=0) estg->bg2->draw(1.0-double(estg->bg_trans_status)/estg->bg_trans_time);
	if(estg->bg1!=0&&estg->bg2==0)
		estg->bg1->draw(1.0);
	if(estg->bg1!=0&&estg->bg2!=0)
		if(estg->bg1->layer>=estg->bg2->layer)
		{
			estg->bg2->draw(1.0);
			estg->bg1->draw(double(estg->bg_trans_status)/estg->bg_trans_time);
		}
		else
		{
			estg->bg1->draw(1.0);
			estg->bg2->draw(1-double(estg->bg_trans_status)/estg->bg_trans_time);
		}
	//bullets
	list<bullet*>::iterator iter;
	int i,j;
	for(j=0;j<MAX_LAYER;j++)
		for(i=0;i<MAX_ATTR;i++)
			for(iter=estg->blist[i][j].begin();iter!=estg->blist[i][j].end();iter++)
				(*iter)->draw();
	//
	//UI
	//
	hge->Gfx_EndScene();
	return false;
}

bool tab_out()
{
	estg->pause=true;
	return false;
}
