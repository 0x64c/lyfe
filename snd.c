#include "snd.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Chunk *sfx_cur=NULL,*sfx_sel=NULL,*sfx_nop=NULL,*sfx_up=NULL,*sfx_down=NULL,*sfx_start=NULL,*sfx_stop=NULL,*sfx_clr;
unsigned int lastplayedtime,lastplayedsound;

void playsnd(WHICHSOUND sound){
	if(((SDL_GetTicks()-lastplayedtime)<100)&&lastplayedsound==sound) return;
	Mix_Chunk *dummy;
	switch(sound){
		case SFX_CUR: dummy=sfx_cur;
		break;
		case SFX_SEL: dummy=sfx_sel;
		break;
		case SFX_NOP: dummy=sfx_nop;
		break;
		case SFX_UP: dummy=sfx_up;
		break;
		case SFX_DOWN: dummy=sfx_down;
		break;
		case SFX_START: dummy=sfx_start;
		break;
		case SFX_STOP: dummy=sfx_stop;
		break;
		case SFX_CLR: dummy=sfx_clr;
		break;
	}
	if(dummy)Mix_PlayChannel(-1,dummy,0);
	lastplayedtime=SDL_GetTicks();
	lastplayedsound=sound;
}

void snd_up(){
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	sfx_cur=Mix_LoadWAV("sfx/sfx_cur.ogg");
	sfx_sel=Mix_LoadWAV("sfx/sfx_sel.ogg");
	sfx_nop=Mix_LoadWAV("sfx/sfx_nope.ogg");
	sfx_up=Mix_LoadWAV("sfx/sfx_up.ogg");
	sfx_down=Mix_LoadWAV("sfx/sfx_down.ogg");
	sfx_start=Mix_LoadWAV("sfx/sfx_start.ogg");
	sfx_stop=Mix_LoadWAV("sfx/sfx_stop.ogg");
	sfx_clr=Mix_LoadWAV("sfx/sfx_clr.ogg");
	lastplayedtime=SDL_GetTicks();
	lastplayedsound=-1;
}

void snd_down(){
	if(sfx_cur)Mix_FreeChunk(sfx_cur);
	if(sfx_sel)Mix_FreeChunk(sfx_sel);
	if(sfx_nop)Mix_FreeChunk(sfx_nop);
	if(sfx_up)Mix_FreeChunk(sfx_up);
	if(sfx_down)Mix_FreeChunk(sfx_down);
	if(sfx_start)Mix_FreeChunk(sfx_start);
	if(sfx_stop)Mix_FreeChunk(sfx_stop);
	if(sfx_clr)Mix_FreeChunk(sfx_clr);
	Mix_CloseAudio();
	Mix_Quit();
}

