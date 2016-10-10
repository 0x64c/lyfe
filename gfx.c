//look, look with your special eyes
#include "SDL2/SDL.h"
//#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "var.h"
#include "menu.h"
#include "SDL_FontCache.h"

#ifdef _GCW_
char fontfile[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#else
char fontfile[] = "/usr/share/fonts/TTF/DejaVuSansMono.ttf";
//"/usr/share/fonts/adobe-source-code-pro/SourceCodePro-Medium.otf";
//"/usr/share/fonts/TTF/LiberationMono-Regular.ttf";
#endif
char fontfile2[] = "./DejaVuSansMono.ttf";


SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer = NULL;
int menuw = 100;
int menuh = 100;
int menubw = 3;
//TTF_Font *font;
FC_Font *font;
/*typedef struct texlist{
	SDL_Texture* tex;
	SDL_Rect rect;
	struct texlist* next;
} texlist;
texlist *first;*/

/*void makemenu(){
	first = (struct texlist *)malloc(sizeof(texlist));
	int textw=0,texth=0;
	texlist *prev;
	SDL_Color textcolour = {0x00,0x00,0xFF};
	int cx = SCREENW/2 -menuw/2+menuw/10;
	int cy = SCREENH/2 -menuh/2-1;
	//for(int i=0;i<10;i++){
	for(int i=10;i--;){
		SDL_Surface *messagebox = TTF_RenderText_Solid(font,menu_lineget(9-i),textcolour);
		SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,messagebox);
		SDL_QueryTexture(message,NULL,NULL,&textw,&texth);
		SDL_Rect r4 = {cx,cy+(9-i)*10,textw,texth};
		if(i==9){
			first->tex = message;
			first->rect = r4;
			first->next = NULL;
			prev = first;
		}else{
			texlist *new = (struct texlist *)malloc(sizeof(texlist));
			new->tex = message;
			new->rect = r4;
			new->next = NULL;
			prev->next = new;
			prev = new;
		}
		SDL_FreeSurface(messagebox);
	}
}*/

void drawmenu(){
	SDL_Rect r = {SCREENW/2 -menuw/2,SCREENH/2 -menuh/2,menuw,menuh};
	SDL_Rect r2 = {SCREENW/2 -menuw/2 -menubw,SCREENH/2 -menuh/2 -menubw,menuw+2*menubw,menuh+2*menubw};
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
	SDL_RenderFillRect(renderer,&r2);
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderFillRect(renderer,&r);
	int curx = SCREENH/2 -menuh/2+4+((menuh/10)*menu_ptget());
	int cury = SCREENW/2 -menuw/2+(menuw/20);
	SDL_Rect r3 = {cury-1,curx-1,5,5};
	SDL_SetRenderDrawColor(renderer,0x80,0x10,0x10,0xFF);
	SDL_RenderFillRect(renderer,&r3);
	/*texlist *current = first;
	while(current!=NULL){
		SDL_RenderCopy(renderer,current->tex,NULL,&current->rect);
		current = current->next;
	}*/

	int cx = SCREENW/2 -menuw/2+menuw/10;
	int cy = SCREENH/2 -menuh/2-1;
	for(int i=0;i<menusize;i++){
		if(i==1) FC_DrawAlign(font,renderer,cx,cy+i*10,FC_ALIGN_LEFT,"%s%d",menu_lineget(i),100-SPD);
		else FC_DrawAlign(font,renderer,cx,cy+i*10,FC_ALIGN_LEFT,"%s",menu_lineget(i));
	}
}

//draw the grid
void drawfield(){
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF); //black
	int i;
	for(i=4;i<=SCREENH-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,4,i,SCREENW-4,i);
	}
	for(i=4;i<=SCREENW-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,i,4,i,SCREENH-4);
	}
}

//draw the cursor
void drawcursor(){
	SDL_SetRenderDrawColor(renderer,0x6A,0xEB,0xEB,0xFF);//blue
	int cx = 4+GRIDW*pt.x;
	int cy = 4+GRIDW*pt.y;
	int dx = cx+GRIDW-1;
	int dy = cy+GRIDW-1;
	SDL_RenderDrawLine(renderer,cx,cy,dx,cy); 
	SDL_RenderDrawLine(renderer,cx,cy,cx,dy); 
	SDL_RenderDrawLine(renderer,cx,dy,dx,dy); 
	SDL_RenderDrawLine(renderer,dx,dy,dx,cy); 
	SDL_SetRenderDrawColor(renderer,0xAB,0x6A,0xEB,0xFF);//purple
	SDL_RenderDrawLine(renderer,cx,cy,dx,dy); //diag
	SDL_RenderDrawLine(renderer,cx,dy,dx,cy); //diag
}

void gfx_up(){
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("Lyfe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(screen);
	font = FC_CreateFont();
	if(!FC_LoadFont(font,renderer,fontfile,10,FC_MakeColor(0,0,255,255),TTF_STYLE_NORMAL))
		FC_LoadFont(font,renderer,fontfile2,10,FC_MakeColor(0,0,255,255),TTF_STYLE_NORMAL);
	//makemenu();
}

/*void deltexlist(texlist *current){
	if(current == NULL) return;
	else if(current->next != NULL){
		deltexlist(current->next);
	}
	free(current->tex);
	free(current);
}*/

void gfx_down(){
	//deltexlist(first);
	FC_FreeFont(font);
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
	TTF_Quit();
}

//draw the pixels
void drawfore(){
	int i,j;
	SDL_Rect r = {0,0,GRIDW-1,GRIDW-1};
	//for(i=0;i<UNI_W;i++){
	for(i=UNI_W;i--;){
		//for(j=0;j<UNI_H;j++){
		for(j=UNI_H;j--;){
			//SDL_Rect r = {5+GRIDW*i,5+GRIDW*j,GRIDW-1,GRIDW-1};
			r.x=5+GRIDW*i; r.y=5+GRIDW*j;
			if(get_a(&uni_data,i,j,DIM)>0) SDL_SetRenderDrawColor(renderer,0xAB,0xEB,0x6A,0xFF);//green
			else SDL_SetRenderDrawColor(renderer,0xEB,0x6A,0x6A,0xFF);//red
			SDL_RenderFillRect(renderer,&r);
		}
	}			
}

void gfx_do(){
	drawfield();
	drawfore();
	drawcursor();
	if(MENU>1)drawmenu();
	SDL_UpdateWindowSurface(window);
}
