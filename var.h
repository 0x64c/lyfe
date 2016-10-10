//herein lies global var
extern const int SCREENW,SCREENH,SCREENBPP;
extern int UNI_H,UNI_W,GRIDW,QUIT,SIM,DIM,SPD,SPDMIN,SPDMAX,CLEAR,MENU;

typedef struct pt_{
	unsigned short x,y,val;
	struct pt_* next;
} pt_;

typedef struct{
	unsigned short x,y,dim;
	unsigned short *data;
} Char3d;

extern pt_ pt;
extern Char3d uni_data;

extern void clr_a();
extern void up_a();
extern void set_a(Char3d*,int,int,int,unsigned short);
extern unsigned short get_a(Char3d*,int,int,int);
extern void down_a();
extern void pop_q();
extern void push_q(unsigned short,unsigned short,unsigned short);
extern pt_* top_q();
