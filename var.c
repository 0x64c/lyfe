//herein lies global var
#include "var.h"
#include <stdlib.h>
#include <string.h>
const int SCREENW = 320;
const int SCREENH = 240;
const int SCREENBPP = 16;

int UNI_W = 39;
int UNI_H = 29;
int GRIDW = 8;
int QUIT = 0;
int SIM = 0;
int DIM = 0;
int SPD = 5;
int CLEAR = 0;

pt_ pt = {0,0,0,NULL};
pt_ *q_first = NULL;
pt_ *q_last = NULL;
pt_ *q_tempy = NULL;
pt_ *q_tempy2 = NULL;

Char3d uni_data;

pt_* top_q(){
	if(q_first == NULL) return NULL;
	return q_first;
}

void pop_q(){
	if(q_first!=NULL){
		if(q_first->next != NULL){
			q_tempy2 = q_first->next;
			free(q_first);
			q_first = q_tempy2;
		}else{
			free(q_first);
			q_first = NULL;
			q_last = NULL;
		}
	}
}

void push_q(char x, char y, char val){
	if(q_last == NULL){
		q_last = (struct pt_ *)malloc(sizeof(pt_));
		q_last->next = NULL;
		q_last->x = x;
		q_last->y = y;
		q_last->val = val;
		q_first = q_last;
	}else{
		q_tempy = (struct pt_ *)malloc(sizeof(pt_));
		q_last->next = q_tempy;
		q_tempy->x = x;
		q_tempy->y = y;
		q_tempy->val = val;
		q_tempy->next = NULL;
		q_last = q_tempy;
	}
}

void clr_a(){
	memset(uni_data.data, 0, uni_data.x * uni_data.y * uni_data.dim * sizeof *uni_data.data);
}

void up_a(){
	uni_data.x = UNI_W;
	uni_data.y = UNI_H;
	uni_data.dim = 2;
	uni_data.data = malloc(uni_data.x * uni_data.y * uni_data.dim * sizeof *uni_data.data);
	clr_a();
}

void set_a(Char3d *arr, int x, int y, int dim, char val){
	arr->data[x * (arr->y * arr->dim) + y * arr->dim + dim] = val;
}
char get_a(Char3d *arr, int x, int y, int dim){
	return arr->data[x * (arr->y * arr->dim) + y * arr->dim + dim];
}

void down_a(){
	free(uni_data.data);
}
