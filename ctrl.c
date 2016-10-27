#include <SDL2/SDL.h>
#include "var.h"
#include "menu.h"
#include "snd.h"
SDL_Event e;

extern void ctrl_do(){
	 while(SDL_PollEvent(&e)!=0){
		if(e.type==SDL_QUIT){
			QUIT = 1;
		}else if(e.type==SDL_KEYDOWN){
			if(MENU){
			switch(e.key.keysym.sym){
			//general
				case SDLK_ESCAPE: //quit
					QUIT = 1;
					break;
			//specific
				case SDLK_LSHIFT: //menu
					if(e.key.repeat)break;
					MENU=-1;
					break;
				case SDLK_LCTRL: //select
					menu_set(1,e.key.repeat);
					break;
				case SDLK_LALT: //back
					menu_set(-1,e.key.repeat);
					break;
				case SDLK_UP: //cursor up
					menu_ptu(e.key.repeat);
					break;
				case SDLK_DOWN: //cursor down
					menu_ptd(e.key.repeat);
					break;
				case SDLK_LEFT: //cursor left
					menu_set(-10,e.key.repeat);
					break;
				case SDLK_RIGHT: //cursor right
					menu_set(10,e.key.repeat);
					break;
			}}else{
			switch(e.key.keysym.sym){
			//general
				case SDLK_ESCAPE: //quit
					QUIT = 1;
					playsnd(SFX_SEL);
					break;
				case SDLK_SPACE: //start/stop sim
					if(e.key.repeat)break;
					if(SIM){SIM = 0; playsnd(SFX_STOP);}
					else{SIM = 1; playsnd(SFX_START);}
					break;
				case SDLK_BACKSPACE: //speed up
					if(SPD>SPDMIN){SPD--;playsnd(SFX_CUR);}
					break;
				case SDLK_TAB: //slow down
					if(SPD<SPDMAX){SPD++;playsnd(SFX_CUR);}
					break;
				case SDLK_RETURN: //clear
					//CLEAR=1;
					if(e.key.repeat)break;
					clr_a();
					playsnd(SFX_CLR);
					break;
			//specific
				case SDLK_LSHIFT: //menu
					if(e.key.repeat)break;
					MENU=1;
					break;
				case SDLK_LCTRL: //place selection
					if(e.key.repeat)break;
					set_a(&uni_data,pt.x,pt.y,DIM,1);
					playsnd(SFX_SEL);
					//push_q(pt.x,pt.y,1);
					break;
				case SDLK_LALT: //remove selection
					if(e.key.repeat)break;
					set_a(&uni_data,pt.x,pt.y,DIM,0);
					playsnd(SFX_SEL);
					//push_q(pt.x,pt.y,0);
					break;
				case SDLK_UP: //cursor up
					if(pt.y>0) pt.y--;
					else pt.y=UNI_H-1;
					playsnd(SFX_CUR);
					break;
				case SDLK_DOWN: //cursor down
					if(pt.y<UNI_H-1) pt.y++;
					else pt.y=0;
					playsnd(SFX_CUR);
					break;
				case SDLK_LEFT: //cursor left
					if(pt.x>0) pt.x--;
					else pt.x=UNI_W-1;
					playsnd(SFX_CUR);
					break;
				case SDLK_RIGHT: //cursor right
					if(pt.x<UNI_W-1) pt.x++;
					else pt.x=0;
					playsnd(SFX_CUR);
					break;
			}}
		}
	}
}
