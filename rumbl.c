#include "shake.h"
#include "var.h"

Shake_Device *device;
Shake_Effect effect0,effect1,effect2,effect3;
int id0,id1,id2,id3;

void rumbl_up(){
	Shake_Init();
	if(Shake_NumOfDevices()>0){
		device = Shake_Open(0);
		Shake_SimpleRumble(&effect0,70.0,30.0,0.2);
		Shake_SimpleRumble(&effect1,70.0,30.0,0.4);
		Shake_SimpleRumble(&effect2,70.0,30.0,0.6);
		Shake_SimpleRumble(&effect3,70.0,30.0,0.8);
		id0 = Shake_UploadEffect(device, &effect0);
		id1 = Shake_UploadEffect(device, &effect1);
		id2 = Shake_UploadEffect(device, &effect2);
		id3 = Shake_UploadEffect(device, &effect3);
	}
}
void rumbl_do(){
	if(!RUMBL)return;
	int x = (SPDMAX-SPDMIN)/SPD;
	if(x>75)Shake_Play(device, id3);
	else if(x>50)Shake_Play(device, id2);
	else if(x>25)Shake_Play(device, id1);
	else Shake_Play(device, id0);
}
void rumbl_down(){
	Shake_EraseEffect(device, id0);
	Shake_EraseEffect(device, id1);
	Shake_EraseEffect(device, id2);
	Shake_EraseEffect(device, id3);
	Shake_Close(device);
	Shake_Quit();
}
