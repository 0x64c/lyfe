#include <SDL2/SDL.h>
#include "var.h"

SDL_Event e;

void ctrl_up(){
	return;
}

void ctrl_down(){
	return;
}

extern void ctrl_do(){
	 while(SDL_PollEvent(&e)!=0){
		if(e.type==SDL_QUIT){
			QUIT = 1;
		}else if(e.type==SDL_KEYDOWN){
			switch(e.key.keysym.sym){
				case SDLK_ESCAPE: //quit
					QUIT = 1;
					break;
				case SDLK_LCTRL: //place selection
					//set_a(&uni_data,pt.x,pt.y,DIM,1);
					push_q(pt.x,pt.y,1);
					break;
				case SDLK_LALT: //remove selection
					//set_a(&uni_data,pt.x,pt.y,DIM,0);
					push_q(pt.x,pt.y,0);
					break;
				case SDLK_UP: //cursor up
					if(pt.y>0) pt.y--;
					else pt.y=UNI_H-1;
					break;
				case SDLK_DOWN: //cursor down
					if(pt.y<UNI_H-1) pt.y++;
					else pt.y=0;
					break;
				case SDLK_LEFT: //cursor left
					if(pt.x>0) pt.x--;
					else pt.x=UNI_W-1;
					break;
				case SDLK_RIGHT: //cursor right
					if(pt.x<UNI_W-1) pt.x++;
					else pt.x=0;
					break;
				case SDLK_SPACE: //start sim
					SIM = 1;
					break;
				case SDLK_LSHIFT: //pause sim
					SIM = 0;
					break;
				case SDLK_TAB: //speed up
					if(SPD>1)SPD--;
					break;
				case SDLK_BACKSPACE: //slow down
					if(SPD<150)SPD++;
					break;
				case SDLK_RETURN: //clear
					CLEAR=1;
					break;
			}
		}
	}
}
