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

struct pt_ pt = {0,0};

Char3d uni_data;

void up_a(){
	uni_data.x = UNI_W;
	uni_data.y = UNI_H;
	uni_data.dim = 2;
	uni_data.data = malloc(uni_data.x * uni_data.y * uni_data.dim * sizeof *uni_data.data);
	memset(uni_data.data, 0, uni_data.x * uni_data.y * uni_data.dim * sizeof *uni_data.data);
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
