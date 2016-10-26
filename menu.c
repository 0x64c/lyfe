#include "var.h"
#include "snd.h"
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
	playsnd(SFX_UP);
}

void menu_down(){
	//MENU=-1;
	MENU=0;
	playsnd(SFX_DOWN);
}
void menu_set(int amt){
	int temp;
	switch (menupt.x){
		case 0:
			temp=RUMBL;
			if(amt>0)RUMBL=1;
			else RUMBL=0;
			if(RUMBL!=temp) playsnd(SFX_SEL);
			else playsnd(SFX_NOP);
		break;
		case 1:
			if(amt>0&&SPD+amt>SPDMAX){SPD=SPDMAX;playsnd(SFX_NOP);}
			else if(amt<0&&SPD+amt<SPDMIN){SPD=SPDMIN;playsnd(SFX_NOP);}
			else{SPD+=amt;playsnd(SFX_SEL);}
		break;
		case 2:
			if(amt>0){if(SIM){SIM--;playsnd(SFX_STOP);}else{SIM++;playsnd(SFX_START);}}
		break;
		case 3:
			if(amt>0){clr_a();playsnd(SFX_CLR);}//CLEAR=1;
		break;
		case 4:
			if(amt>0) MENU=-1;
		break;
		case 5:
			if(amt>0) QUIT=1;
		break;
	}
}
void menu_do(){
	return;
}

void menu_ptu(){
	if(menupt.x>0){menupt.x--;playsnd(SFX_SEL);}
	else playsnd(SFX_NOP);
}

void menu_ptd(){
	if(menupt.x<menupt.val-1){menupt.x++;playsnd(SFX_SEL);}
	else playsnd(SFX_NOP);
}

int menu_ptget(){
	return menupt.x;
}

char* menu_lineget(int in){
	return str[in];
}
