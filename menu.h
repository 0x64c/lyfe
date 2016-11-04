typedef enum {
	MENU_NONE=	1<<0,
	MAIN_MENU=	1<<1,
	COLOUR_MENU=	1<<2,
	MENU_UP=	1<<3,
	MENU_DOWN=	1<<4,
	COLOURS=	1<<5
} MENU_CATEGORY;
extern void menu_do();
extern void menu_up();
extern void menu_down();
extern void menu_ptu(int);
extern void menu_ptd(int);
extern int menu_ptget();
extern char* menu_lineget(int,MENU_CATEGORY);
extern const int menusize,ncolours;
extern void menu_set(int,int,MENU_CATEGORY);
extern int gridw,menu_state;
extern int menu_numitems(MENU_CATEGORY);
