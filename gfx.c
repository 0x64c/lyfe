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
SDL_Texture **menutext_tex,**colourmenutext_tex;
SDL_Rect **menutext_rect,**colourmenutext_rect;
SDL_Colour textcolour = {0x00,0x00,0x00,0xFF};
SDL_Colour cursorcolour0 = {0x00,0x00,0x00,0xFF};
SDL_Colour cursorcolour1 = {0x33,0x33,0xFF,0xFF};
SDL_Colour pixelcolour0 = {0x33,0xFF,0x33,0xFF};
SDL_Colour pixelcolour1 = {0xFF,0x33,0x33,0xFF};
SDL_Colour gridcolour0 = {0x00,0x00,0x00,0xFF};
SDL_Colour menucolour0 = {0x00,0x00,0x00,0x90};
SDL_Colour menucolour1 = {0xFF,0xFF,0xFF,0xE0};
SDL_Colour menucolour2 = {0xFF,0x33,0x33,0xFF};

SDL_Colour *colourpointers[]={&textcolour,&cursorcolour0,&cursorcolour1,&pixelcolour0,
	&pixelcolour1,&gridcolour0,&menucolour0,&menucolour1,&menucolour2};

SDL_Rect r_menu,r_menu_b,r_menu_c,r_c_tex,r_p_tex,r_p_tex2,r_g_tex;
int c_menu_x,c_menu_text_x;
Uint8 temp_r,temp_g,temp_b,temp_a;

SDL_Texture *c_tex,*p_tex,*g_tex,*menu_tex,*menu_c_tex;
void inittempcolour(int which){
	temp_r=colourpointers[which]->r;
	temp_g=colourpointers[which]->g;
	temp_b=colourpointers[which]->b;
	temp_a=colourpointers[which]->a;
}
int settempcolour(int subcolour,int x){
	Uint8 *c;
	switch(subcolour){
		case 0: c=&temp_r; break;			
		case 1: c=&temp_g; break;			
		case 2: c=&temp_b; break;			
		case 3: c=&temp_a; break;
		default: c=NULL; break;
	}
	if((*c)+x>255)
		(*c)=255;
	else if((*c)+x<0)
		(*c)=0;
	else{
		(*c)+=x;
		return 1;
	}
	return 0;
}
void confirmcolour(int which){
	colourpointers[which]->r=temp_r;
	colourpointers[which]->g=temp_g;
	colourpointers[which]->b=temp_b;
	colourpointers[which]->a=temp_a;
}
void updatemenu(int line, MENU_CATEGORY category){
	int textw=0,texth=0;
	SDL_Surface *messagebox;
	char buffer[20];
	switch(category){
		case MAIN_MENU:
			switch(line){
				case 0:
					sprintf(buffer,"%s%d",menu_lineget(line,category),RUMBL);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 1:
					sprintf(buffer,"%s%d",menu_lineget(line,category),SPD);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 2:
					sprintf(buffer,"%s%d",menu_lineget(line,category),SIM);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 4:
					sprintf(buffer,"%s%d",menu_lineget(line,category),gridw);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;		
				default:
					messagebox = TTF_RenderText_Solid(font,menu_lineget(line,category),textcolour);
					break;
			}
			break;
		case COLOUR_MENU:
			switch(line){
				case 0:
					sprintf(buffer,"%s%s",menu_lineget(line,category),menu_lineget(COLOUR,COLOURS));
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 1:
					sprintf(buffer,"%s%X",menu_lineget(line,category),temp_r);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 2:
					sprintf(buffer,"%s%X",menu_lineget(line,category),temp_g);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 3:
					sprintf(buffer,"%s%X",menu_lineget(line,category),temp_b);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				case 4:
					sprintf(buffer,"%s%X",menu_lineget(line,category),temp_a);
					messagebox = TTF_RenderText_Solid(font,buffer,textcolour);
					break;
				default:
					messagebox = TTF_RenderText_Solid(font,menu_lineget(line,category),textcolour);
					break;
			}
			break;
		default:
			break;
	}
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer,messagebox);
	SDL_QueryTexture(message,NULL,NULL,&textw,&texth);
	switch(category){
		case MAIN_MENU:
			menutext_rect[line]->x=SCREENW/2-menuw/2+menuw/10;
			menutext_rect[line]->y=r_menu_b.y+3+line*FONTSIZE;
			menutext_rect[line]->w=textw;
			menutext_rect[line]->h=texth;
			menutext_tex[line] = message;
			break;
		case COLOUR_MENU:
			colourmenutext_rect[line]->x=SCREENW/2-menuw/2+menuw/10;
			colourmenutext_rect[line]->y=r_menu_b.y+3+line*FONTSIZE;
			colourmenutext_rect[line]->w=textw;
			colourmenutext_rect[line]->h=texth;
			colourmenutext_tex[line] = message;
			break;
		default:
			break;
	}
	SDL_FreeSurface(messagebox);
}

SDL_Rect draw_cursor(){
	int width = GRIDW;
	SDL_Rect rect={0,0,width+1,width+1};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	if(GRIDW>3){
	SDL_SetRenderDrawColor(renderer2,cursorcolour0.r,cursorcolour0.g,cursorcolour0.b,cursorcolour0.a);//black
		SDL_RenderDrawLine(renderer2,0,0,width,width); //diag
		SDL_RenderDrawLine(renderer2,0,width,width,0); //diag
	}
	SDL_SetRenderDrawColor(renderer2,cursorcolour1.r,cursorcolour1.g,cursorcolour1.b,cursorcolour1.a);//blue
	SDL_Point points[]={{.x=0,.y=0},{.x=width,.y=0},{.x=width,.y=width},{.x=0,.y=width},{.x=0,.y=0}};
	SDL_RenderDrawLines(renderer2,points,5);
	return rect;
}
SDL_Rect draw_pixels(){
	int i=GRIDW-1;
//	if(GRIDW<3)i=2;
	SDL_Rect rect={0,0,i,i};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,pixelcolour0.r,pixelcolour0.g,pixelcolour0.b,pixelcolour0.a);//green
	SDL_RenderFillRect(renderer2,&rect);
	SDL_SetRenderDrawColor(renderer2,pixelcolour1.r,pixelcolour1.g,pixelcolour1.b,pixelcolour1.a);//red
	rect.x+=rect.w;
	SDL_RenderFillRect(renderer2,&rect);
	rect.x-=rect.w;
	rect.w+=rect.w;
	return rect;
}
SDL_Rect draw_grid(){
	SDL_Rect rect={0,0,320,240};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,gridcolour0.r,gridcolour0.g,gridcolour0.b,gridcolour0.a); //black
	SDL_RenderFillRect(renderer2,&rect);
/*	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0xFF); //black
	int i;
	for(i=0;i<=DISPH;i++){
		SDL_RenderDrawLine(renderer2,BORDERW,BORDERH+i*GRIDW,SCREENW-BORDERW-1,BORDERH+i*GRIDW);
	}
	for(i=0;i<=DISPW;i++){
		SDL_RenderDrawLine(renderer2,BORDERW+i*GRIDW,BORDERH,BORDERW+i*GRIDW,SCREENH-BORDERH-1);
	}*/
	return rect;
}

SDL_Rect draw_menubg(){
	SDL_Rect rect={0,0,menuw+2*menubw,menuh+2*menubw};
	SDL_Rect rect2={menubw,menubw,menuw,menuh};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,menucolour0.r,menucolour0.g,menucolour0.b,menucolour0.a);//black
	SDL_RenderFillRect(renderer2,&rect);
	SDL_SetRenderDrawColor(renderer2,menucolour1.r,menucolour1.g,menucolour1.b,menucolour1.a);//white
	SDL_RenderFillRect(renderer2,&rect2);
	return rect;
}
SDL_Rect draw_menupt(){
	SDL_Rect rect={0,0,5,5};
	SDL_SetRenderDrawColor(renderer2,0x00,0x00,0x00,0x00);SDL_RenderClear(renderer2);
	SDL_SetRenderDrawColor(renderer2,menucolour2.r,menucolour2.g,menucolour2.b,menucolour2.a);//red
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

	for(int i=0;i<menu_numitems(MAIN_MENU);i++){
		menutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i,MAIN_MENU);
	}

	for(int i=0;i<menu_numitems(COLOUR_MENU);i++){
		colourmenutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i,COLOUR_MENU);
	}

	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer2);
}

void drawmenu(MENU_CATEGORY category){
	r_menu_c.y=r_menu_b.y+8+FONTSIZE*menu_ptget();
	r_menu_c.x=r_menu_b.x+(menuw/20);
	SDL_RenderCopy(renderer,menu_tex,NULL,&r_menu_b);
	SDL_RenderCopy(renderer,menu_c_tex,NULL,&r_menu_c);
	for(int i=0;i<menu_numitems(category);i++){
		switch(category){
			case MAIN_MENU:
				SDL_RenderCopy(renderer,menutext_tex[i],NULL,menutext_rect[i]);
				break;
			case COLOUR_MENU:
				SDL_RenderCopy(renderer,colourmenutext_tex[i],NULL,colourmenutext_rect[i]);
				break;
			default:
			break;
		}
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
	menuw = 12*FONTSIZE;
	menuh = menu_numitems(MAIN_MENU)*FONTSIZE+3;
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
	colourmenutext_rect = malloc(menusize * sizeof(SDL_Rect*));
	colourmenutext_tex = malloc(menusize * sizeof(SDL_Texture*));
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

	for(int i=0;i<menu_numitems(MAIN_MENU);i++){
		menutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i,MAIN_MENU);
	}

	for(int i=0;i<menu_numitems(COLOUR_MENU);i++){
		colourmenutext_rect[i]=malloc(sizeof(SDL_Rect));
		updatemenu(i,COLOUR_MENU);
	}


	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer2);

	if(pt.x>DISPW)pt.x=DISPW-1;
	if(pt.y>DISPH)pt.y=DISPH-1;
}

void gfx_down(){
	for(int i=0;i<menu_numitems(MAIN_MENU);i++){
		SDL_DestroyTexture(menutext_tex[i]);
		free(menutext_rect[i]);
	}
	for(int i=0;i<menu_numitems(COLOUR_MENU);i++){
		SDL_DestroyTexture(colourmenutext_tex[i]);
		free(colourmenutext_rect[i]);
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
	if(menu_state&(COLOUR_MENU|MAIN_MENU))drawmenu(menu_state);
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
