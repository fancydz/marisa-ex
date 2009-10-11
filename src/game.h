#ifndef GAME_H
#define GAME_H
#include <hge.h>
#include <hgefont.h>
#include <ESTG.h>

extern HGE* hge;
extern ESTG* estg;
void hge_init(void);
bool FrameFunc();
bool RenderFunc();
bool tab_out();

#endif
