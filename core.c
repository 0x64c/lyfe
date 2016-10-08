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
	//pthread_t simthread;
	//pthread_mutex_init(&lock)
	//pthread_create(&simthread,NULL,sim_do,NULL);
	int i=0;
	do{
		gfx_do();
		ctrl_do();
		if((++i%(25*SPD))==0) sim_do();
	} while(!QUIT);
	//pthread_join(simthread,NULL);
}
