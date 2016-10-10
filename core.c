#include "gfx.h"
#include "var.h"
#include "ctrl.h"
#include "sim.h"
#include "menu.h"
#include <SDL/SDL.h>
#include <stdio.h>

void lyfe_up(){
	up_a();
	gfx_up();
}

void lyfe_down(){
	gfx_down();
	down_a();
}

void lyfe_do(){
	unsigned int i=0,j=0,k=0,l=0;
	do{
		j=SDL_GetTicks();
		if(j>l+10){
			l=j;
			ctrl_do();
			sim_upd();
		}

		j=SDL_GetTicks();
		if(j>k+20){
			k=j;
			if(MENU==1) menu_up();
			else if (MENU==2) menu_do();
			else if(MENU==-1) menu_down();
			gfx_do();
		}

		j=SDL_GetTicks();
		if(j>i+SPD*20){
			i=j;
			sim_do();
		}
	} while(!QUIT);
}
