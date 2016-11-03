#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "var.h"
#include "menu.h"
#include <stdio.h>

#ifdef _GCW_
char fontfile[] = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#else
char fontfile[] = "/usr/share/fonts/TTF/DejaVuSansMono.ttf";
char fontfile2[] = "./DejaVuSansMono.ttf";
#endif


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Renderer *renderer2 = NULL;
SDL_Surface *surface = NULL;
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
		case 4:
			sprintf(buffer,"%s%d",menu_lineget(line),gridw);
			messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
			break;		
		default:
			messagebox = TTF_RenderText_Solid(font,menu_lineget(line),textcolour);
			break;
	}
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,messagebox);
	SDL_QueryTexture(message,NULL,NULL,&textw,&texth);
	menutext_rect[line]->x=SCREENW/2-menuw/2+menuw/10;
	menutext_rect[line]->y=r_menu_b.y+3+line*FONTSIZE;
	menutext_rect[line]->w=textw;
	menutext_rect[line]->h=texth;
	menutext_tex[line] = message;
	SDL_FreeSurface(messagebox);
}

SDL_Rect draw_cursor(){
	int width = GRIDW;
	if(GRIDW<3)width=3;
	SDL_Rect rect={0,0,width+1,width+1};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0xFF);//black
	if(GRIDW>2){
		SDL_RenderDrawLine(renderer2,0,0,width,width); //diag
		SDL_RenderDrawLine(renderer2,0,width,width,0); //diag
		SDL_SetRenderDrawColor(renderer2,0x6A,0xEB,0xEB,0xFF);//blue
	}
	SDL_Point points[]={{.x=0,.y=0},{.x=width,.y=0},{.x=width,.y=width},{.x=0,.y=width},{.x=0,.y=0}};
	SDL_RenderDrawLines(renderer2,points,5);
	return rect;
}
SDL_Rect draw_pixels(){
	int i=GRIDW-1;
//	if(GRIDW<3)i=2;
	SDL_Rect rect={0,0,i,i};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,0xAB,0xEB,0x6A,0xFF);//green
	SDL_RenderFillRect(renderer2,&rect);
	SDL_SetRenderDrawColor(renderer2,0xEB,0x6A,0x6A,0xFF);//red
	rect.x+=rect.w;
	SDL_RenderFillRect(renderer2,&rect);
	rect.x-=rect.w;
	rect.w+=rect.w;
	return rect;
}
SDL_Rect draw_grid(){
	SDL_Rect rect={0,0,320,240};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,0xFF,0xFF,0xFF,0xFF); //white
	SDL_RenderFillRect(renderer2,&rect);
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0xFF); //black
	if(GRIDW<3)return rect;
	int i;
	for(i=0;i<=DISPH;i++){
		SDL_RenderDrawLine(renderer2,BORDERW,BORDERH+i*GRIDW,SCREENW-BORDERW-1,BORDERH+i*GRIDW);
	}
	for(i=0;i<=DISPW;i++){
		SDL_RenderDrawLine(renderer2,BORDERW+i*GRIDW,BORDERH,BORDERW+i*GRIDW,SCREENH-BORDERH-1);
	}
	return rect;
}

SDL_Rect draw_menubg(){
	SDL_Rect rect={0,0,menuw+2*menubw,menuh+2*menubw};
	SDL_Rect rect2={menubw,menubw,menuw,menuh};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0xFF);//black
	SDL_RenderFillRect(renderer2,&rect);
	SDL_SetRenderDrawColor(renderer2,0xFF,0xFF,0xFF,0xFF);//white
	SDL_RenderFillRect(renderer2,&rect2);
	return rect;
}
SDL_Rect draw_menupt(){
	SDL_Rect rect={0,0,5,5};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,0x80,0x10,0x10,0xFF);
	SDL_RenderFillRect(renderer2,&rect);
	return rect;
}
SDL_Texture* draw_sprite(SDL_Rect* rect2,SDL_Rect (*draw)()){
	SDL_Rect rect = draw();
	SDL_Surface *dummy_surface = SDL_CreateRGBSurface(0,rect.w,rect.h,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_BlitSurface(surface,&rect,dummy_surface,NULL);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,dummy_surface);
	SDL_FreeSurface(dummy_surface);
	rect2->x=rect.x;
	rect2->y=rect.y;
	rect2->w=rect.w;
	rect2->h=rect.h;
	return tex;
}

void init_gfx_obj(){
	surface = SDL_CreateRGBSurface(0,320,240,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	renderer2 = SDL_CreateSoftwareRenderer(surface);

	menu_tex = draw_sprite(&r_menu_b,(*draw_menubg));
	menu_c_tex = draw_sprite(&r_menu_c,(*draw_menupt));
	p_tex = draw_sprite(&r_p_tex,(*draw_pixels));
	c_tex = draw_sprite(&r_c_tex,(*draw_cursor));
	g_tex = draw_sprite(&r_g_tex,(*draw_grid));

	r_menu_b.x=SCREENW/2 -menuw/2 -menubw;
	r_menu_b.y=SCREENH/2 -menuh/2 -menubw;
	r_p_tex2.x=r_p_tex.x;
	r_p_tex2.y=r_p_tex.y;
	r_p_tex.w=r_p_tex2.w=r_p_tex.w/2;
	r_p_tex2.h=r_p_tex.h;

	for(int i=0;i<menusize;i++){
		menutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i);
	}
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer2);
}

void drawmenu(){
	r_menu_c.y=r_menu_b.y+8+FONTSIZE*menu_ptget();
	r_menu_c.x=r_menu_b.x+(menuw/20);
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
	int i=GRIDW; int j=BORDERW; int k=BORDERH;
	if(GRIDW<3){i=2;j=-1;}
	r_c_tex.x=j+i*pt.x;
	r_c_tex.y=k+i*pt.y;
	SDL_RenderCopy(renderer,c_tex,NULL,&r_c_tex);
}

void gfx_up(){
	menuw = 10*FONTSIZE;
	menuh = (menusize)*FONTSIZE+3;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("Lyfe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	font = TTF_OpenFont(fontfile,FONTSIZE);
#ifndef _GCW_
	if(!font) TTF_OpenFont(fontfile2,FONTSIZE);
#endif
	menutext_rect = malloc(menusize * sizeof(SDL_Rect*));
	menutext_tex = malloc(menusize * sizeof(SDL_Texture*));
	init_gfx_obj();
}

void gfx_resize(int gridw_){
	SDL_DestroyTexture(c_tex);
	SDL_DestroyTexture(p_tex);
	SDL_DestroyTexture(g_tex);
	SDL_DestroyTexture(menu_tex);
	SDL_DestroyTexture(menu_c_tex);
	GRIDW=gridw_;
	BORDERW=(SCREENW%GRIDW)/2;
	BORDERH=(SCREENH%GRIDW)/2;
	DISPW=SCREENW/GRIDW;
	DISPH=SCREENH/GRIDW;

	surface = SDL_CreateRGBSurface(0,320,240,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	renderer2 = SDL_CreateSoftwareRenderer(surface);

	menu_tex = draw_sprite(&r_menu_b,(*draw_menubg));
	menu_c_tex = draw_sprite(&r_menu_c,(*draw_menupt));
	p_tex = draw_sprite(&r_p_tex,(*draw_pixels));
	c_tex = draw_sprite(&r_c_tex,(*draw_cursor));
	g_tex = draw_sprite(&r_g_tex,(*draw_grid));

	r_menu_b.x=SCREENW/2 -menuw/2 -menubw;
	r_menu_b.y=SCREENH/2 -menuh/2 -menubw;
	r_p_tex2.x=r_p_tex.x;
	r_p_tex2.y=r_p_tex.y;
	r_p_tex.w=r_p_tex2.w=r_p_tex.w/2;
	r_p_tex2.h=r_p_tex.h;

	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer2);

	if(pt.x>DISPW)pt.x=DISPW-1;
	if(pt.y>DISPH)pt.y=DISPH-1;
}

void gfx_down(){
	for(int i=0;i<menusize;i++){
		SDL_DestroyTexture(menutext_tex[i]);
		free(menutext_rect[i]);
	}
	SDL_DestroyTexture(c_tex);
	SDL_DestroyTexture(p_tex);
	SDL_DestroyTexture(g_tex);
	SDL_DestroyTexture(menu_tex);
	SDL_DestroyTexture(menu_c_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

//draw the pixels
void drawfore(){
	int i,j;
	int k=GRIDW;
	int l=BORDERW+1;
	int m=BORDERH+1;
	if(k<3){k=2;l=0;}
	for(i=DISPW;i--;){
		for(j=DISPH;j--;){
			r_p_tex2.y=m+k*j; r_p_tex2.x=l+k*i;
			if((get_a(&uni_data,i+MAP_X,j+MAP_Y)&vismask)>0) r_p_tex.x=0;
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
