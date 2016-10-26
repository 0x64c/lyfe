#include "var.h"
#include "rumbl.h"
#include <stddef.h>
int mod(int a,int b){
	int r = a % b;
	return r < 0 ? r + b : r;
}

int neighbours(int x, int y, int dim){
/*	int n;
	if(x==0&&y==0&&x==UNI_W-1&&y==UNI_H-1){
		n=	get_a(&uni_data,x,y-1,dim)+
			get_a(&uni_data,x,y+1,dim)+
			get_a(&uni_data,x-1,y,dim)+
			get_a(&uni_data,x+1,y,dim)+
			get_a(&uni_data,x-1,y-1,dim)+
			get_a(&uni_data,x-1,y+1,dim)+
			get_a(&uni_data,x+1,y-1,dim)+
			get_a(&uni_data,x+1,y+1,dim);
	}else{*/
//		n=	
	return 		get_a(&uni_data,x,mod(y-1,UNI_H),dim)+
			get_a(&uni_data,x,mod(y+1,UNI_H),dim)+
			get_a(&uni_data,mod(x-1,UNI_W),y,dim)+
			get_a(&uni_data,mod(x+1,UNI_W),y,dim)+
			get_a(&uni_data,mod(x-1,UNI_W),mod(y-1,UNI_H),dim)+
			get_a(&uni_data,mod(x-1,UNI_W),mod(y+1,UNI_H),dim)+
			get_a(&uni_data,mod(x+1,UNI_W),mod(y-1,UNI_H),dim)+
			get_a(&uni_data,mod(x+1,UNI_W),mod(y+1,UNI_H),dim);
//	}
//	return n;
}

/*void sim_upd(){
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
}*/

void sim_do(){
	int i,j,k;
	if (SIM){
		if(DIM) k = 0;
		else k = 1;
		for(i=UNI_W;i--;){
			for(j=UNI_H;j--;){
				int n = neighbours(i,j,DIM);
				int m = get_a(&uni_data,i,j,DIM);
				if((n==3)||(n==2&&m==1)) set_a(&uni_data,i,j,k,1);
				else set_a(&uni_data,i,j,k,0);
			}
		}
		DIM=k;
		rumbl_do();
	}
}
