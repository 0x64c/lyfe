//herein lies global var
extern const int SCREENW,SCREENH,SCREENBPP;
extern int UNI_H,UNI_W,GRIDW,QUIT,SIM,DIM;

struct pt_{int x,y;};

typedef struct {
	char x,y,dim;
	char *data;
} Char3d;

extern struct pt_ pt;
extern Char3d uni_data;

extern void up_a();
extern void set_a(Char3d*,int,int,int,char);
extern char get_a(Char3d*,int,int,int);
extern void down_a();
