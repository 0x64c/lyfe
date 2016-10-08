#include "gfx.h"
#include "var.h"
#include "ctrl.h"
#include "sim.h"
#include <SDL/SDL.h>

void lyfe_up(){
	up_a();
	gfx_up();
}

void lyfe_down(){
	gfx_down();
	down_a();
}

void lyfe_do(){
	do{
		gfx_do();
		ctrl_do();
		if(SIM){
			sim_do();
			SDL_Delay(30);
		}
	} while(!QUIT);
}
