//herein lies global var
extern const int SCREENW,SCREENH,SCREENBPP;
extern int UNI_H,UNI_W,GRIDW,QUIT,SIM,DIM,SPD,CLEAR;

typedef struct pt_{
	char x,y,val;
	struct pt_* next;
} pt_;

typedef struct{
	char x,y,dim;
	char *data;
} Char3d;

extern pt_ pt;
extern Char3d uni_data;

extern void clr_a();
extern void up_a();
extern void set_a(Char3d*,int,int,int,char);
extern char get_a(Char3d*,int,int,int);
extern void down_a();
extern void pop_q();
extern void push_q(char,char,char);
extern pt_* top_q();
