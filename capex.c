/*  CAPEX for FBA2X

    Copyright (C) 2007  JyCet
	Copyright (C) 2008 Juanvvc. Adapted from capex for cps2emu by Jycet

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// CAPEX
// FBA2X Frontend
// JYCET & Juanvvc 2K8
// v0.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>



#include "./gfx/gfx_BG.h"
#include "./gfx/gfx_CAPEX.h"
#include "./gfx/gfx_FONT.h"
#include "./gfx/gfx_SELECTEUR.h"

#include "capex.h"
#ifdef GP2X
#include "cpuclock.h"
#endif

extern char **environ;

#define FBIO_WAITFORVSYNC _IOW('F', 0x20, __u32)
unsigned long fbdev;
int vb;

int ErrorQuit;

SDL_Event event;

SDL_Surface *screen2;
SDL_Surface *screen;
SDL_Surface *bg;
SDL_Surface *bgs;
SDL_Surface *bg_temp;
SDL_Surface *font;
SDL_Surface *barre;
SDL_Surface *preview;
SDL_Surface *title;
SDL_Surface *help;
SDL_Surface *credit;
SDL_Surface *Tmp;

SDL_RWops *rw;

FILE *fp;
FILE *fp2;
//FILE *fp3;

unsigned int font6x[255];
int i;
unsigned int ii;
unsigned char flag_preview;
char g_string[255];
char ar;
char * path;
char * argument[N_ARG];
//unsigned char title_y;
unsigned char flag_save;
unsigned char flag_TV;
unsigned char offset_x , offset_y ;
Uint32 fps_count;
//char *cf;
unsigned long   gp2x_dev;
unsigned short *gp2x_memregs;

struct data
{
	unsigned int nb_rom;
	unsigned int nb_cache;
	unsigned int nb_list[NB_FILTRE];
	int nb_namelength[NB_MAX_GAMES];
	char *name[NB_MAX_GAMES];
	int nb_ziplength[NB_MAX_GAMES];
	char *zip[NB_MAX_GAMES];
	int nb_statuslength[NB_MAX_GAMES];
	char *status[NB_MAX_GAMES];
	int nb_parentlength[NB_MAX_GAMES];
	char *parent[NB_MAX_GAMES];
	unsigned char etat[NB_MAX_GAMES];
	unsigned int longueur[NB_MAX_GAMES];
	unsigned int long_max;
}data;

unsigned int listing_tri[NB_FILTRE][NB_MAX_GAMES];


struct options
{
	unsigned char y;
	unsigned char num;
	unsigned int offset_num;

	unsigned int cpu;
/*	signed int cpu68k;
	signed int cpuz80;*/
	unsigned char sound;
	unsigned int samplerate;
	unsigned char rescale;
	unsigned char rotate;
	unsigned char showfps;
	unsigned char linescroll;
	unsigned char frontend;
/*	unsigned char showtitle;
	signed char screenposition;
	unsigned char fullcache;

	unsigned char extinput;
	unsigned char xorrom;*/
	unsigned char tweak;
	unsigned char hiscore;

	unsigned char nb;
	unsigned char listing;
	unsigned char z80core;
	unsigned char filter;
	unsigned char spare1;
	unsigned char spare2;
	unsigned char spare3;
	unsigned char spare4;
	unsigned char spare5;
	unsigned int sense;


}options;


struct conf
{
	unsigned char exist;
	char *cf;
	unsigned int cpu;
/*	signed int cpu68k;
	signed int cpuz80;*/
	unsigned char sound;
	unsigned int samplerate;
	unsigned char rescale;
	unsigned char rotate;
/*	unsigned char showfps;
	unsigned char linescroll;
	unsigned char showtitle;
	signed char screenposition;
	unsigned char fullcache;

	unsigned char extinput;
	unsigned char xorrom;*/
	unsigned char tweak;
	unsigned char hiscore;

	unsigned char z80core;
	unsigned char filter;
	unsigned char spare1;
	unsigned char spare2;
	unsigned char spare3;
	unsigned char spare4;
	unsigned char spare5;
	unsigned int sense;

}conf;

struct capex
{
	unsigned char clock;
	unsigned char tweak;
	unsigned char delayspeed;
	signed char repeatspeed;
	unsigned char list;
	signed char FXshadow;
	float FLshadow;
	unsigned char skin;
	signed char deadzone;
}capex;

struct selector
{
	unsigned char y;
	unsigned char crt_x;
	unsigned int num;
	unsigned int offset_num;
}selector;

struct run
{
	unsigned char y;
	signed char num;
}run;

#include "capex_ecriture.h"
#include "capex_lecture.h"
#include "capex_tri.h"
#include "capex_pixel.h"

#ifdef CAANOO

#define CPU_SPEED_COUNT		12
int mCpuSpeedLookup[CPU_SPEED_COUNT]={300,400,466,533,633,666,700,766,800,833,866,900};

int CpuSpeedNext(int currSpeed)
{
	int newSpeed=currSpeed;
	int i;
	for(i=0;i<CPU_SPEED_COUNT;i++)
	{
		if(mCpuSpeedLookup[i] > currSpeed)
		{
			newSpeed=mCpuSpeedLookup[i];
			break;
		}
	}
	return newSpeed;
}

int CpuSpeedPrevious(int currSpeed)
{
	int newSpeed=currSpeed;
	int i;
	for(i=CPU_SPEED_COUNT-1;i>=0;i--)
	{
		if(mCpuSpeedLookup[i] < currSpeed)
		{
			newSpeed=mCpuSpeedLookup[i];
			break;
		}
	}
	return newSpeed;
}

#define msleep(x) usleep(x*1000)

enum _pollux_clock_ioctl {
    IOCTL_SET_PLL0,
    IOCTL_SET_PLL1,
    IOCTL_GET_PLL0,
    IOCTL_GET_PLL1,
    IOCTL_SET_CLK_DEFUALTS
};


enum _pollux_pll0_index {
   	PLL0_200 = 0,
   	PLL0_300,
    	PLL0_400,
	PLL0_470,
	PLL0_530,
	PLL0_600,
	PLL0_620,
	PLL0_650,    //7
	PLL0_680,    //8
	PLL0_710,    //9
	PLL0_750,    //10
	PLL0_780,
	PLL0_800,
	PLL0_830,
	PLL0_850,
	PLL0_870,
	PLL0_900
};

enum _pollux_pll1_index {
    PLL1_261 = 0,
    PLL1_132_75,
    PLL1_124_2
};

void CaanooCpuSpeedSet(unsigned int MHZ)
{
 	int index=0;
        if(MHZ<=300)
	   	index=1;
	else if(MHZ<=400)
		index=2;
	else if(MHZ<=466)
		index=3;
	else if(MHZ<=533)
		index=4;
	else if(MHZ<=633)
		index=6;
	else if(MHZ<=666)
		index=7;
	else if(MHZ<=700)
		index=9;
	else if(MHZ<=766)
		index=10;
	else if(MHZ<=800)
		index=11;
	else if(MHZ<=833)
		index=12;
	else if(MHZ<=866)
		index=13;
	else if(MHZ<=900)
		index=14;


	int fd_clk = -1;

       fd_clk = open( "/dev/pollux_clock" , O_RDWR);
	if(fd_clk < 0) {
	    printf("error: failed to open \n");
	}
	printf("index: %d\r\n",index);
	printf("MHZ: %d\r\n", MHZ);
	ioctl(fd_clk, IOCTL_SET_PLL0, &index);
       msleep(200);
       close(fd_clk);
}
#endif

static void xtoa (
        unsigned long val,
        char *buf,
        unsigned radix,
        int is_neg
        )
{
        char *p;                /* pointer to traverse string */
        char *firstdig;         /* pointer to first digit */
        char temp;              /* temp char */
        unsigned digval;        /* value of digit */

        p = buf;

        if (is_neg) {
            /* negative, so output '-' and negate */
            *p++ = '-';
            val = (unsigned long)(-(long)val);
        }

        firstdig = p;           /* save pointer to first digit */

        do {
            digval = (unsigned) (val % radix);
            val /= radix;       /* get next digit */

            /* convert to ascii and store */
            if (digval > 9)
                *p++ = (char) (digval - 10 + 'a');  /* a letter */
            else
                *p++ = (char) (digval + '0');       /* a digit */
        } while (val > 0);
		*p=0;

        /* We now have the digit of the number in the buffer, but in reverse
           order.  Thus we reverse them now. */

        //*p-- = '\0';            /* terminate string; p points to last digit */
		*p--;

        do {
            temp = *p;
            *p = *firstdig;
            *firstdig = temp;   /* swap *p and *firstdig */
            --p;
            ++firstdig;         /* advance to next two digits */
        } while (firstdig < p); /* repeat until halfway */
}

/* Actual functions just call conversion helper with neg flag set correctly,
   and return pointer to buffer. */

void nitoa (
        int val,
        char *buf,
        int radix
        )
{
        if (radix == 10 && val < 0)
            xtoa((unsigned long)val, buf, radix, 1);
        else
            xtoa((unsigned long)(unsigned int)val, buf, radix, 0);
        return buf;
}



void redraw_screen(void)
{
	if (flag_TV){
		drawSprite(screen, screen2, 0, 0, offset_x, offset_y, 320, 240);
		SDL_UpdateRect( screen2 , offset_x, offset_y, 320, 240 );
		while ( ((SDL_GetTicks() - fps_count) <<10 ) < 17066 ); //17066 ~ 60Hz | 20480 ~ 50Hz
		fps_count = SDL_GetTicks();
	}else {
	    SDL_Flip(screen);
	    ioctl(fbdev,FBIO_WAITFORVSYNC,&vb);
	}
}

void free_memory(void)
{
	printf("Freeing surfaces\n");
	if (screen2) SDL_FreeSurface(screen2);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(bgs);
	SDL_FreeSurface(bg_temp);
	SDL_FreeSurface(font);
	SDL_FreeSurface(barre);
	SDL_FreeSurface(preview);
	SDL_FreeSurface(title);
	SDL_FreeSurface(help);
	SDL_FreeSurface(credit);
	printf("Freeing memory\n");
	for (ii=0;ii<data.nb_list[0];++ii){
		free(data.name[ii]);
		free(data.zip[ii]);
		free(data.status[ii]);
		free(data.parent[ii]);
	}
}

int exit_prog(void)
{
	//remet timing par defaut
#ifdef GP2X
	set_RAM_Timings(8, 16, 3, 8, 8, 8, 8);
#endif

	//menage avant execution
	free_memory();

	SDL_JoystickClose(0);
	SDL_Quit();
#ifdef GP2X
	chdir("/usr/gp2x");
	execl("gp2xmenu","gp2xmenu",NULL);
#endif
	return 0;

}

void put_string(char *string, unsigned int pos_x, unsigned int pos_y, unsigned char couleur, SDL_Surface *s)
{
	SDL_Rect Src;
	SDL_Rect Dest;

	Src.y = couleur;
	Src.w = 5;
	Src.h = 9;
	Dest.y = pos_y;

	while(*string)
	{
		if (font6x[*string]){
			Src.x = font6x[*string];
			Dest.x = pos_x;
			SDL_BlitSurface(font, &Src, s, &Dest);
		}
		++string;
		pos_x += 6;
	}
}

void put_stringM(char *string, unsigned int pos_x, unsigned int pos_y, unsigned int taille, unsigned char couleur)
{
	SDL_Rect Src;
	SDL_Rect Dest;
	unsigned char caratere;

	if( taille > selector.crt_x ){

		string += selector.crt_x ;

		Src.y = couleur;
		Src.w = 5;
		Src.h = 9;
		Dest.y = pos_y;


		if ( (taille-selector.crt_x) > 65 ) {
			for( caratere=selector.crt_x ; caratere<(selector.crt_x+61) ; ++caratere)
			{
				if (font6x[*string]){
					Src.x = font6x[*string];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, screen, &Dest);
				}
				++string;
				pos_x += 6;
			}
			for( caratere=0 ; caratere<3 ; ++caratere)
			{
				if (font6x[*string]){
					Src.x = font6x[46];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, screen, &Dest);
				}
				pos_x += 6;
			}
		}else{
			while(*string)
			{
				if (font6x[*string]){
					Src.x = font6x[*string];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, screen, &Dest);
				}
				++string;
				pos_x += 6;
			}
		}
	}
}

char ss_prg_credit(void)
{
	#define CREDIT_X	108
	#define CREDIT_Y	62
	#define CREDIT_L	184
	#define CREDIT_H	116

	unsigned int compteur = 1;
	Uint32 Pnoir = SDL_MapRGB(credit->format, 0, 0, 0);
	Uint32 Pblanc = SDL_MapRGB(credit->format, 255, 255, 255 );

	//capture screen actuel
	drawSprite( screen , credit , 0 , 0 , 0 , 0 , 400 , 240 );
	//detourage
	ligneV( credit , CREDIT_X-1 , CREDIT_Y , CREDIT_H , Pnoir );
	ligneV( credit , CREDIT_X+CREDIT_L , CREDIT_Y , CREDIT_H , Pnoir );
	ligneH( credit , CREDIT_X , CREDIT_Y-1 , CREDIT_L , Pnoir);
	ligneH( credit , CREDIT_X , CREDIT_Y+CREDIT_H , CREDIT_L , Pnoir);
	//cadre
	carre_plein( credit , CREDIT_X, CREDIT_Y, CREDIT_L, CREDIT_H, Pblanc);
	carre_plein( credit , CREDIT_X+1, CREDIT_Y+1, CREDIT_L-2, CREDIT_H-2, Pnoir);

	put_string( "CREDIT" , 142 , CREDIT_Y+8 , BLANC , credit );
	put_string( "CAPEX v0.7 by .... Juanvvc" , CREDIT_X+8 , CREDIT_Y+24 , BLEU , credit );
	put_string( "for FBA Emu by .... Juanvvc" , CREDIT_X+8 , CREDIT_Y+34 , BLEU , credit );
	put_string( "Code & design by ..... JyCet" , CREDIT_X+8 , CREDIT_Y+44 , VERT , credit );
	put_string( "Preview pack by ... Juanvvc" , CREDIT_X+8 , CREDIT_Y+54 , VERT , credit );
	put_string( "External skin by ... Pedator" , CREDIT_X+8 , CREDIT_Y+64 , VERT , credit );
	//put_string( "Betatest by ... Yod4z and me" , CREDIT_X+8 , CREDIT_Y+84 , VERT , credit );
	put_string( "Press (START) to quit CAPEX" , 119 , CREDIT_Y+100 , BLANC , credit );

	while(1)
	{
		drawSprite( credit , screen , 0 , 0 , 0 , 0 , 400 , 240 );
		redraw_screen();

		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			if (compteur==0 || (compteur>capex.delayspeed && ((compteur&joy_speed[capex.repeatspeed])==0))){
				if (( event.key.keysym.sym==SDLK_LALT ) || ( event.key.keysym.sym==SDLK_0 )){
					return 1 ;
				}else return 0;
			}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			compteur=0;// reinitialisation joystick
		}
	}
}
void ss_prg_help(void)
{
	#define HELP_X	93
	#define HELP_Y	62
	#define HELP_L	214
	#define HELP_H	116

	unsigned int compteur = 1;
	Uint32 Pnoir = SDL_MapRGB(help->format, 0, 0, 0);
	Uint32 Pblanc = SDL_MapRGB(help->format, 255, 255, 255 );

	//capture screen actuel
	drawSprite( screen , help , 0 , 0 , 0 , 0 , 320 , 240 );
	//detourage
	ligneV( help , HELP_X-1 , HELP_Y , HELP_H , Pnoir );
	ligneV( help , HELP_X+HELP_L , HELP_Y , HELP_H , Pnoir );
	ligneH( help , HELP_X , HELP_Y-1 , HELP_L , Pnoir);
	ligneH( help , HELP_X , HELP_Y+HELP_H , HELP_L , Pnoir);
	//cadre
	carre_plein( help , HELP_X, HELP_Y, HELP_L, HELP_H, Pblanc);
	carre_plein( help , HELP_X+1, HELP_Y+1, HELP_L-2, HELP_H-2, Pnoir);

	put_string( "COLOR HELP" , 130 , HELP_Y+8 , BLANC , help );
	put_string( "RED      missing" , HELP_X+8 , HELP_Y+24 , ROUGE , help );
	put_string( "ORANGE   clone rom detected" , HELP_X+8 , HELP_Y+34 , ORANGE , help );
	put_string( "YELLOW   parent or clone detected" , HELP_X+8 , HELP_Y+44 , JAUNE , help );
	put_string( "         & parent detected" , HELP_X+8 , HELP_Y+54 , JAUNE , help );
	put_string( "GREEN    clone & parent & cache" , HELP_X+8 , HELP_Y+64 , VERT , help );
	put_string( "         detected" , HELP_X+8 , HELP_Y+74 , VERT , help );
	put_string( "BLUE     parent & cache detected" , HELP_X+8 , HELP_Y+84 , BLEU , help );
	put_string( "Any button to return" , 100 , HELP_Y+100 , BLANC , help );

	int Hquit = 0;
	while(!Hquit)
	{
		drawSprite( help , screen , 0 , 0 , 0 , 0 , 320 , 240 );
		redraw_screen();

		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			//if (compteur==0 || (compteur>capex.delayspeed && ((compteur&joy_speed[capex.repeatspeed])==0))){
				//if ( event.key.keysym.sym==SDLK_A ){
				if ( event.key.keysym.sym > 0)
					if (compteur==0) Hquit = 1 ;
				//}
			//}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			compteur=0;// reinitialisation joystick
		}
	}
}

void init_title(void)
{
	//load background interne ou skin
	rw = SDL_RWFromMem(gfx_BG,sizeof(gfx_BG)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (capex.skin){
		if ((fp = fopen( "./skin/capex_bg.bmp" , "r")) != NULL){
			Tmp = SDL_LoadBMP( "./skin/capex_bg.bmp" );
			fclose(fp);
		}
	}
	bg = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);

	//load selector interne ou skin
	rw = SDL_RWFromMem(gfx_SELECTEUR,sizeof(gfx_SELECTEUR)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (capex.skin){
		if ((fp = fopen( "./skin/capex_selector.bmp" , "r")) != NULL){
			Tmp = SDL_LoadBMP( "./skin/capex_selector.bmp" );
			fclose(fp);
		}
	}
	barre = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_SetColorKey(barre ,SDL_SRCCOLORKEY,SDL_MapRGB(barre ->format,255,0,255));

	//load title interne ou skin
	rw = SDL_RWFromMem(gfx_CAPEX,sizeof(gfx_CAPEX)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (capex.skin){
		if ((fp = fopen( "./skin/capex_title.png" , "r")) != NULL){
			Tmp = IMG_Load( "./skin/capex_title.png" );
			fclose(fp);
		}
	}
	title = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_SetColorKey(title ,SDL_SRCCOLORKEY,SDL_MapRGB(title ->format,255,0,255));

	rw = SDL_RWFromMem(gfx_FONT,sizeof(gfx_FONT)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	font = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_FreeRW (rw);
	SDL_SetColorKey(font,SDL_SRCCOLORKEY,SDL_MapRGB(font->format,255,0,255));

	bg_temp = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	bgs = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	help = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	credit = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);

	drawSprite( bg , bgs , 0 , 0 , 0 , 0 , 400 , 240 );
	if (capex.FXshadow < 100) pixel_gamma( bgs );

	preparation_fenetre( bgs , bg , 204 , 3 , 192 , 112 );
	preparation_fenetre( bgs , bg , 4 , 53 , 196 , 62 );
	drawSprite( title , bg, 0, 0, 0, 0, 203, 52);

}

void prep_bg_run(void)
{
	drawSprite( bg , bg_temp , 0 , 0 , 0 , 0 , 400 , 240 );
	preparation_fenetre( bgs , bg_temp , 4 , 119 , 392 , 37 );
	if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 300-preview->w/2, 3, 192, 112);
	//if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 204, 3, 192, 112);

	put_string( "FBA2X clock:" , 6 , 55 , BLANC , bg_temp);
	put_string( "ROM" , 6 , 65 , BLANC , bg_temp);
		switch(capex.list)
		{
			case 0:
				sprintf((char*)g_string, "Database: %d roms" , data.nb_list[0] );
				break;
			case 1:
				sprintf((char*)g_string, "Missing: %d roms" , data.nb_list[1] );
				break;
			case 2:
				sprintf((char*)g_string, "Available: %d roms" , data.nb_list[2] );
				break;
			case 3:
				sprintf((char*)g_string, "Playable: %d roms" , data.nb_list[3] );
				break;
		}
		put_string( g_string , 6 , 105 , BLANC , bg_temp );
}

void prep_bg_options(void)
{
	drawSprite( bg , bg_temp , 0 , 0 , 0 , 0 , 400 , 240 );
	preparation_fenetre( bgs , bg_temp , 4 , 119 , 340 , 118 );
	preparation_fenetre( bgs , bg_temp , 349 , 119 , 47 , 118 );
	if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 300-preview->w/2, 3, 192, 112);
	//if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 204, 3, 192, 112);

	put_string( "FBA2X clock:" , 6 , 55 , BLANC , bg_temp);
	put_string( "ROM" , 6 , 65 , BLANC , bg_temp);
		switch(capex.list)
		{
			case 0:
				sprintf((char*)g_string, "Database: %d roms" , data.nb_list[0] );
				break;
			case 1:
				sprintf((char*)g_string, "Missing: %d roms" , data.nb_list[1] );
				break;
			case 2:
				sprintf((char*)g_string, "Available: %d roms" , data.nb_list[2] );
				break;
			case 3:
				sprintf((char*)g_string, "Playable: %d roms" , data.nb_list[3] );
				break;
		}
		put_string( g_string , 6 , 105 , BLANC , bg_temp );
}

void prep_bg_list(void)
{
	drawSprite( bg , bg_temp , 0 , 0 , 0 , 0 , 400 , 240 );
	preparation_fenetre( bgs , bg_temp , 4 , 119 , 392 , 118 );
	if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 300-preview->w/2, 3, 192, 112);
	//if ( flag_preview )	drawSprite(preview, bg_temp, 0, 0, 204, 3, 192, 112);

	put_string( "FBA2X clock:" , 6 , 55 , BLANC , bg_temp);
	put_string( "ROM" , 6 , 65 , BLANC , bg_temp);
		switch(capex.list)
		{
			case 0:
				sprintf((char*)g_string, "Database: %d roms" , data.nb_list[0] );
				break;
			case 1:
				sprintf((char*)g_string, "Missing: %d roms" , data.nb_list[1] );
				break;
			case 2:
				sprintf((char*)g_string, "Available: %d roms" , data.nb_list[2] );
				break;
			case 3:
				sprintf((char*)g_string, "Playable: %d roms" , data.nb_list[3] );
				break;
		}
		put_string( g_string , 6 , 105 , BLANC , bg_temp );
}

void affiche_BG(void)
{
		drawSprite( bg_temp , screen , 0 , 0 , 0 , 0 , 400 , 240 );

		sprintf((char*)g_string, "%d" , options.cpu );
		put_string( g_string , 96 , 55 , BLANC , screen );

		sprintf((char*)g_string, "%s.zip" , data.zip[listing_tri[capex.list][selector.num]]);
		put_string( g_string , 30 , 65 , BLANC , screen );

		if ( strcmp( data.parent[listing_tri[capex.list][selector.num]] , "fba" ) == 0 ){
			put_string( "Parent rom" , 6 , 75 , BLANC , screen );
		}else{
			sprintf((char*)g_string, "Clone of %s" , data.parent[listing_tri[capex.list][selector.num]]);
			put_string( g_string , 6 , 75 , BLANC , screen );
		}

		if (conf.exist){
			sprintf((char*)g_string, "%s.cf YES" , conf.cf);
			put_string( g_string , 6 , 85 , VERT , screen );
		}else{
			sprintf((char*)g_string, "%s.cf NO" , conf.cf);
			put_string( g_string , 6 , 85 , ROUGE , screen );
		}

		if ( data.status[listing_tri[capex.list][selector.num]] != NULL ){
			put_string( data.status[listing_tri[capex.list][selector.num]] , 6 , 95 , BLANC , screen );
		}

}

void affiche_ligne_options(unsigned char num, unsigned char y)
{
	#define OPTIONS_START_X	8
	#define CONF_START_X	352

	switch (num)
	{
		case OPTION_NUM_FBA2X_CPU:
			sprintf((char*)g_string, "FBA2X clock: %dMHz" , options.cpu );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%dMHz" , conf.cpu );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "---MHz" , CONF_START_X , y , ROUGE , screen );
			}
			break;/*
		case OPTION_NUM_FBA2X_68K:
			sprintf((char*)g_string, "68000 clock: %d%c" , options.cpu68k, 37 );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%d%c" , conf.cpu68k, 37 );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-%" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_Z80:
			sprintf((char*)g_string, "Z80 clock: %d%c" , options.cpuz80, 37 );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%d%c" , conf.cpuz80, 37 );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-%" , CONF_START_X , y , ROUGE , screen );
			}
			break; */
		case OPTION_NUM_FBA2X_SOUND:
			if (options.sound) put_string( "Sound: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Sound: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.sound] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_SAMPLERATE:
			sprintf((char*)g_string, "Audio sample rate: %dHz" , options.samplerate );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%dHz" , conf.samplerate );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-----Hz" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_RESCALE:
			if (options.rescale == 3) put_string( "Scale: Full" , OPTIONS_START_X , y , BLANC , screen );
			else
			if (options.rescale == 2) put_string( "Scale: Best Fit" , OPTIONS_START_X , y , BLANC , screen );
			else if (options.rescale == 1) put_string( "Scale: 2x" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Scale: None" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[1][conf.rescale] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;/*
		case OPTION_NUM_FBA2X_SHOWFPS:
			if (options.showfps) put_string( "Show FPS: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Show FPS: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.showfps] , CONF_START_X , y , VERT , screen );

			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_LINESCROLL:
			if (options.linescroll) put_string( "Line scroll: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Line scroll: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.linescroll] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;*/
		case OPTION_NUM_FBA2X_FRONTEND:
			if (options.rotate == 2) put_string( "Rotate: Vertical" , OPTIONS_START_X , y , BLANC , screen );
			else if (options.rotate == 1) put_string( "Rotate: Horizontal" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Rotate: Auto" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[2][conf.rotate] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;/*
		case OPTION_NUM_FBA2X_SHOWTITLE:
			if (options.showtitle) put_string( "Show 'FBA2X for GP2X' title" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Hide 'FBA2X for GP2X' title" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[2][conf.showtitle] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_SCREENPOSITION:
			sprintf((char*)g_string, "Screen offset position: %d pixel(s)" , options.screenposition );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%d px." , conf.screenposition );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-p" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_FULLCACHE:
			if (options.fullcache) put_string( "Full cache: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Full cache: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.fullcache] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_EXTINPUT:
			if (options.extinput) put_string( "External input device: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "External input device: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.extinput] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_FBA2X_XORROM:
			if (options.xorrom) put_string( "XOR ROM using: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "XOR ROM using: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.xorrom] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;*/
		case OPTION_NUM_FBA2X_TWEAK:
			if (options.tweak == 2) put_string( "68K Emu Core: Force Cyclone" , OPTIONS_START_X , y , BLANC , screen );
			else
			if (options.tweak == 1) put_string( "68K Emu Core: Force M68K" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "68K Emu Core: Auto" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[3][conf.tweak] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;/*
		case OPTION_NUM_FBA2X_HISCORE:
			if (options.hiscore) put_string( "High score save/load: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "High score save/load: Disable" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[0][conf.hiscore] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;*/
		case OPTION_NUM_CAPEX_DEADZONE:
			sprintf((char*)g_string, "Analogue Sensitivity: %d%%" , options.sense );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				sprintf((char*)g_string, "%d%%" , conf.sense );
				put_string( g_string , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "---%%" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_CAPEX_CLOCK:
			if (options.z80core == 1) put_string( "Z80 Emu Core: C Z80" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Z80 Emu Core: DR Z80" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[4][conf.z80core] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;
		case OPTION_NUM_CAPEX_TWEAK:
			if (options.filter == 1) put_string( "Filter: None" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Filter: Default" , OPTIONS_START_X , y , BLANC , screen );
			if (conf.exist){
				put_string( abreviation_cf[5][conf.filter] , CONF_START_X , y , VERT , screen );
			}else{
				put_string( "-" , CONF_START_X , y , ROUGE , screen );
			}
			break;

		case OPTION_NUM_CAPEX_DELAYSPEED:
			sprintf((char*)g_string, "CAPEX delay speed: %d" , capex.delayspeed );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			break;
		case OPTION_NUM_CAPEX_REPEATSPEED:
			sprintf((char*)g_string, "CAPEX repeat speed: %d" , capex.repeatspeed );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			break;
		case OPTION_NUM_CAPEX_LIST:
			if (capex.list == 3) put_string( "Listing view: Playable only" , OPTIONS_START_X , y , BLANC , screen );
			else if (capex.list == 2) put_string( "Listing view: Available only" , OPTIONS_START_X , y , BLANC , screen );
			else if (capex.list == 1) put_string( "Listing view: Missing only" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "Listing view: All" , OPTIONS_START_X , y , BLANC , screen );
			break;
		case OPTION_NUM_CAPEX_SHADOW:
			sprintf((char*)g_string, "CAPEX background shadow: %d%c" , capex.FXshadow, 37 );
			put_string( g_string , OPTIONS_START_X , y , BLANC , screen );
			break;
		case OPTION_NUM_CAPEX_SKIN:
			if (capex.skin) put_string( "External CAPEX skin: Enable" , OPTIONS_START_X , y , BLANC , screen );
			else put_string( "External CAPEX skin: Disable" , OPTIONS_START_X , y , BLANC , screen );
			break;
		case OPTION_NUM_SAVE:
			put_string( "Save all settings" , OPTIONS_START_X , y , flag_save , screen );
			break;
		case OPTION_NUM_SAVE_CF:
			sprintf((char*)g_string, "Save FBA2X settings in %s.cf file" , conf.cf );
			put_string( g_string , OPTIONS_START_X , y , flag_save , screen );
			break;
		case OPTION_NUM_RETURN:
			put_string( "Return to the game list" , OPTIONS_START_X , y , BLANC , screen );
			break;
	}
}

void ss_prg_options(void)
{
	int Quit;
	unsigned int compteur = 1;
	unsigned char y;
	flag_save = VERT;
	options.y = START_Y-1;
	options.num = 0;
	options.offset_num = 0;

	unsigned option_start;

	prep_bg_options();

	Quit=0;
	while(!Quit)
	{
		affiche_BG();

		drawSprite(barre , screen, 0, 0, 4, options.y, 340, 10);
		drawSprite(barre , screen, 0, 0, 349, options.y, 47, 10);

		option_start = START_Y;
		for ( y = options.offset_num ; y<(options.offset_num+13) ; ++y){
			affiche_ligne_options( y , option_start );
			option_start += 9;
		}

		redraw_screen();
		//SDL_Flip(screen);

		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			if (compteur==0 || (compteur>capex.delayspeed && ((compteur&joy_speed[capex.repeatspeed])==0))){
				if ( event.key.keysym.sym==SDLK_DOWN /*&& options.num<12 */){
					//++ options.num;
					//options.y += 9;
					if ( options.num == NOMBRE_OPTIONS && compteur==0 ){
						options.y = START_Y-1;
						options.num = 0;
						options.offset_num = 0;
					}else{
						if (options.num < 6 || options.offset_num == ( NOMBRE_OPTIONS - 12 ) ){
							if ( options.num < NOMBRE_OPTIONS ){
								options.y += 9;
								++options.num;
							}
						}else{
							++options.offset_num;
							++options.num;
						}
					}
				}else if ( event.key.keysym.sym==SDLK_UP /*&& options.num*/ ){
					//-- options.num;
					//options.y -= 9;
					if ( options.num == 0 && compteur==0 ){
						options.y = START_Y -1 + (12*9) ;
						options.num = NOMBRE_OPTIONS;
						options.offset_num = NOMBRE_OPTIONS - 12;
					}else{
						if ( options.num > ( NOMBRE_OPTIONS - 6 ) || options.offset_num == 0 ){
							if (options.num>0){
								options.y -= 9;
								--options.num;
							}
						}else{
							--options.offset_num;
							--options.num;
						}
					}
				}else if ( event.key.keysym.sym==SDLK_LEFT ){
					switch(options.num){
						case OPTION_NUM_CAPEX_DEADZONE:
							flag_save = ROUGE;
							--options.sense;
							if (options.sense < 10) options.sense=100;
							break;

						case OPTION_NUM_FBA2X_CPU:
							flag_save = ROUGE;
#ifdef CAANOO
							options.cpu=CpuSpeedPrevious(options.cpu);
#else
							-- options.cpu;
							if ( options.cpu < 200 ) options.cpu = 200;
#endif
							break;/*
						case OPTION_NUM_FBA2X_68K:
							flag_save = ROUGE;
							-- options.cpu68k;
							if ( options.cpu68k == -51 ) options.cpu68k = 50;
							break;
						case OPTION_NUM_FBA2X_Z80:
							flag_save = ROUGE;
							-- options.cpuz80;
							if ( options.cpuz80 == -51 ) options.cpuz80 = 50;
							break;
						case OPTION_NUM_FBA2X_SCREENPOSITION:
							flag_save = ROUGE;
							--options.screenposition;
							if ( options.screenposition == -33 ) options.screenposition = 32;
							break;*/
						case OPTION_NUM_CAPEX_CLOCK:
							flag_save = ROUGE;
#ifdef CAANOO
							capex.clock=CpuSpeedPrevious(capex.clock);
#endif
#ifdef GP2X
							--capex.clock
							if ( capex.clock == 32 ) capex.clock = 100;
#endif
							break;
						case OPTION_NUM_CAPEX_DELAYSPEED:
							flag_save = ROUGE;
							-- capex.delayspeed;
							if ( capex.delayspeed == 9 ) capex.delayspeed = 50;
							break;
						case OPTION_NUM_CAPEX_REPEATSPEED:
							flag_save = ROUGE;
							-- capex.repeatspeed;
							if ( capex.repeatspeed == -1 ) capex.repeatspeed = 3;
							break;
						case OPTION_NUM_CAPEX_SHADOW:
							flag_save = ROUGE;
							-- capex.FXshadow;
							if ( capex.FXshadow == -1 ) capex.FXshadow = 100;
							break;
					}
                }else if ( event.key.keysym.sym==SDLK_RSHIFT ){
					switch(options.num){

						case OPTION_NUM_FBA2X_CPU:
							flag_save = ROUGE;
#ifndef CAANOO
							options.cpu-=50;
							if ( options.cpu < 200 ) options.cpu = 200;
#endif
							break;

					}
				}else if ( event.key.keysym.sym==SDLK_RIGHT ){
					switch(options.num){
						case OPTION_NUM_CAPEX_DEADZONE:
							flag_save = ROUGE;
							++options.sense;
							if (options.sense > 100) options.sense=10;
							break;

						case OPTION_NUM_FBA2X_CPU:
							flag_save = ROUGE;
#ifdef CAANOO
							options.cpu=CpuSpeedNext(options.cpu);
#else
							++options.cpu;
							if ( options.cpu > 1200 ) options.cpu = 1200;
#endif
							break;/*
						case OPTION_NUM_FBA2X_68K:
							flag_save = ROUGE;
							++options.cpu68k;
							if ( options.cpu68k == 51 ) options.cpu68k = -50;
							break;
						case OPTION_NUM_FBA2X_Z80:
							flag_save = ROUGE;
							++options.cpuz80;
							if ( options.cpuz80 == 51 ) options.cpuz80 = -50;
							break;
						case OPTION_NUM_FBA2X_SCREENPOSITION:
							flag_save = ROUGE;
							++options.screenposition;
							if ( options.screenposition == 33 ) options.screenposition = -32;
							break;*/
						/*case OPTION_NUM_CAPEX_CLOCK:
							flag_save = ROUGE;
#ifdef CAANOO
							capex.clock=CpuSpeedNext(capex.clock);
#else
							++ capex.clock;
							if ( capex.clock > 100 ) capex.clock = 32;
#endif
							break;*/
						case OPTION_NUM_CAPEX_DELAYSPEED:
							flag_save = ROUGE;
							++ capex.delayspeed;
							if ( capex.delayspeed == 51 ) capex.delayspeed = 10;
							break;
						case OPTION_NUM_CAPEX_REPEATSPEED:
							flag_save = ROUGE;
							++ capex.repeatspeed;
							if ( capex.repeatspeed == 4 ) capex.repeatspeed = 0;
							break;
						case OPTION_NUM_CAPEX_SHADOW:
							flag_save = ROUGE;
							++ capex.FXshadow;
							if ( capex.FXshadow == 101 ) capex.FXshadow = 0;
							break;
					}
                    }else if ( event.key.keysym.sym==SDLK_RCTRL ){
					switch(options.num){

						case OPTION_NUM_FBA2X_CPU:
							flag_save = ROUGE;
#ifndef CAANOO
							options.cpu+=50;
							if ( options.cpu > 1200 ) options.cpu = 1200;
#endif
							break;

					}
				}else if ( event.key.keysym.sym==SDLK_HOME ){
					switch(options.num){
						case OPTION_NUM_FBA2X_SOUND:
							flag_save = ROUGE;
							++options.sound;
							options.sound &= 1;
							break;
						case OPTION_NUM_FBA2X_SAMPLERATE:
							flag_save = ROUGE;
							options.samplerate = options.samplerate * 2;
							if ( options.samplerate == 88200 ) options.samplerate = 11025;
							break;
						case OPTION_NUM_FBA2X_RESCALE:
							flag_save = ROUGE;
							++options.rescale;
							if ( options.rescale > 3 ) options.rescale = 0;
							break;/*
						case OPTION_NUM_FBA2X_SHOWFPS:
							flag_save = ROUGE;
							++options.showfps;
							options.showfps &= 1;
							break;
						case OPTION_NUM_FBA2X_LINESCROLL:
							flag_save = ROUGE;
							++options.linescroll;
							options.linescroll &= 1;
							break;*/
						case OPTION_NUM_FBA2X_FRONTEND:
							flag_save = ROUGE;
							++options.rotate;
							if ( options.rotate > 2 ) options.rotate = 0;
							break;/*
						case OPTION_NUM_FBA2X_SHOWTITLE:
							flag_save = ROUGE;
							++options.showtitle;
							options.showtitle &= 1;
							break;
						case OPTION_NUM_FBA2X_FULLCACHE:
							flag_save = ROUGE;
							++options.fullcache;
							options.fullcache &= 1;
							break;
						case OPTION_NUM_FBA2X_EXTINPUT:
							flag_save = ROUGE;
							++options.extinput;
							options.extinput &= 1;
							break;
						case OPTION_NUM_FBA2X_XORROM:
							flag_save = ROUGE;
							++options.xorrom;
							options.xorrom &= 1;
							break;*/
						case OPTION_NUM_FBA2X_TWEAK:
							flag_save = ROUGE;
							++options.tweak;
							if (options.tweak>2) options.tweak= 0;
							break;
                        case OPTION_NUM_CAPEX_CLOCK:
                            flag_save = ROUGE;
							++options.z80core;
							if (options.z80core>1) options.z80core= 0;
							break;
                        case OPTION_NUM_CAPEX_TWEAK:
                            flag_save = ROUGE;
							++options.filter;
							if (options.filter>1) options.filter= 0;
							break;
                        /*
						case OPTION_NUM_FBA2X_HISCORE:
							flag_save = ROUGE;
							++options.hiscore;
							options.hiscore &= 1;
							break;
						case OPTION_NUM_CAPEX_TWEAK:
							flag_save = ROUGE;
							++ capex.tweak;
							if ( capex.tweak == 3 ) capex.tweak = 0;
							break;*/
						case OPTION_NUM_CAPEX_LIST:
							flag_save = ROUGE;
							++capex.list;
							if ( capex.list == NB_FILTRE ) capex.list = 0;
							selector.y = START_Y-1;
							selector.crt_x=0;
							selector.num = 0;
							selector.offset_num = 0;
							break;
						case OPTION_NUM_CAPEX_SKIN:
							flag_save = ROUGE;
							++capex.skin;
							capex.skin &= 1;
							break;
						case OPTION_NUM_SAVE:
							write_cfg();
							flag_save = VERT;
							break;
						case OPTION_NUM_SAVE_CF:
							write_cf( );
							flag_save = VERT;
							load_cf();
							load_cfg();
							break;
						case OPTION_NUM_RETURN:
							prep_bg_list();
							Quit = 1;
							break;
					}
				}
			}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			compteur=0;// reinitialisation joystick
		}

	}
}

void ss_prog_run(void)
{
	#define RUN_START_X	8

	int Quit;
	unsigned int compteur = 1;
	if (conf.exist)
	{
        run.y = START_Y-1;
        run.num = 0;
	}
	else
	{
        run.y = START_Y+8;
        run.num = 1;
	}


	prep_bg_run();

	Quit=0;
	while(!Quit)
	{
		affiche_BG();
		drawSprite(barre , screen, 0, 0, 4, run.y, 392, 10);

		sprintf((char*)g_string, "Launch %s.zip with global settings" , data.zip[listing_tri[capex.list][selector.num]] );
		put_string( g_string , RUN_START_X , START_Y+9 , BLANC , screen );

		sprintf((char*)g_string, "Launch %s.zip with %s.cf settings" , data.zip[listing_tri[capex.list][selector.num]] , conf.cf);
		put_string( g_string , RUN_START_X , START_Y , BLANC , screen );

		put_string( "Return to the game list" , RUN_START_X , START_Y+18 , BLANC , screen );

		put_string( "Quit CAPEX" , RUN_START_X , START_Y+27 , BLANC , screen );

		redraw_screen();
		//SDL_Flip(screen);

		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			if (compteur==0 || (compteur>capex.delayspeed && ((compteur&joy_speed[capex.repeatspeed])==0))){
				if ( event.key.keysym.sym==SDLK_DOWN ){
					++ run.num;
					if ( run.num == 4){
						run.y = START_Y-1;
						run.num = 0;
					}else{
						run.y += 9;
					}
				}else if ( event.key.keysym.sym==SDLK_UP ){
					-- run.num;
					if ( run.num == -1){
						run.y = START_Y -1 + (3*9);
						run.num = 3;
					}else{
						run.y -= 9;
					}
				}else if ( event.key.keysym.sym==SDLK_HOME ){
				    FILE * outlistno;
				    outlistno=fopen("./lastsel.cap","w");
				    fwrite(&selector.num,1,sizeof(int),outlistno);
				    fwrite(&selector.offset_num,1,sizeof(int),outlistno);
				    fwrite(&selector.y,1,sizeof(char),outlistno);
				    fclose(outlistno);
					switch (run.num)
					{
						case 1:

#ifdef GP2X
							Set920Clock(options.cpu);
							if (options.tweak) set_RAM_Timings(6, 4, 1, 1, 1, 2, 2);
							//if (options.gamma != 100 ) set_gamma(options.gamma);
#endif
#ifdef CAANOO
							CaanooCpuSpeedSet(options.cpu);
#endif

							ar=0;
							argument[ ar ] = "fba.sh";
							++ar;

							sprintf((char*)g_string, "roms/%s.zip" , data.zip[listing_tri[capex.list][selector.num]]);
							argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
							strcpy(argument[ ar ],g_string);
							++ar;

							/*sprintf((char*)g_string, "--deadzone=%d" , capex.deadzone);
							argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
							strcpy(argument[ ar ],g_string);
							++ar;
*/

							sprintf((char*)g_string, "--clock=%d" , options.cpu);
							argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
							strcpy(argument[ ar ],g_string);
							++ar;

							sprintf((char*)g_string, "--sense=%d" , options.sense);
							argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
							strcpy(argument[ ar ],g_string);
							++ar;


/*
							if (options.cpu68k){
								sprintf((char*)g_string, "--68kclock=%d" , options.cpu68k);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;
							}
							if (options.cpuz80){
								sprintf((char*)g_string, "--z80clock=%d" , options.cpuz80);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;
							}*/
							if (options.sound){
								argument[ ar ] = "--sound-sdl";
								++ar;

								sprintf((char*)g_string, "--samplerate=%d" , options.samplerate);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;
							}else{
								argument[ ar ] = "--no-sound";
								++ar;
							}

                            if (options.rescale == 3){
								//argument[ ar ] = "--hwho-rescale";
								argument[ ar ] = "--scaling=3";
								++ar;
							}else if (options.rescale == 2){
								argument[ ar ] = "--scaling=2";
								++ar;
							}else if (options.rescale == 1){
								argument[ ar ] = "--scaling=1";
								++ar;
							}else{
								argument[ ar ] = "--scaling=0";
								++ar;
							}

							if (options.rotate == 2){
								argument[ ar ] = "--rotate=2";
								++ar;
							}else if (options.rotate == 1){
								argument[ ar ] = "--rotate=1";
								++ar;
							}else{
								argument[ ar ] = "--rotate=0";
								++ar;
							}

							if (options.tweak == 2){
								argument[ ar ] = "--force-c68k";
								++ar;
							}else if (options.tweak == 1){
								argument[ ar ] = "--force-m68k";
								++ar;
							}

							if (options.z80core == 1){
                                    argument[ ar ] = "--z80core=1";
                                    ++ar;
                                }else if (options.z80core == 0){
                                    argument[ ar ] = "--z80core=0";
                                    ++ar;
                                }

                                if (options.filter == 1){
                                    argument[ ar ] = "--filter=1";
                                    ++ar;
                                }else if (options.filter == 0){
                                    argument[ ar ] = "--filter=0";
                                    ++ar;
                                }

							if (options.showfps){
								argument[ ar ] = "--showfps";
								++ar	;
							}
/*
							if (options.linescroll)	argument[ ar ] = "--linescroll";
							else	argument[ ar ] = "--no-linescroll";
							++ar	;
*/
							if (options.frontend){
								argument[ ar ] = "--frontend=./fbacapex.sh";
								++ar	;
							}
/*
							if (options.showtitle) argument[ ar ] = "--showtitle";
							else argument[ ar ] = "--no-showtitle";
							++ar	;

							if (options.screenposition){
								sprintf((char*)g_string, "--screen-position=%d" , options.screenposition);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;
							}

							if (options.fullcache) argument[ ar ] = "--fullcache";
							else argument[ ar ] = "--no-fullcache";
							++ar	;

							if (options.extinput) argument[ ar ] = "--extinput";
							else argument[ ar ] = "--no-extinput";
							++ar	;

							if (options.xorrom) argument[ ar ] = "--xorrom";
							else argument[ ar ] = "--no-xorrom";
							++ar	;

							if (options.tweak) argument[ ar ] = "--tweak";
							else argument[ ar ] = "--no-tweak";
							++ar	;

							if (options.hiscore) argument[ ar ] = "--hiscore";
							else argument[ ar ] = "--no-hiscore";
							++ar	;
*/
							argument[ ar ] = (char *)0;
							path = "fba.sh";

                            close(fbdev);
							free_memory();
							SDL_Quit();
							int i;
                            for (i=0;environ[i];i++)
                            {
                                if (strstr(environ[i],"SDL_OMAP_LAYER_SIZE="))
                                {
                                    printf("found layer size %d\n",options.rescale);
                                    if (options.rescale == 6)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=480x480");
                                    }
                                    else if (options.rescale == 5)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=600x480");
                                    }
                                    else if (options.rescale == 3)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=300x480");
                                        printf("setting to 300x480\n");

                                    }
                                    else
                                    strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=768x480");
                                }
                                if (strstr(environ[i],"SDL_OMAP_VSYNC="))
                                {
                                    strcpy(environ[i],"SDL_OMAP_VSYNC=0");
                                }
                            }
							execv(path, argument);
							break;
						case 0:
							if (conf.exist){
#ifdef GP2X
								Set920Clock(conf.cpu);
								if (options.tweak) set_RAM_Timings(6, 4, 1, 1, 1, 2, 2);
#endif
#ifdef CAANOO
								CaanooCpuSpeedSet(options.cpu);
#endif
								//if (options.gamma != 100 ) set_gamma(options.gamma);

								ar=0;
								argument[ ar ] = "fba.sh";
								++ar;

								sprintf((char*)g_string, "roms/%s.zip" , data.zip[listing_tri[capex.list][selector.num]]);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;

								sprintf((char*)g_string, "--clock=%d" , conf.cpu);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;

								sprintf((char*)g_string, "--sense=%d" , conf.sense);
								argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
								strcpy(argument[ ar ],g_string);
								++ar;
/*
								if (conf.cpu68k){
									sprintf((char*)g_string, "--68kclock=%d" , conf.cpu68k);
									argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
									strcpy(argument[ ar ],g_string);
									++ar;
								}
								if (conf.cpuz80){
									sprintf((char*)g_string, "--z80clock=%d" , conf.cpuz80);
									argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
									strcpy(argument[ ar ],g_string);
									++ar;
								}*/
								if (conf.sound){
									argument[ ar ] = "--sound-sdl";
									++ar;

									sprintf((char*)g_string, "--samplerate=%d" , conf.samplerate);
									argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
									strcpy(argument[ ar ],g_string);
									++ar;
								}else{
									argument[ ar ] = "--no-sound";
									++ar;
								}

                            if (conf.rescale == 3){
								//argument[ ar ] = "--hwho-rescale";
								argument[ ar ] = "--scaling=3";
								++ar;
							}else if (conf.rescale == 2){
								argument[ ar ] = "--scaling=2";
								++ar;
							}else if (conf.rescale == 1){
								argument[ ar ] = "--scaling=1";
								++ar;
							}else{
								argument[ ar ] = "--scaling=0";
								++ar;
							}

							if (conf.rotate == 2){
								argument[ ar ] = "--rotate=2";
								++ar;
							}else if (conf.rotate == 1){
								argument[ ar ] = "--rotate=1";
								++ar;
							}else{
								argument[ ar ] = "--rotate=0";
								++ar;
							}

								if (conf.tweak == 2){
                                    argument[ ar ] = "--force-c68k";
                                    ++ar;
                                }else if (conf.tweak == 1){
                                    argument[ ar ] = "--force-m68k";
                                    ++ar;
                                }

                                if (conf.z80core == 1){
                                    argument[ ar ] = "--z80core=1";
                                    ++ar;
                                }else if (conf.z80core == 0){
                                    argument[ ar ] = "--z80core=0";
                                    ++ar;
                                }

                                if (conf.filter == 1){
                                    argument[ ar ] = "--filter=1";
                                    ++ar;
                                }else if (conf.filter == 0){
                                    argument[ ar ] = "--filter=0";
                                    ++ar;
                                }
/*
								if (conf.showfps){
									argument[ ar ] = "--showfps";
									++ar	;
								}

								if (conf.linescroll)	argument[ ar ] = "--linescroll";
								else	argument[ ar ] = "--no-linescroll";
								++ar	;
*/
								if (options.frontend){
									argument[ ar ] = "--frontend=./fbacapex.gpe";
									++ar	;
								}
/*
								if (conf.showtitle) argument[ ar ] = "--showtitle";
								else argument[ ar ] = "--no-showtitle";
								++ar	;

								if (conf.screenposition){
									sprintf((char*)g_string, "--screen-position=%d" , conf.screenposition);
									argument[ ar ] = (char*) calloc( strlen(g_string) + 1 , sizeof(char));
									strcpy(argument[ ar ],g_string);
									++ar;
								}

								if (options.fullcache) argument[ ar ] = "--fullcache";
								else argument[ ar ] = "--no-fullcache";
								++ar	;

								if (options.extinput) argument[ ar ] = "--extinput";
								else argument[ ar ] = "--no-extinput";
								++ar	;

								if (options.xorrom) argument[ ar ] = "--xorrom";
								else argument[ ar ] = "--no-xorrom";
								++ar	;

								if (options.tweak) argument[ ar ] = "--tweak";
								else argument[ ar ] = "--no-tweak";
								++ar	;

								if (options.hiscore) argument[ ar ] = "--hiscore";
								else argument[ ar ] = "--no-hiscore";
								++ar	;
*/
								argument[ ar ] = (char *)0;
								path = "fba.sh";

                                close(fbdev);
								free_memory();
								SDL_Quit();

								int i;
                            for (i=0;environ[i];i++)
                            {
                                if (strstr(environ[i],"SDL_OMAP_LAYER_SIZE="))
                                {
                                    if (conf.rescale == 6)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=480x480");
                                    }
                                    else if (conf.rescale == 5)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=600x480");
                                    }
                                    else if (conf.rescale == 3)
                                    {
                                        strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=300x480");
                                    }
                                    else
                                    strcpy(environ[i],"SDL_OMAP_LAYER_SIZE=768x480");
                                }
                                if (strstr(environ[i],"SDL_OMAP_VSYNC="))
                                {
                                    strcpy(environ[i],"SDL_OMAP_VSYNC=0");
                                }
                            }

								execv(path, argument);
							}
							break;
						case 2:
							prep_bg_list();
							Quit = 1;
							break;
						case 3:
							exit_prog();
							break;
					}
				}
			}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			compteur=0;// reinitialisation joystick
		}
	}

}

int findfirst(int l,int s)
{
    l-=32;
    //printf("letter to find %d\n",l);
    int z=0;
    while (z<data.nb_list[capex.list])
    {
        //printf("%s\n",data.name[listing_tri[capex.list][z]]);
        if (data.name[listing_tri[capex.list][z]][0]==l)
        {
            s=z;
            z=data.nb_list[capex.list];
        }
        z++;
    }
    //printf("go to line %d\n",s);
    if (s>data.nb_list[capex.list]-13) s=data.nb_list[capex.list]-13;
    return s;
}

void scan_roms()
{
    FILE * dumpdata;
    put_string( "READING GAME LIST" , 130 , 100 ,BLANC, help );
	//drawSprite(help,screen,0,0,0,0,help->w,help->h);

	redraw_screen();

	if (lecture_zipname()) ErrorQuit = 1;
	else{
		tri_alphabeticAZ(0,data.nb_list[0]);
		if ( lecture_rominfo() ) ErrorQuit = 2;
		else{
			lecture_rom_jouable();
			ErrorQuit = 0;
		}
	}

	printf("Finished parsing roms\n");


	data.nb_list[1] = 0;
	data.nb_list[2] = 0;
	data.nb_list[3] = 0;
	for ( ii=0 ; ii<data.nb_list[0] ; ++ii){
		if (data.etat[listing_tri[0][ii]] == ROUGE ) {
			listing_tri[1][data.nb_list[1]] = listing_tri[0][ii];
			++data.nb_list[1];
		}else{
			listing_tri[2][data.nb_list[2]] = listing_tri[0][ii];
			++data.nb_list[2];

			if (data.etat[listing_tri[0][ii]] == VERT || data.etat[listing_tri[0][ii]] == BLEU ) {
				listing_tri[3][data.nb_list[3]] = listing_tri[0][ii];
				++data.nb_list[3];
			}
		}
	}

    printf("Finished something roms\n");

    dumpdata=fopen("gamelist.cpx","wb");
    if (dumpdata)
    {
        int z;
        char buffer[20];
        	SDL_Rect progrect;
	progrect.x=130;
	progrect.y=100;
	progrect.w=150;
	progrect.h=10;
		char prog[256];

        fwrite(&data.nb_cache,1,sizeof(data.nb_cache),dumpdata);
        fwrite(&data.nb_rom,1,sizeof(data.nb_rom),dumpdata);
        for (i=0;i<NB_FILTRE;i++)
        {
            fwrite(&data.nb_list[i],1,sizeof(data.nb_list[i]),dumpdata);
        }
        for (i=0;i<NB_MAX_GAMES;i++)
        {
            z=data.nb_namelength[i];
            fwrite(&z,1,sizeof(z),dumpdata);
            fwrite(data.name[i],1,z,dumpdata);
            z=data.nb_ziplength[i];
            fwrite(&z,1,sizeof(z),dumpdata);
            fwrite(data.zip[i],1,z,dumpdata);
            z=data.nb_statuslength[i];
            fwrite(&z,1,sizeof(z),dumpdata);
            fwrite(data.status[i],1,z,dumpdata);
            z=data.nb_parentlength[i];
            fwrite(&z,1,sizeof(z),dumpdata);
            fwrite(data.parent[i],1,z,dumpdata);
            fwrite(&data.etat[i],1,sizeof(data.etat[i]),dumpdata);
            fwrite(&data.longueur[i],1,sizeof(data.longueur[i]),dumpdata);

            nitoa((int)i+1,buffer,10);
            strcpy(prog,"WRITING GAME LIST: ");
            strcat(prog,buffer);
            SDL_FillRect(screen,&progrect,0);
			put_string( prog , 130 , 100 ,BLANC, screen );
			SDL_Flip(screen);

        }
        fwrite(&data.long_max,1,sizeof(data.long_max),dumpdata);
        fwrite(&listing_tri[0][0],1,sizeof(listing_tri),dumpdata);
    }
    fclose(dumpdata);
    	selector.y = START_Y-1;
	selector.crt_x=0;
	selector.num = 0;
	selector.offset_num = 0;

}

int main(int argc, char *argv[])
{
	printf("CAPEX frontend for FBA2X\n");
	printf("v0.1 by JYCET\n");

	int Quit ;
	//int Write = 0;
	unsigned int zipnum;
	unsigned int y;
	unsigned int compteur = 0;


    for (i=0;environ[i];i++)
    {
        if (strstr(environ[i],"SDL_OMAP_VSYNC="))
        {
            strcpy(environ[i],"SDL_OMAP_VSYNC=0");
        }
    }


	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

#ifdef GP2X
	if(!gp2x_dev) gp2x_dev = open("/dev/mem", O_RDWR);
	gp2x_memregs=(unsigned short *)mmap(0, 0x10000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_dev, 0xc0000000);

	// TV OUT
	if((gp2x_memregs[0x2800>>1]&0x100)){
		if (gp2x_memregs[0x2818>>1]  == 287){ //PAL
			screen2 = SDL_SetVideoMode(360, 288, 16, SDL_HWSURFACE);
			offset_x = 7;
			offset_y = 17;
		}else if (gp2x_memregs[0x2818>>1]  == 239){ //NTSC
			screen2 = SDL_SetVideoMode(360, 240, 16, SDL_HWSURFACE);
			offset_x = 7;
			offset_y = 0;
		}
		screen = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
		flag_TV = 1;
	}else{
#endif
		//LCD
		screen = SDL_SetVideoMode(400, 240, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
		flag_TV = 0;
#ifdef GP2X
	}
#endif

	SDL_ShowCursor (0); //desactive souris
	//SDL_JoystickOpen(0);

    fbdev=open("/dev/fb0", O_RDONLY);


	//precalcul font6 x coordonn�e
	for (i=0;i<32;++i) font6x[i]=0;
	for (i=32;i<255;++i) font6x[i]=(i-32)*6;

    load_cfg();
	init_title();

	FILE * dumpdata;

	dumpdata=fopen("gamelist.cpx","rb");
	if (dumpdata)
	{
	    int z;
	    fread(&data.nb_cache,1,sizeof(data.nb_cache),dumpdata);
        fread(&data.nb_rom,1,sizeof(data.nb_rom),dumpdata);
        for (i=0;i<NB_FILTRE;i++)
        {
            fread(&data.nb_list[i],1,sizeof(data.nb_list[i]),dumpdata);
        }
	    for (i=0;i<NB_MAX_GAMES;i++)
        {
            fread(&z,1,sizeof(z),dumpdata);
            data.name[i]=(char*)malloc(z);
            fread(data.name[i],1,z,dumpdata);
            fread(&z,1,sizeof(z),dumpdata);
            data.zip[i]=(char*)malloc(z);
            fread(data.zip[i],1,z,dumpdata);
            fread(&z,1,sizeof(z),dumpdata);
            data.status[i]=(char*)malloc(z);
            fread(data.status[i],1,z,dumpdata);
            fread(&z,1,sizeof(z),dumpdata);
            data.parent[i]=calloc(z,sizeof(char));
            fread(data.parent[i],1,z,dumpdata);
            fread(&data.etat[i],1,sizeof(data.etat[i]),dumpdata);
            fread(&data.longueur[i],1,sizeof(data.longueur[i]),dumpdata);
        }
            fread(&data.long_max,1,sizeof(data.long_max),dumpdata);
            fread(&listing_tri[0][0],1,sizeof(listing_tri),dumpdata);
            fclose(dumpdata);

            	FILE * outlistno;
    outlistno=fopen("./lastsel.cap","r");
    if (outlistno)
    {
        fread(&selector.num,1,sizeof(int),outlistno);
        fread(&selector.offset_num,1,sizeof(int),outlistno);
        fread(&selector.y,1,sizeof(char),outlistno);
        printf("%u   %u   %c\n",selector.num,selector.offset_num,selector.y);
        fclose(outlistno);
        if (selector.num>data.nb_list[capex.list])
        {
            selector.y = START_Y-1;
            selector.crt_x=0;
            selector.num = 0;
            selector.offset_num = 0;
        }
        if (selector.num>data.nb_list[capex.list]-13)
        {
            selector.num=data.nb_list[capex.list]-13;
            selector.offset_num=selector.num;
            selector.y = START_Y-1;
        }
    }
	}
    else
    {

        scan_roms();
    }


/*
	FILE * logFile;
	printf("Debut generation log.txt\n");
	logFile = fopen ("log.txt","w");
	fprintf(logFile, "Name, Parent, Title\n");
	fprintf(logFile, "------ ------- -----\n");
	for ( ii=0 ; ii<data.nb_list[0] ; ++ii){
		fprintf(logFile, "%s, %s, %s\n", data.zip[ii], data.parent[ii], data.name[ii]);
		printf("|");
	}
	printf("\nFin generation log.txt\n");
	fclose (logFile);
*/
#ifdef GP2X
	Set920Clock(capex.clock);
	if (capex.tweak == 0 ) set_RAM_Timings(8, 16, 3, 8, 8, 8, 8);
	else if (capex.tweak == 1 ) set_RAM_Timings(7, 10, 2, 4, 4, 5, 5);
	else if (capex.tweak == 2 ) set_RAM_Timings(6, 4, 1, 1, 1, 2, 2);
#endif
#ifdef CAANOO
	CaanooCpuSpeedSet(capex.clock);
#endif
	//set_gamma(100);







	flag_preview = 0;
	load_preview(selector.num);
	load_cf();
	prep_bg_list();

	Quit = 0;
	while (!Quit)
	{
		affiche_BG();

		drawSprite(barre , screen, 0, 0, 4, selector.y, 392, 10);

		if (ErrorQuit == 1) put_string("erreur de lecture zipname.fba" , 8 , 220 , 0 , screen );
		else if (ErrorQuit == 2) put_string("erreur de lecture rominfo.fba" , 8 , 220 , 0 , screen );
		else{
			zipnum = START_Y;
			if ( data.nb_list[capex.list] < 14){
				for ( y = 0 ; y<data.nb_list[capex.list] ; ++y){
					put_stringM(data.name[listing_tri[capex.list][y]] , 8 , zipnum, data.longueur[listing_tri[capex.list][y]] , data.etat[listing_tri[capex.list][y]] );
					zipnum += 9;
				}
			}else{
				for ( y = selector.offset_num ; y<(selector.offset_num+13) ; ++y){
					put_stringM(data.name[listing_tri[capex.list][y]] , 8 , zipnum, data.longueur[listing_tri[capex.list][y]] , data.etat[listing_tri[capex.list][y]] );
					zipnum += 9;
				}
			}
		}


		redraw_screen();
		//SDL_Flip(screen);


		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			//printf("but: %d\r\n",event.key.keysym.sym);
			if (compteur==0 || (compteur>capex.delayspeed && ((compteur&joy_speed[capex.repeatspeed])==0))){
			    if ((event.key.keysym.sym>=SDLK_a) && (event.key.keysym.sym<=SDLK_z)){
			        selector.num=findfirst(event.key.keysym.sym,selector.num);
			        selector.offset_num=selector.num;
			        selector.y = START_Y-1;
			    }
			    if (event.key.keysym.sym==SDLK_PAGEUP){
			        scan_roms();
			    }
				if (event.key.keysym.sym==SDLK_DOWN){
					if ( selector.num == (data.nb_list[capex.list]-1) && compteur==0 ){
						selector.y = START_Y-1;
						selector.num = 0;
						selector.offset_num = 0;
					}else{
						if (data.nb_list[capex.list] < 14){
								if (selector.num < (data.nb_list[capex.list]-1) ) {
									selector.y+=9;
									++selector.num;
									if (compteur==0){
										load_preview(selector.num);
										load_cf();
									}
								}
						}else{
							if (selector.num<7 || selector.offset_num==(data.nb_list[capex.list]-13)){
								if (selector.num < (data.nb_list[capex.list]-1)){
									selector.y+=9;
									++selector.num;
									if (compteur==0){
										load_preview(selector.num);
										load_cf();
									}
								}
							}else{
								++selector.offset_num;
								++selector.num;
								if (compteur==0){
									load_preview(selector.num);
									load_cf();
								}
							}
						}
					}
				}else if (event.key.keysym.sym==SDLK_UP){
					if ( selector.num==0 && compteur==0 ){
						selector.num = data.nb_list[capex.list] - 1 ;
						if (data.nb_list[capex.list] < 14){
							selector.y = START_Y -1 + ( ( data.nb_list[capex.list] - 1 ) *9 ) ;
							//selector.offset_num = 0;
						}else{
							selector.y = START_Y -1 + (12*9) ;
							selector.offset_num = data.nb_list[capex.list] - 13;
						}
					}else{
						if ( selector.num > (data.nb_list[capex.list]-7) || selector.offset_num==0){
							if (selector.num>0){
								selector.y-=9;
								--selector.num;
								if (compteur==0){
									load_preview(selector.num);
									load_cf();
								}
							}
						}else{
							--selector.offset_num;
							--selector.num;
							if (compteur==0){
								load_preview(selector.num);
								load_cf();
							}
						}
					}
				}else if (event.key.keysym.sym==SDLK_LEFT && selector.crt_x>0){
					--selector.crt_x;
				}else if (event.key.keysym.sym==SDLK_RIGHT && selector.crt_x<data.long_max-53 ){
					++selector.crt_x;
				}else if (event.key.keysym.sym==SDLK_LALT){
					if ( ss_prg_credit() ) Quit = 1;
                }else if (event.key.keysym.sym==SDLK_0){
					if ( ss_prg_credit() ) Quit = 1;
				}else if (event.key.keysym.sym==SDLK_HOME ){
					// executer l'emu
					//if ( data.etat[listing_tri[capex.list][selector.num]] == VERT || data.etat[listing_tri[capex.list][selector.num]] == BLEU ){
					if ( data.etat[listing_tri[capex.list][selector.num]] > ROUGE ){

						ss_prog_run();
					}
				//}else if (event.key.keysym.sym==SDLK_X && conf.exist){
					// executer l'emu
					//if ( data.etat[listing_tri[capex.list][selector.num]] == VERT || data.etat[listing_tri[capex.list][selector.num]] == BLEU ){
					//if ( data.etat[listing_tri[capex.list][selector.num]] > ROUGE ){


					//}
				}else if( event.key.keysym.sym == SDLK_PAGEDOWN ){
					if (compteur==0) ss_prg_help();
				}else if( event.key.keysym.sym == SDLK_LCTRL ){
					ss_prg_options();
				}
			}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			if (compteur){
				load_preview(selector.num);
				load_cf();
			}
			compteur=0;// reinitialisation joystick
		}

	}

	exit_prog();
	return 0;
}


/*EOF*/
