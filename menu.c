#include "var.h"
#include <stddef.h>

pt_ menupt;
const int menusize = 10;

void menu_up(){
	//MENU=1;
	menupt.x=0,menupt.y=0,menupt.val=menusize,menupt.next=NULL;
	MENU=2;
}

void menu_down(){
	//MENU=-1;
	MENU=0;
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
	switch(in){
		case 0:
			return "TOPKEK";
		case 1:
			return "TOPKEK+1";
		case 2:
			return "TOPKEK+2";
		case 3:
			return "TOPKEK+3";
		case 4:
			return "TOPKEK+4";
		case 5:
			return "TOPKEK+5";
		case 6:
			return "TOPKEK+6";
		case 7:
			return "TOPKEK+7";
		case 8:
			return "TOPKEK+8";
		case 9:
			return "TOPKEK+9";
	}
}
