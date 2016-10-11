#include "var.h"
#include "rumbl.h"
#include <stddef.h>
int normalize(int n, int min, int max){
	int res;
	if(n < min) res= n + max;
	else if(n >= max) res = n % max;
	else res = n;
	return res;
}

int neighbours(int x, int y, int dim){
	int n;
	if(!(x==0||y==0||x==UNI_W-1||y==UNI_H-1)){
		n=	get_a(&uni_data,x,y-1,dim)+
			get_a(&uni_data,x,y+1,dim)+
			get_a(&uni_data,x-1,y,dim)+
			get_a(&uni_data,x+1,y,dim)+
			get_a(&uni_data,x-1,y-1,dim)+
			get_a(&uni_data,x-1,y+1,dim)+
			get_a(&uni_data,x+1,y-1,dim)+
			get_a(&uni_data,x+1,y+1,dim);
	}else{
		n=	get_a(&uni_data,x,normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,x,normalize(y+1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),y,dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),y,dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x-1,0,UNI_W),normalize(y+1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),normalize(y-1,0,UNI_H),dim)+
			get_a(&uni_data,normalize(x+1,0,UNI_W),normalize(y+1,0,UNI_H),dim);
	}
	return n;
}

void sim_upd(){
	pt_ *n = top_q();
	while(n != NULL){
		set_a(&uni_data,n->x,n->y,DIM,n->val);
		pop_q();
		n = top_q();
	}
	if(CLEAR){
		clr_a();
		CLEAR = 0;
	}
}
//void *sim_do(void *args){
void sim_do(){
	int i,j,k;
	if (SIM){
		if(DIM) k = 0;
		else k = 1;
		//for(i=0;i<UNI_W;i++){
		for(i=UNI_W;i--;){
			//for(j=0;j<UNI_H;j++){
			for(j=UNI_H;j--;){
				int n = neighbours(i,j,DIM);
				int m = get_a(&uni_data,i,j,DIM);
				//if((m==0&&n==3)||(m==1&&(n==2||n==3))) set_a(&uni_data,i,j,k,1);
				if((n==3)||(n==2&&m==1)) set_a(&uni_data,i,j,k,1);
				else set_a(&uni_data,i,j,k,0);
			}
		}
		DIM=k;
		rumbl_do();
	}
}
