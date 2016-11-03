#include "var.h"
#include "rumbl.h"
#include <stddef.h>

int mod(int a,int b){
	int r = a % b;
	return r < 0 ? r + b : r;
}

int neighbours(int x, int y){
	return	(vismask&get_a(&uni_data,x             ,mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,x             ,mod(y+1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),y             ))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),y             ))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x-1,UNI_W),mod(y+1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),mod(y-1,UNI_H)))+
			(vismask&get_a(&uni_data,mod(x+1,UNI_W),mod(y+1,UNI_H)));
}

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
				if(m!=x)updateneighbourflags(i,j);
			}
		}
		rumbl_do();
	}
}
