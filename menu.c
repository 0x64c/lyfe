#include "var.h"
#include <stddef.h>
pt_ menupt;
const int menusize = 6;

char* str[]={
	"Rumble: ",
	"Sim Delay: ",
	"Pause Sim",
	"Clear Screen",
	"Close Dialogue",
	"Exit Game"
};

void menu_up(){
	//MENU=1;
	menupt.x=0,menupt.y=0,menupt.val=menusize,menupt.next=NULL;
	MENU=2;
}

void menu_down(){
	//MENU=-1;
	MENU=0;
}
void menu_set(int amt){
	switch (menupt.x){
		case 0:
			if(amt>0)RUMBL=1;
			else RUMBL=0;
		break;
		case 1:
			if(amt>0&&SPD+amt>SPDMAX) SPD=SPDMAX;
			else if(amt<0&&SPD+amt<SPDMIN) SPD=SPDMIN;
			else SPD+=amt;
		break;
		case 2:
			if(amt>0){if(SIM)SIM--;else SIM++;}
		break;
		case 3:
			if(amt>0)CLEAR=1;
		break;
		case 4:
			if(amt>0)MENU=-1;
		break;
		case 5:
			if(amt>0)QUIT=1;
		break;
	}
}
void menu_do(){
	return;
}

void menu_ptu(){
	if(menupt.x>0) menupt.x--;
}

void menu_ptd(){
	if(menupt.x<menupt.val-1) menupt.x++;
}

int menu_ptget(){
	return menupt.x;
}

char* menu_lineget(int in){
	return str[in];
}
