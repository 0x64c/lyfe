#include "var.h"
#include "rumbl.h"
#include <stddef.h>
#include <stdio.h>
int mod(int a,int b){
	int r = a % b;
	return r < 0 ? r + b : r;
}

int neighbours(int x, int y){
/*	int n;
	if(x==0&&y==0&&x==UNI_W-1&&y==UNI_H-1){
		n=	get_a(&uni_data,x,y-1)+
			get_a(&uni_data,x,y+1)+
			get_a(&uni_data,x-1,y)+
			get_a(&uni_data,x+1,y)+
			get_a(&uni_data,x-1,y-1)+
			get_a(&uni_data,x-1,y+1)+
			get_a(&uni_data,x+1,y-1)+
			get_a(&uni_data,x+1,y+1);
	}else{*/
//		n=	
	int z =((vismask&get_a(&uni_data,x             ,mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,x             ,mod(y+1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),y             ))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),y             ))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),mod(y+1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),mod(y+1,UNI_H))));
			if(z)printf("%d\n",z);
	return z;
//	}
//	return n;
}

/*void sim_upd(){
	pt_ *n = top_q();
	while(n != NULL){
		set_a(&uni_data,n->x,n->y,n->val);
		pop_q();
		n = top_q();
	}
	if(CLEAR){
		clr_a();
		CLEAR = 0;
	}
}*/
void updateneighbours(){
	int i,j;
	for(i=UNI_W;i--;){
		for(j=UNI_H;j--;){
			if(get_a(&uni_data,i,j)>>5){
				int x = neighbours(i,j);
				set_a(&uni_data,i,j,x<<1,neighbourmask|neighbourflagmask);
			}
		}
	}
}
void updateneighbourflags(int x,int y){
	set_a(&uni_data,mod(x-1,UNI_W),mod(y-1,UNI_H),1<<5,neighbourflagmask);
	set_a(&uni_data,mod(x-1,UNI_W),mod(y+1,UNI_H),1<<5,neighbourflagmask);
	set_a(&uni_data,mod(x+1,UNI_W),mod(y-1,UNI_H),1<<5,neighbourflagmask);
	set_a(&uni_data,mod(x+1,UNI_W),mod(y+1,UNI_H),1<<5,neighbourflagmask);
	set_a(&uni_data,x             ,mod(y-1,UNI_H),1<<5,neighbourflagmask);
	set_a(&uni_data,x             ,mod(y+1,UNI_H),1<<5,neighbourflagmask);
	//set_a(&uni_data,x             ,y             ,1<<5,neighbourflagmask);
	set_a(&uni_data,mod(x-1,UNI_W),y             ,1<<5,neighbourflagmask);
	set_a(&uni_data,mod(x+1,UNI_W),y             ,1<<5,neighbourflagmask);
}

void sim_do(){
	int i,j,l,m,n,x;
	updateneighbours();
	if (SIM){
		for(i=UNI_W;i--;){
			for(j=UNI_H;j--;){
				l = get_a(&uni_data,i,j);
				n = (l&neighbourmask)>>1;
				m = l&vismask;
				if((n==3)||(n==2&&m==1)) x=1;
				else x=0;
				set_a(&uni_data,i,j,x,vismask);
				updateneighbourflags(i,j);
			}
		}
		rumbl_do();
	}
}
