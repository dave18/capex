/*  CAPEX for GP2X

    Copyright (C) 2007  JyCet

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

#if defined(GP2X)
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
#elif defined(CAANOO)
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
#else
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (2)
#define GP2X_BUTTON_LEFT            (3)
#define GP2X_BUTTON_RIGHT           (1)
#define GP2X_BUTTON_UPLEFT          (10)
#define GP2X_BUTTON_UPRIGHT         (10)
#define GP2X_BUTTON_DOWNLEFT        (10)
#define GP2X_BUTTON_DOWNRIGHT       (10)
#define GP2X_BUTTON_CLICK           (11)
#define GP2X_BUTTON_A               (6)
#define GP2X_BUTTON_B               (4)
#define GP2X_BUTTON_X               (7)
#define GP2X_BUTTON_Y               (5)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (9)
#define GP2X_BUTTON_SELECT          (8)
#define GP2X_BUTTON_VOLUP           (10)
#define GP2X_BUTTON_VOLDOWN         (11)
#endif

#define START_X	8
#define START_Y	120

#define NB_FILTRE	4
//#define NB_MAX_GAMES	2048
#define NB_MAX_GAMES	6000
#define N_ARG 50

#define BLANC	0
#define ROUGE	9
#define ORANGE	18
#define JAUNE	27
#define VERT	36
#define BLEU	45

#define OPTION_NUM_FBA2X_CPU		0
#define OPTION_NUM_FBA2X_68K		91
#define OPTION_NUM_FBA2X_Z80		92
#define OPTION_NUM_FBA2X_SOUND		1
#define OPTION_NUM_FBA2X_SAMPLERATE	2
#define OPTION_NUM_FBA2X_RESCALE	3
#define OPTION_NUM_FBA2X_SHOWFPS	96
#define OPTION_NUM_FBA2X_LINESCROLL	97
#define OPTION_NUM_FBA2X_FRONTEND	4
#define OPTION_NUM_FBA2X_SHOWTITLE	99
#define OPTION_NUM_FBA2X_SCREENPOSITION	910
#define OPTION_NUM_FBA2X_FULLCACHE	911

#define OPTION_NUM_FBA2X_EXTINPUT	 912
#define OPTION_NUM_FBA2X_XORROM		913
#define OPTION_NUM_FBA2X_TWEAK		5
#define OPTION_NUM_FBA2X_HISCORE	915

#define OPTION_NUM_CAPEX_CLOCK		6
#define OPTION_NUM_CAPEX_TWEAK		7
#define OPTION_NUM_CAPEX_DELAYSPEED	8
#define OPTION_NUM_CAPEX_REPEATSPEED	9
#define OPTION_NUM_CAPEX_LIST			10
#define OPTION_NUM_CAPEX_SHADOW		11
#define OPTION_NUM_CAPEX_SKIN			12
#define OPTION_NUM_CAPEX_DEADZONE		13

#define OPTION_NUM_SAVE				14
#define OPTION_NUM_SAVE_CF			15
#define OPTION_NUM_RETURN			16


/*#define OPTION_NUM_FBA2X_CPU		0
#define OPTION_NUM_FBA2X_68K		1
#define OPTION_NUM_FBA2X_Z80		2
#define OPTION_NUM_FBA2X_SOUND		3
#define OPTION_NUM_FBA2X_SAMPLERATE	4
#define OPTION_NUM_FBA2X_RESCALE	5
#define OPTION_NUM_FBA2X_SHOWFPS	6
#define OPTION_NUM_FBA2X_LINESCROLL	7
#define OPTION_NUM_FBA2X_FRONTEND	8
#define OPTION_NUM_FBA2X_SHOWTITLE	9
#define OPTION_NUM_FBA2X_SCREENPOSITION	10
#define OPTION_NUM_FBA2X_FULLCACHE	11

#define OPTION_NUM_FBA2X_EXTINPUT	12
#define OPTION_NUM_FBA2X_XORROM		13
#define OPTION_NUM_FBA2X_TWEAK		14
#define OPTION_NUM_FBA2X_HISCORE	15

#define OPTION_NUM_CAPEX_CLOCK		16
#define OPTION_NUM_CAPEX_TWEAK		17
#define OPTION_NUM_CAPEX_DELAYSPEED	18
#define OPTION_NUM_CAPEX_REPEATSPEED	19
#define OPTION_NUM_CAPEX_LIST			20
#define OPTION_NUM_CAPEX_SHADOW		21
#define OPTION_NUM_CAPEX_SKIN			22

#define OPTION_NUM_SAVE				23
#define OPTION_NUM_SAVE_CF			24
#define OPTION_NUM_RETURN			25*/
/*#define OPTION_NUM_FBA2X_CPU		0
#define OPTION_NUM_FBA2X_68K		1
#define OPTION_NUM_FBA2X_Z80		2
#define OPTION_NUM_FBA2X_SOUND		3
#define OPTION_NUM_FBA2X_SAMPLERATE	4
#define OPTION_NUM_FBA2X_RESCALE	5
#define OPTION_NUM_FBA2X_SHOWFPS	6
#define OPTION_NUM_FBA2X_LINESCROLL	7
#define OPTION_NUM_FBA2X_FRONTEND	8
#define OPTION_NUM_FBA2X_SHOWTITLE	9
#define OPTION_NUM_FBA2X_SCREENPOSITION	10
#define OPTION_NUM_FBA2X_FULLCACHE	11

#define OPTION_NUM_FBA2X_EXTINPUT	12
#define OPTION_NUM_FBA2X_XORROM		13
#define OPTION_NUM_FBA2X_TWEAK		14
#define OPTION_NUM_FBA2X_HISCORE	15

#define OPTION_NUM_CAPEX_CLOCK		16
#define OPTION_NUM_CAPEX_TWEAK		17
#define OPTION_NUM_CAPEX_DELAYSPEED	18
#define OPTION_NUM_CAPEX_REPEATSPEED	19
#define OPTION_NUM_CAPEX_LIST			20
#define OPTION_NUM_CAPEX_SHADOW		21
#define OPTION_NUM_CAPEX_SKIN			22
#define OPTION_NUM_SAVE				23
#define OPTION_NUM_SAVE_CF			24
#define OPTION_NUM_RETURN			25*/


#define NOMBRE_OPTIONS				OPTION_NUM_RETURN

unsigned char joy_speed[4]={0,1,3,7};

static char *abreviation_cf[6][7]={
	{"Disable","Enable","","","","",""},
	{"Scaled","","","Rotate","Rot Scl","Rot Sl2","Rot Sl3"},
	{"Hide","Show","","","","",""},
	{"Auto","Fc M68K","Fc C68K","","","",""},
	{"DR Z80","C Z80","","","","",""},
	{"Default","None","","","","",""}
};

void ligneH(SDL_Surface* screenSurface, int x, int y, int w, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;

  SDL_FillRect(screenSurface, &r, coul);
}

void ligneV(SDL_Surface* screenSurface, int x, int y, int h, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = h;

  SDL_FillRect(screenSurface, &r, coul);
}

void carre_plein(SDL_Surface* screenSurface, int x, int y, int w, int h, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;

  SDL_FillRect(screenSurface, &r, coul);
}

void drawSprite(SDL_Surface* imageSurface, SDL_Surface* screenSurface, int srcX, int srcY, int dstX, int dstY, int width, int height)
{
	SDL_Rect srcRect;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = width;
	srcRect.h = height;

	SDL_Rect dstRect;
	dstRect.x = dstX;
	dstRect.y = dstY;
	dstRect.w = width;
	dstRect.h = height;

	SDL_BlitSurface(imageSurface, &srcRect, screenSurface, &dstRect);
}

void preparation_fenetre(SDL_Surface *src, SDL_Surface *dest, int win_x , int win_y , int win_l , int win_h)
{
	Uint32 Pnoir = SDL_MapRGB(dest->format, 0, 0, 0);
	//preparation surface
	drawSprite( src , dest , win_x , win_y , win_x , win_y , win_l , win_h );
	ligneV( dest , win_x-1 , win_y , win_h , Pnoir );
	ligneV( dest , win_x+win_l , win_y , win_h , Pnoir );
	ligneH( dest , win_x , win_y-1 , win_l , Pnoir);
	ligneH( dest , win_x , win_y+win_h , win_l , Pnoir);
}
