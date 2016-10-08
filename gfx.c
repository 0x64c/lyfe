//look, look with your special eyes
#include "SDL2/SDL.h"
#include "var.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer = NULL;

void drawfield(){
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF); //blue
	int i;
	for(i=4;i<=SCREENH-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,4,i,SCREENW-4,i);
	}
	for(i=4;i<=SCREENW-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,i,4,i,SCREENH-4);
	}
}

void drawcursor(){
	SDL_SetRenderDrawColor(renderer,0x6A,0xEB,0xEB,0xFF);//b
	int cx = 4+GRIDW*pt.x;
	int cy = 4+GRIDW*pt.y;
	int dx = cx+GRIDW-1;
	int dy = cy+GRIDW-1;
	SDL_RenderDrawLine(renderer,cx,cy,dx,cy); //top
	SDL_RenderDrawLine(renderer,cx,cy,cx,dy); //left
	SDL_RenderDrawLine(renderer,cx,dy,dx,dy); //bottom
	SDL_RenderDrawLine(renderer,dx,dy,dx,cy); //right
	SDL_SetRenderDrawColor(renderer,0xAB,0x6A,0xEB,0xFF);//p
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

void drawfore(){
	int i,j;
	for(i=0;i<UNI_W;i++){
		for(j=0;j<UNI_H;j++){
			SDL_Rect r = {5+GRIDW*i,5+GRIDW*j,GRIDW-1,GRIDW-1};
			if(get_a(&uni_data,i,j,DIM)>0) SDL_SetRenderDrawColor(renderer,0xAB,0xEB,0x6A,0xFF);//g
			else SDL_SetRenderDrawColor(renderer,0xEB,0x6A,0x6A,0xFF);//r
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
