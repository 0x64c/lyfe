#include "shake.h"
#include "var.h"
#include <stdio.h>
Shake_Device *device;
Shake_Effect effect0;
int id0;
int COUNTER=0;

void rumbl_update(){
	Shake_SimplePeriodic(&effect0,SHAKE_PERIODIC_SINE,1,0,0.3,0.1);
	id0 = Shake_UploadEffect(device, &effect0);
}
void rumbl_up(){
	Shake_Init();
	if(Shake_NumOfDevices()>0){
		device = Shake_Open(0);
		rumbl_update();
	}
}
void rumbl_do(){
	if(RUMBL){
		/*if(SIM>7||(COUNTER>>2)){
			Shake_Play(device, id0);
			COUNTER=0;
		}else COUNTER++;*/
		if(SPD>9){
			Shake_Play(device, id0);
		}else{
			if(COUNTER<(1<<(9-SPD))) COUNTER++;
			else {Shake_Play(device, id0); COUNTER=0;}
		}
	}
}
void rumbl_down(){
	Shake_EraseEffect(device, id0);
	Shake_Close(device);
	Shake_Quit();
}
