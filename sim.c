#include "var.h"
#include <stdio.h>
int normalize(int n, int min, int max){
	int res;
	if(n < min) res= n + max;
	else if(n >= max) res = n % max;
	else res = n;
	return res;
}

int neighbours(int x, int y, int dim){
	int n;
	if(x==0||y==0||x==UNI_W-1||y==UNI_H-1){
		n=	get_a(&uni_data,x,normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,x,normalize(y+1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),y,dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),y,dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),normalize(y+1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),normalize(y+1,0,UNI_H),dim);
	}else{
		n=	get_a(&uni_data,x,y-1,dim)+
			get_a(&uni_data,x,y+1,dim)+
			get_a(&uni_data,x-1,y,dim)+
			get_a(&uni_data,x+1,y,dim)+
			get_a(&uni_data,x-1,y-1,dim)+
			get_a(&uni_data,x-1,y+1,dim)+
			get_a(&uni_data,x+1,y-1,dim)+
			get_a(&uni_data,x+1,y+1,dim);
	}
	return n;
}

void sim_do(){
	int i,j,k;
	if(DIM) k = 0;
	else k = 1;
	for(i=0;i<UNI_W;i++){
		for(j=0;j<UNI_H;j++){
			int n = neighbours(i,j,DIM);
			int m = get_a(&uni_data,i,j,DIM);
			if((m==0 && n==3)||(m==1 && n>1 && n<4)) set_a(&uni_data,i,j,k,1);
			else set_a(&uni_data,i,j,k,0);
		}
	}
	DIM=k;
}
