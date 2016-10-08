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
				case SDLK_ESCAPE:
					QUIT = 1;
					break;
				case SDLK_LCTRL:
					set_a(&uni_data,pt.x,pt.y,DIM,1);
					break;
				case SDLK_LALT:
					set_a(&uni_data,pt.x,pt.y,DIM,0);
					break;
				case SDLK_UP:
					if(pt.y>0) pt.y--;
					else pt.y=UNI_H-1;
					break;
				case SDLK_DOWN:
					if(pt.y<UNI_H-1) pt.y++;
					else pt.y=0;
					break;
				case SDLK_LEFT:
					if(pt.x>0) pt.x--;
					else pt.x=UNI_W-1;
					break;
				case SDLK_RIGHT:
					if(pt.x<UNI_W-1) pt.x++;
					else pt.x=0;
					break;
				case SDLK_SPACE:
					SIM = 1;
					break;
				case SDLK_LSHIFT:
					SIM = 0;
					break;
			}
		}
	}
}
