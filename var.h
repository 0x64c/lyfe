extern const int SCREENW,SCREENH,FONTSIZE,JOYDEADZONE,JOYTHRESHOLD;
extern int UNI_H,UNI_W,GRIDW,BORDER,QUIT,SIM,DIM,SPD,SPDMIN,SPDMAX,CLEAR,MENU,RUMBL,MOVEMAP_X,MOVEMAP_Y,MAP_X,MAP_Y,BORDERW,BORDERH,DISPW,DISPH;

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

extern unsigned short vismask,neighbourmask,neighbourflagmask;
extern void clr_a();
extern void up_a();
extern void set_a(Char3d*,unsigned short,unsigned short,unsigned short,unsigned short);
extern unsigned short get_a(Char3d*,unsigned short,unsigned short);
extern void down_a();
extern void displaybox_do();
