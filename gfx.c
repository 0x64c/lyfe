//look, look with your special eyes
#include "SDL2/SDL.h"
//#include <SDL/SDL_image.h>
//#include <SDL/SDL_ttf.h>
#include "var.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer = NULL;

/*void drawmenu(){
	
}*/

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
	window = SDL_CreateWindow("Lyfe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(screen);
}

void gfx_down(){
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
}

//draw the pixels
void drawfore(){
	int i,j;
	for(i=0;i<UNI_W;i++){
		for(j=0;j<UNI_H;j++){
			SDL_Rect r = {5+GRIDW*i,5+GRIDW*j,GRIDW-1,GRIDW-1};
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
	SDL_UpdateWindowSurface(window);
}
