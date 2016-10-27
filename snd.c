#include "snd.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Chunk *sfx_cur=NULL,*sfx_sel=NULL,*sfx_nop=NULL,*sfx_up=NULL,*sfx_down=NULL,*sfx_start=NULL,*sfx_stop=NULL,*sfx_clr;
unsigned int lastplayedtime,lastplayedsound;

void playsnd(WHICHSOUND sound){
	if(((SDL_GetTicks()-lastplayedtime)<100)&&lastplayedsound==sound) return;
	switch(sound){
		case SFX_CUR: Mix_PlayChannel(-1,sfx_cur,0);
		break;
		case SFX_SEL: Mix_PlayChannel(-1,sfx_sel,0);
		break;
		case SFX_NOP: Mix_PlayChannel(-1,sfx_nop,0);
		break;
		case SFX_UP: Mix_PlayChannel(-1,sfx_up,0);
		break;
		case SFX_DOWN: Mix_PlayChannel(-1,sfx_down,0);
		break;
		case SFX_START: Mix_PlayChannel(-1,sfx_start,0);
		break;
		case SFX_STOP: Mix_PlayChannel(-1,sfx_stop,0);
		break;
		case SFX_CLR: Mix_PlayChannel(-1,sfx_clr,0);
		break;
	}
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
	Mix_FreeChunk(sfx_cur);
	Mix_FreeChunk(sfx_sel);
	Mix_FreeChunk(sfx_nop);
	Mix_FreeChunk(sfx_up);
	Mix_FreeChunk(sfx_down);
	Mix_FreeChunk(sfx_start);
	Mix_FreeChunk(sfx_stop);
	Mix_FreeChunk(sfx_clr);
	Mix_Quit();
}

