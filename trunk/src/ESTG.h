#ifndef ESTG_H
#define ESTG_H

#include <list>

#include <hge.h>
#include <hgefont.h>

#include <common\common_res.h>
#include <bullet.h>
#include <common\self_char\self_char.h>
#include <common\self_char\green_dam\green_dam.h>

using namespace std;

class ESTG
{
public:
	ESTG(char* rep_file=0);
	list<bullet*> blist[MAX_ATTR][MAX_LAYER];
	self_char* self;
	bullet* stage_master;
	bool pause;
	struct control_t
	{
		bool up,down,left,right,fire,slow,bomb;
	} control;
	struct data_t
	{
		int object;
		int object_alive;
		int point;
		int p2p[8];
		int player;
		int spell;
		int graze;
		int score;
		int score_show;
	} data;
	int ticker;
	list<bullet*>::iterator add(bullet* pbullet);
	void add_self(int _self);
	void loop();
	void run_scripts();
	float xorg,yorg,xstr,ystr,xos,yos;
	int shake_status;
	void shake(int duration=120);
	back_ground* bg1;//pre
	back_ground* bg2;//post
	void set_bg(back_ground* pbg,int trans_time=60);
	int bg_trans_time;
	int bg_trans_status;//0 means post bg is fully drawn
	resource sres;
	float se_volume;
	float bgm_volume;
	void play_se(char* effect,float volume)
	{
		res->snd[effect]->vol+=exp(volume*SND_FACTOR);
	}
	struct bgm_info_t
	{
		HEFFECT next_bgm;
		HCHANNEL bgm_chn;
		int fade_status;
		float loop_end;
		float loop_lenth;
		float pos;
	} bgm;
	void play_bgm(HEFFECT se_bgm,float lp_end,float lp_lenth);
	void destroy_all_enemy();
	void kill_all_bullet();
	float hp_bar;
	float count_down_timer;
	bool is_replay;
	bool no_rep;
	char rep_data[1024*1024];
	struct rep_info_t
	{
		int ran_seed;
		int lenth;
		//and other informations
	} rep_info;
	void save_rep(char* rep_file_path);
	void load_rep(char* rep_file_path);
	bool quit_flag;
	void quit();
	~ESTG();
};

inline bool is_collide(bullet* attacker,bullet* sufferer,float sufferer_r=-1.0);

extern HGE* hge;
extern ESTG* estg;
extern cres* res;

inline float x2scr(float x){return (estg->xos+estg->xorg+estg->xstr*x);}
inline float y2scr(float y){return (estg->yos+estg->yorg+estg->ystr*y);}

inline float uix2scr(float x){return (estg->xorg+estg->xstr*x);}
inline float uiy2scr(float y){return (estg->yorg+estg->ystr*y);}

//score calc
#define BULLET_BONUS 15
#define ATTACK_BONUS 15
#define POINT_BONUS 3000
#define GRAZE_BONUS 150
#define TIME_BONUS 2000
#define GRAZE_FACTOR 7500
#define CARD_FACTOR 3
//

#endif
