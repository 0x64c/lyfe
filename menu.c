#include "var.h"
#include "snd.h"
#include "gfx.h"
#include <stddef.h>
#include "menu.h"
#include <stdio.h>

pt_ menupt;
const int menusize = 9;
const int menusize_colours = 7;
const int ncolours = 9;
int gridw;
int menu_state=1;

char* str[]={
	"Rumble: ",
	"Sim Delay: ",
	"Sim ON/OFF: ",
	"Clear Screen",
	"Grid Size: ",
	"Commit Resize",
	"Palette Editor",
	"Close Dialogue",
	"Exit Game"
};

char* str_colours[]={
	"Text",
	"Cursor 0",
	"Cursor 1",
	"Pixel 0",
	"Pixel 1",
	"Grid",
	"Menu 0",
	"Menu 1",
	"Menu 2"
};

char* str_colourmenu[]={
	"Colour: ",
	"R: ",
	"G: ",
	"B: ",
	"A: ",
	"Set",
	"Return"
};

int menu_numitems(MENU_CATEGORY category){
	int x;
	switch(category){
		case MAIN_MENU: x=menusize; break;
		case COLOURS: x=ncolours; break;
		case COLOUR_MENU: x=menusize_colours; break;
		default: x=0; break;
	}
	return x;
}

void menu_up(){
	menu_state&=~MENU_UP;
	menupt.x=0,menupt.y=0,menupt.next=NULL;
	gridw=GRIDW;
	switch(menu_state){
		case MENU_NONE:
			playsnd(SFX_UP);
		case COLOUR_MENU:
			menu_state=MAIN_MENU;
			menupt.val=menu_numitems(menu_state);
			for(int i=0;i<3;i++)updatemenu(i,menu_state);
			updatemenu(4,menu_state);
			break;
		case MAIN_MENU:
			COLOUR=0;
			inittempcolour(COLOUR);
			menu_state=COLOUR_MENU;
			menupt.val=menu_numitems(menu_state);
			for(int i=0;i<5;i++)updatemenu(i,menu_state);
			playsnd(SFX_UP);
			break;
		default:
			menu_state=MENU_NONE;
			break;
	}

}

void menu_down(){
	menu_state&=~MENU_DOWN;
	switch(menu_state){
		case MAIN_MENU:
			menu_state=MENU_NONE;
			playsnd(SFX_DOWN);
			break;
		case COLOUR_MENU:
			menu_state|=MENU_UP;
			playsnd(SFX_DOWN);
			break;
		default:
			break;
	}
}

void menu_set(int amt,int repeat, MENU_CATEGORY category){
	int temp;

	switch(category){
		case MAIN_MENU:
			switch (menupt.x){
				case 0:
					temp=RUMBL;
					if(amt>0)RUMBL=1;
					else RUMBL=0;
					if(RUMBL!=temp){playsnd(SFX_SEL);updatemenu(menupt.x,category);}
					else if(!repeat) playsnd(SFX_NOP);
					break;
				case 1:
					temp=SPD;
					if(amt>0&&SPD+amt>SPDMAX)SPD=SPDMAX;
					else if(amt<0&&SPD+amt<SPDMIN)SPD=SPDMIN;
					else SPD+=amt;
					if(temp!=SPD){updatemenu(menupt.x,category);playsnd(SFX_SEL);}
					else if(!repeat) playsnd(SFX_NOP);
					break;
				case 2:
					if(!repeat){if(SIM){SIM--;playsnd(SFX_STOP);updatemenu(menupt.x,category);}else{SIM++;playsnd(SFX_START);updatemenu(menupt.x,category);}}
					break;
				case 3:
					if(!repeat){clr_a();playsnd(SFX_CLR);}//CLEAR=1;
					break;
				case 4:
					gridw=gridw+amt;
					if(gridw<3) gridw=3;
					else if(gridw>SCREENH) gridw=SCREENH;
					updatemenu(menupt.x,category);
					playsnd(SFX_SEL);
					break;
				case 5:
					gfx_resize(gridw);
					playsnd(SFX_CLR);
					break;
				case 6:
					menu_up(COLOUR_MENU);
					break;
				case 7:
					menu_down(category);
					break;
				case 8:
					if(amt>0) QUIT=1;
					break;
			}
			break;
		case COLOUR_MENU:
			switch (menupt.x){
				case 0:
					if(amt<0) temp=COLOUR-1;
					else if(amt>0) temp=COLOUR+1;
					if(temp>=0&&temp<ncolours){
						COLOUR=temp;
						playsnd(SFX_SEL);
						inittempcolour(COLOUR);
						updatemenu(menupt.x,category);
						updatemenu(1,category);
						updatemenu(2,category);
						updatemenu(3,category);
						updatemenu(4,category);
					}
					else if(!repeat)playsnd(SFX_NOP);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					temp = settempcolour(menupt.x-1,amt);
					if(temp) playsnd(SFX_SEL);
					else if(temp==0&&!repeat) playsnd(SFX_NOP);
					updatemenu(menupt.x,category);
					break;
				case 5:
					confirmcolour(COLOUR);
					gfx_resize(GRIDW);
					playsnd(SFX_CLR);
					break;
				case 6:
					menu_down(category);
					break;
			}
			break;
		default:
			break;
	}
}

void menu_ptu(int repeat){
	if(menupt.x>0){menupt.x--;playsnd(SFX_SEL);}
	else if(!repeat) playsnd(SFX_NOP);
}

void menu_ptd(int repeat){
	if(menupt.x<menupt.val-1){menupt.x++;playsnd(SFX_SEL);}
	else if(!repeat) playsnd(SFX_NOP);
}

int menu_ptget(){
	return menupt.x;
}

char* menu_lineget(int in, MENU_CATEGORY category){
	char* string;
	switch(category){
		case MAIN_MENU: string=str[in]; break;
		case COLOURS: string=str_colours[in]; break;
		case COLOUR_MENU: string=str_colourmenu[in]; break;
		default: string=NULL; break;
	}
	return string;
}

