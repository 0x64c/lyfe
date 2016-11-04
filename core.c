#include <SDL2/SDL.h>
#include "gfx.h"
#include "var.h"
#include "ctrl.h"
#include "sim.h"
#include "menu.h"
#include "rumbl.h"
#include "snd.h"
#include <stdio.h>

void lyfe_up(){
	up_a();
	gfx_up();
	ctrl_up();
	snd_up();
	rumbl_up();
}

void lyfe_down(){
	down_a();
	gfx_down();
	rumbl_down();
	ctrl_down();
	snd_down();
	SDL_Quit();
}

void lyfe_do(){
	unsigned int i=0,j=0,k=0,l=0;
	do{
		j=SDL_GetTicks();
		if(j>l+10){
			l=j;
			ctrl_do();
			displaybox_do();
		}

		j=SDL_GetTicks();
		if(j>k+30){
			k=j;
			if(menu_state&MENU_UP){
				//menu_state&=!MENU_UP;
				menu_up();
			}
			else if(menu_state&MENU_DOWN){
				//menu_state&=!MENU_DOWN;
				menu_down();
			}
			gfx_do();
		}

		j=SDL_GetTicks();
		if(j>i+SPD*10){
			i=j;
			sim_do();
		}
	} while(!QUIT);
	//SDL_Delay(1000);
}
