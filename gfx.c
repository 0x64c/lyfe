#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "var.h"
#include "menu.h"
#include <stdio.h>

#ifdef _GCW_
char fontfile[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#else
char fontfile[] = "/usr/share/fonts/TTF/DejaVuSansMono.ttf";
#endif
char fontfile2[] = "./DejaVuSansMono.ttf";

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int menuw;// = 10*FONTSIZE;
int menuh;// = (menusize+2)*FONTSIZE;
int menubw = 3;

TTF_Font *font;
SDL_Texture **menutext_tex;
SDL_Rect **menutext_rect;
SDL_Color textcolour = {000,000,255,255};

SDL_Rect r_menu,r_menu_b,r_menu_c,r_c_tex,r_p_tex,r_p_tex2,r_g_tex;
int c_menu_x,c_menu_text_x;

SDL_Texture *c_tex,*p_tex,*g_tex,*menu_tex,*menu_c_tex;

void updatemenu(int line){
	int textw=0,texth=0;
	SDL_Surface *messagebox;
	char buffer[20];
	switch(line){
		case 0:
			sprintf(buffer,"%s%d",menu_lineget(line),RUMBL);
			messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
			break;
		case 1:
			sprintf(buffer,"%s%d",menu_lineget(line),SPD);
			messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
			break;
		case 2:
			sprintf(buffer,"%s%d",menu_lineget(line),SIM);
			messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
			break;		
		default:
			messagebox = TTF_RenderText_Solid(font,menu_lineget(line),textcolour);
			break;
	}
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,messagebox);
	SDL_QueryTexture(message,NULL,NULL,&textw,&texth);
	menutext_rect[line]->x=c_menu_text_x;
	menutext_rect[line]->y=r_menu.y+line*FONTSIZE;
	menutext_rect[line]->w=textw;
	menutext_rect[line]->h=texth;
	menutext_tex[line] = message;
	SDL_FreeSurface(messagebox);
}

void init_gfx_obj(){
	//menu
	r_menu.x=SCREENW/2 -menuw/2; r_menu.y=SCREENH/2 -menuh/2; r_menu.w=menuw; r_menu.h=menuh;
	r_menu_b.x=SCREENW/2 -menuw/2 -menubw; r_menu_b.y=SCREENH/2 -menuh/2 -menubw; r_menu_b.w=menuw+2*menubw; r_menu_b.h=menuh+2*menubw;
	r_menu_c.y=0;
	r_menu_c.w=5;
	r_menu_c.h=5;
	c_menu_x = r_menu.x+(menuw/20);
	c_menu_text_x=r_menu.x+menuw/10;
	r_menu_c.x=c_menu_x-4;
	//cursor
	r_c_tex.x=0;r_c_tex.y=0;r_c_tex.w=GRIDW+1;r_c_tex.h=GRIDW+1;
	c_tex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,r_c_tex.w,r_c_tex.h);
	SDL_SetRenderTarget(renderer,c_tex);
	SDL_SetTextureBlendMode(c_tex,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);//black
	SDL_RenderDrawLine(renderer,0,0,8,8); //diag
	SDL_RenderDrawLine(renderer,0,8,8,0); //diag	
	SDL_SetRenderDrawColor(renderer,0x6A,0xEB,0xEB,0xFF);//blue
	SDL_Point points[]={{.x=0,.y=0},{.x=8,.y=0},{.x=8,.y=8},{.x=0,.y=8},{.x=0,.y=0}};
	SDL_RenderDrawLines(renderer,points,5);
	//pixels
	r_p_tex.x=0;r_p_tex.y=0;r_p_tex.w=GRIDW-1;r_p_tex.h=GRIDW-1;
	r_p_tex2.x=0;r_p_tex2.y=0;r_p_tex2.w=GRIDW-1;r_p_tex2.h=GRIDW-1;
	p_tex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,r_p_tex.w*2,r_p_tex.h);
	SDL_SetRenderTarget(renderer,p_tex);
	SDL_SetRenderDrawColor(renderer,0xAB,0xEB,0x6A,0xFF);//green
	SDL_RenderFillRect(renderer,&r_p_tex);
	SDL_SetRenderDrawColor(renderer,0xEB,0x6A,0x6A,0xFF);//red
	r_p_tex.x+=r_p_tex.w;
	SDL_RenderFillRect(renderer,&r_p_tex);;
	//grid
	r_g_tex.x=0;r_g_tex.y=0;r_g_tex.w=320;r_g_tex.h=240;
	g_tex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,r_g_tex.w,r_g_tex.h);
	SDL_SetRenderTarget(renderer,g_tex);
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF); //white
	SDL_RenderFillRect(renderer,&r_g_tex);
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF); //black
	int i;
	for(i=4;i<=SCREENH-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,4,i,SCREENW-4,i);
	}
	for(i=4;i<=SCREENW-4;i=i+GRIDW){
		SDL_RenderDrawLine(renderer,i,4,i,SCREENH-4);
	}
	//menubg
	SDL_Rect r_menu_tex={0,0,r_menu_b.w,r_menu_b.h};
	menu_tex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,r_menu_tex.w,r_menu_tex.h);
	SDL_SetRenderTarget(renderer,menu_tex);
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);//black
	SDL_RenderFillRect(renderer,&r_menu_tex);
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);//white
	r_menu_tex.x+=menubw;r_menu_tex.y+=menubw;r_menu_tex.w-=2*menubw;r_menu_tex.h-=2*menubw;
	SDL_RenderFillRect(renderer,&r_menu_tex);
	//menupt
	r_menu_tex.x=0;r_menu_tex.y=0;r_menu_tex.w=r_menu_c.w;r_menu_tex.h=r_menu_c.h;
	menu_c_tex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,r_menu_tex.w,r_menu_tex.h);
	SDL_SetRenderTarget(renderer,menu_c_tex);
	SDL_SetRenderDrawColor(renderer,0x80,0x10,0x10,0xFF);
	SDL_RenderFillRect(renderer,&r_menu_tex);

	SDL_SetRenderTarget(renderer,NULL);
	//menutext
	for(int i=0;i<menusize;i++){
		menutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i);
	}
}

void drawmenu(){
	r_menu_c.y=r_menu.y+4+FONTSIZE*menu_ptget();
	SDL_RenderCopy(renderer,menu_tex,NULL,&r_menu_b);
	SDL_RenderCopy(renderer,menu_c_tex,NULL,&r_menu_c);
	for(int i=0;i<menusize;i++){
		SDL_RenderCopy(renderer,menutext_tex[i],NULL,menutext_rect[i]);
	}
}

//draw the grid
void drawfield(){
	SDL_RenderCopy(renderer,g_tex,NULL,&r_g_tex);
}

//draw the cursor
void drawcursor(){
	r_c_tex.x=4+GRIDW*pt.x; r_c_tex.y=4+GRIDW*pt.y;
	SDL_RenderCopy(renderer,c_tex,NULL,&r_c_tex);
}

void gfx_up(){
	menuw = 10*FONTSIZE;
	menuh = (menusize)*FONTSIZE+3;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("Lyfe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,SDL_WINDOW_SHOWN);
#ifndef _GCW_
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
#else
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
#endif
	font = TTF_OpenFont(fontfile,FONTSIZE);
	if(!font) TTF_OpenFont(fontfile2,FONTSIZE);
	menutext_rect = malloc(menusize * sizeof(SDL_Rect*));
	menutext_tex = malloc(menusize * sizeof(SDL_Texture*));
	init_gfx_obj();
}

void gfx_down(){
	for(int i=0;i<menusize;i++){
		SDL_DestroyTexture(menutext_tex[i]);
		free(menutext_rect[i]);
	}
	SDL_DestroyTexture(c_tex);
	SDL_DestroyTexture(p_tex);
	SDL_DestroyTexture(g_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

//draw the pixels
void drawfore(){
	int i,j;
	for(i=UNI_W;i--;){
		for(j=UNI_H;j--;){
			r_p_tex2.y=5+GRIDW*j; r_p_tex2.x=5+GRIDW*i;
			if(get_a(&uni_data,i,j,DIM)>0) r_p_tex.x=0;
			else r_p_tex.x=r_p_tex.w;
			SDL_RenderCopy(renderer,p_tex,&r_p_tex,&r_p_tex2);
		}
	}
}

void gfx_do(){
	drawfield();
	drawfore();
	drawcursor();
	if(MENU>1)drawmenu();
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
