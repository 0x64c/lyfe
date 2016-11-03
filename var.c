#include "var.h"
#include <stdlib.h>
#include <string.h>
const int SCREENW = 320;
const int SCREENH = 240;
const int FONTSIZE = 12;
const int JOYDEADZONE = 3200;
const int JOYTHRESHOLD = 15000;

int UNI_W,UNI_H,BORDERW,BORDERH,DISPH,DISPW;
int GRIDW = 10;
int QUIT = 0;
int SIM = 0;
int DIM = 0;
int SPD = 5;
int SPDMIN = 1;
int SPDMAX = 100;
int CLEAR = 0;
int MENU = 0;
int RUMBL = 0;
int MOVEMAP_X=0;
int MOVEMAP_Y=0;
int MAP_X=0;
int MAP_Y=0;
unsigned short vismask=0x1;		//0b 0000 0001
unsigned short neighbourmask=0x1E;	//0b 0001 1110
unsigned short neighbourflagmask=0x20;	//0b 0010 0000

Char3d uni_data;
pt_ pt = {0,0,0,NULL};

void displaybox_do(){
	MAP_X=MAP_X + MOVEMAP_X;//*(DISPW/2);
	MAP_Y=MAP_Y + MOVEMAP_Y;//*(DISPH/2);
	if(MAP_X<0)MAP_X=0;
	else if(MAP_X>UNI_W-DISPW)MAP_X=UNI_W-DISPW;
	if(MAP_Y<0)MAP_Y=0;
	else if(MAP_Y>UNI_H-DISPH)MAP_Y=UNI_H-DISPH;
}

void clr_a(){
	memset(uni_data.data, 0, uni_data.x * uni_data.y * (sizeof *uni_data.data));
}

void up_a(){
	BORDERW=(SCREENW%GRIDW)/2;
	BORDERH=(SCREENH%GRIDW)/2;
	DISPW=SCREENW/GRIDW;
	DISPH=SCREENH/GRIDW;
	UNI_W=320;
	UNI_H=240;
	uni_data.x = UNI_W;
	uni_data.y = UNI_H;
	uni_data.data = malloc(uni_data.x * uni_data.y * sizeof *uni_data.data);
	clr_a();
}

void set_a(Char3d *arr,unsigned short x,unsigned short y,unsigned short val,unsigned short mask){
	arr->data[x * arr->y + y] = 
		(arr->data[x * arr->y + y] &~mask) | (val&mask);
}
unsigned short get_a(Char3d *arr,unsigned short x,unsigned short y){
	return arr->data[x * arr->y + y];
}

void down_a(){
	if(uni_data.data){
		free(uni_data.data);
		uni_data.data=NULL;
	}
}
