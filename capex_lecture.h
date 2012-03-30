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

void put_string(char *string, unsigned int pos_x, unsigned int pos_y, unsigned char couleur, SDL_Surface *s);
void load_cfg()
{
	char arg1[128];
	signed long argd;
	char ligne[256];

	// force les settings si un parametre est absent
	options.cpu = 600;
/*	options.cpu68k = 0;
	options.cpuz80 = 0;*/
	options.sound = 1;
	options.samplerate = 11025;
	options.rescale = 3;
	options.rotate = 0;
	options.sense = 100;
/*	options.showfps = 0;
	options.linescroll = 0;
	options.frontend = 1;
	options.showtitle = 1;
	options.screenposition = 0;
	options.fullcache = 1;
	options.extinput = 0;
	options.xorrom = 1;*/
	options.tweak = 0;
	options.hiscore = 1;

	capex.clock = 66;
	capex.tweak = 0;
	capex.delayspeed = 30;
	capex.repeatspeed = 1;
	capex.list = 0;
	capex.FXshadow = 90;
	capex.skin = 1;

	//lire le fichier de configuration
	if ((fp = fopen("capex.cfg", "r")) != NULL){
		while(fgets(ligne,sizeof(ligne),fp) != NULL){

			sscanf(ligne, "%s %d", &arg1,&argd);

			if (strcmp(arg1,"#")!=0){

				if (strcmp(arg1,"fba2x_clock")==0) options.cpu = argd;
/*				else if (strcmp(arg1,"fba2x_68k_clock")==0) options.cpu68k = argd;
				else if (strcmp(arg1,"fba2x_z80_clock")==0) options.cpuz80 = argd;*/
				else if (strcmp(arg1,"fba2x_sound")==0) options.sound = argd;
				else if (strcmp(arg1,"fba2x_samplerate")==0) options.samplerate = argd;
				else if (strcmp(arg1,"fba2x_rescale")==0) options.rescale = argd;
/*				else if (strcmp(arg1,"fba2x_showfps")==0) options.showfps = argd;
				else if (strcmp(arg1,"fba2x_linescroll")==0) options.linescroll = argd;
				else if (strcmp(arg1,"fba2x_frontend")==0) options.frontend = argd;
				else if (strcmp(arg1,"fba2x_showtitle")==0) options.showtitle = argd;
				else if (strcmp(arg1,"fba2x_screenposition")==0) options.screenposition = argd;
				else if (strcmp(arg1,"fba2x_extinput")==0) options.extinput = argd;
				else if (strcmp(arg1,"fba2x_xorrom")==0) options.xorrom = argd;*/
				else if (strcmp(arg1,"fba2x_tweak")==0) options.tweak = argd;
				else if (strcmp(arg1,"fba2x_hiscore")==0) options.hiscore = argd;
				else if (strcmp(arg1,"capex_deadzone")==0) capex.deadzone = argd;
				else if (strcmp(arg1,"capex_clock")==0) capex.clock = argd;
				else if (strcmp(arg1,"capex_tweak")==0) capex.tweak = argd;
				else if (strcmp(arg1,"z80_core")==0) options.z80core = argd;
				else if (strcmp(arg1,"rotate")==0) options.rotate = argd;
				else if (strcmp(arg1,"filter")==0) options.filter = argd;
				else if (strcmp(arg1,"sensitivity")==0) options.sense = argd;
				else if (strcmp(arg1,"capex_delay_speed")==0) capex.delayspeed = argd;
				else if (strcmp(arg1,"capex_repeat_speed")==0) capex.repeatspeed = argd;
				else if (strcmp(arg1,"capex_list")==0) capex.list = argd;
				else if (strcmp(arg1,"capex_shadow")==0) capex.FXshadow = argd;
				else if (strcmp(arg1,"capex_skin")==0) capex.skin = argd;

			}
		}
		fclose(fp);
	}else{
		write_cfg();
	}

	//check tous les settings et corrige si besoin
	//a faire
}

void load_cf(void)
{
	char arg1[128];
	signed long argd;
	char ligne[256];


	if ( strcmp( data.parent[listing_tri[capex.list][selector.num]] , "fba" ) == 0 ){
		conf.cf = (char*) calloc( strlen(data.zip[listing_tri[capex.list][selector.num]]) + 1 , sizeof(char));
		strcpy( conf.cf , data.zip[listing_tri[capex.list][selector.num]] );
	}else{
		conf.cf = (char*) calloc( strlen(data.parent[listing_tri[capex.list][selector.num]]) + 1 , sizeof(char));
		strcpy( conf.cf , data.parent[listing_tri[capex.list][selector.num]] );
	}


	//lire le fichier de configuration d�di�
	sprintf((char*)g_string, "./conf/%s.cf", conf.cf);

	if ((fp = fopen( g_string , "r")) != NULL){

		//fichier cf present
		conf.exist = 1;

		// force les settings si un parametre est absent
		conf.cpu = options.cpu;
/*		conf.cpu68k = options.cpu68k;
		conf.cpuz80 = options.cpuz80;*/
		conf.sound = options.sound;
		conf.samplerate = options.samplerate;
		conf.rescale = options.rescale;
		conf.rotate = options.rotate;
		conf.sense = options.sense;
		conf.filter = options.filter;
		conf.z80core = options.z80core;
/*		conf.showfps = options.showfps;
		conf.linescroll = options.linescroll;
		conf.showtitle = options.showtitle;
		conf.screenposition = options.screenposition;
		conf.fullcache = options.fullcache;

		conf.extinput = options.extinput;
		conf.xorrom = options.xorrom;*/
		conf.tweak = options.tweak;
		conf.hiscore = options.hiscore;

		while(fgets(ligne,sizeof(ligne),fp) != NULL){

			sscanf(ligne, "%s %d", &arg1,&argd);

			if (strcmp(arg1,"#")!=0){

				if (strcmp(arg1,"fba2x_clock")==0) conf.cpu = argd;
/*				else if (strcmp(arg1,"fba2x_68k_clock")==0) conf.cpu68k = argd;
				else if (strcmp(arg1,"fba2x_z80_clock")==0) conf.cpuz80 = argd;*/
				else if (strcmp(arg1,"fba2x_sound")==0) conf.sound = argd;
				else if (strcmp(arg1,"fba2x_samplerate")==0) conf.samplerate = argd;
				else if (strcmp(arg1,"fba2x_rescale")==0) conf.rescale = argd;
				else if (strcmp(arg1,"fba2x_rotate")==0) conf.rotate = argd;
				else if (strcmp(arg1,"fba2x_sensitivity")==0) conf.sense = argd;
/*				else if (strcmp(arg1,"fba2x_showfps")==0) conf.showfps = argd;
				else if (strcmp(arg1,"fba2x_linescroll")==0) conf.linescroll = argd;
				else if (strcmp(arg1,"fba2x_showtitle")==0) conf.showtitle = argd;
				else if (strcmp(arg1,"fba2x_screenposition")==0) conf.screenposition = argd;
				else if (strcmp(arg1,"fba2x_fullcache")==0) conf.fullcache = argd;
				else if (strcmp(arg1,"fba2x_extinput")==0) conf.extinput = argd;
				else if (strcmp(arg1,"fba2x_xorrom")==0) conf.xorrom = argd;*/
				else if (strcmp(arg1,"fba2x_tweak")==0) conf.tweak = argd;
				else if (strcmp(arg1,"fba2x_hiscore")==0) conf.hiscore = argd;
				else if (strcmp(arg1,"z80_core")==0) conf.z80core = argd;
				else if (strcmp(arg1,"filter")==0) conf.filter = argd;
			}
		}
		fclose(fp);
	}else{
		//initialisation fichier cf absent
		conf.exist = 0;
	}
}


char lecture_zipname(void)
{
	unsigned int caractere;
	unsigned int temp;
	unsigned char flag_v0,flag_v1;

	char ligne[256];
	char *arg;
	data.nb_list[0] = 0;
	data.long_max = 0;
	data.nb_rom = 0;
	char prog[256];
	char buffer[20];
	SDL_Rect progrect;
	progrect.x=130;
	progrect.y=100;
	progrect.w=150;
	progrect.h=10;

	printf("lecture fichier zipname.fba\n");
	if ((fp = fopen("zipname.fba", "r")) != NULL){
		printf("[");
		while(fgets(ligne,sizeof(ligne),fp) != NULL){

			//initialisation de la liste de tri�e
			listing_tri[0][data.nb_list[0]] = data.nb_list[0];

			flag_v0 = flag_v1 = 0;
			temp=strlen(ligne);

			for ( caractere = 0 ; caractere < temp ; ++caractere){
				if (strncmp( &ligne[caractere] ,"," , 1)==0){
				    if (data.zip[data.nb_list[0]])
				    {
				        free(data.zip[data.nb_list[0]]);
				        data.zip[data.nb_list[0]]=NULL;
				    }

					data.zip[data.nb_list[0]] = (char*) calloc( caractere + 1 , sizeof(char));
					data.nb_ziplength[data.nb_list[0]] =caractere + 1;
					strncpy(data.zip[data.nb_list[0]], ligne ,caractere);

					flag_v0 = caractere+1;
					break;
				}
			}

			for ( caractere = flag_v0 ; caractere < temp ; ++caractere){
				if (strncmp( &ligne[caractere] ,"," , 1)==0){
					flag_v1 = caractere;
					break;
				}
			}
			if (data.name[data.nb_list[0]])
            {
                free(data.name[data.nb_list[0]]);
                data.name[data.nb_list[0]]=NULL;
            }
            if (data.status[data.nb_list[0]])
            {
                free(data.status[data.nb_list[0]]);
                data.status[data.nb_list[0]]=NULL;
            }

			if (flag_v1){
					data.name[data.nb_list[0]] = (char*) calloc( (flag_v1-flag_v0) + 1 , sizeof(char));
					data.nb_namelength[data.nb_list[0]] =(flag_v1-flag_v0) + 1;
					strncpy(data.name[data.nb_list[0]], &ligne[flag_v0] , (flag_v1-flag_v0) );

					data.status[data.nb_list[0]] = (char*) calloc( (temp  - flag_v1)  , sizeof(char));
					data.nb_statuslength[data.nb_list[0]] = (temp  - flag_v1);
					strncpy(data.status[data.nb_list[0]], &ligne[flag_v1+1] , (temp  - flag_v1 - 1) );
			}else{
					data.name[data.nb_list[0]] = (char*) calloc( (temp-flag_v0) , sizeof(char));
					data.nb_namelength[data.nb_list[0]] =(temp-flag_v0);
					strncpy(data.name[data.nb_list[0]], &ligne[flag_v0] , (temp-flag_v0)-1 );
			}

			data.longueur[data.nb_list[0]] = strlen(data.name[data.nb_list[0]]);
			if (data.long_max < data.longueur[data.nb_list[0]] ) data.long_max = data.longueur[data.nb_list[0]];

			//verification presence SET
			data.etat[data.nb_list[0]] = ROUGE ; //absent
			sprintf((char*)g_string, "./roms/%s.zip", data.zip[data.nb_list[0]] );
			if ((fp2 = fopen(g_string, "r")) != NULL){
			    fclose(fp2);
				data.etat[data.nb_list[0]] = ORANGE ;
				++data.nb_rom;
			}
			/*sprintf((char*)g_string, "./cache/%s.cache", data.zip[data.nb_list[0]] );
			if ((fp2 = fopen(g_string, "r")) != NULL){
				data.etat[data.nb_list[0]] +=9 ;
				++data.nb_cache;
			}*/
			nitoa((int)data.nb_list[0]+1,buffer,10);
            strcpy(prog,"READING GAME LIST: ");
            strcat(prog,buffer);
            SDL_FillRect(screen,&progrect,0);
			put_string( prog , 130 , 100 ,BLANC, screen );
			SDL_Flip(screen);

			printf("-");

			//increment nombre de set detect�
			++data.nb_list[0];
		}
		fclose(fp);
		printf("]\n");
	}else return 1;
	printf("fin lecture fichier zipname.fba %d\n",data.nb_list[0]);

	return 0;
}

void lecture_rom_jouable(void)
{
	unsigned flag_rom ;
	unsigned int num;
	int test=0;
	int test2=0;

	printf("debut analyse set %d\n",data.nb_list[0]);


	data.nb_cache = 0;

	//verification presence SET
	for ( num=0 ; num<data.nb_list[0] ; ++num ){

		//absent
		//data.etat[num] = ROUGE ;
		flag_rom = 0;

		if ( data.etat[num] == ORANGE ){
		    test2++;
		//test si rom parent
		if ( strcmp( data.parent[num] , "fba" ) == 0 ){
			/*sprintf((char*)g_string, "./roms/%s.zip", data.zip[num] );
			printf("%s",g_string);
			if ((fp = fopen(g_string, "r")) != NULL){
				data.etat[num] +=18 ;
				++data.nb_rom;
				++flag_rom;
				printf("[");
				fclose(fp);
			}
			if ( flag_rom ){*/
				sprintf((char*)g_string, "./cache/%s.cache", data.zip[num] );
				//printf("%s",g_string);
				if ((fp = fopen(g_string, "r")) != NULL){
					data.etat[num] = BLEU ;
					++data.nb_cache;
					//printf("]");
					fclose(fp);
				//}
			} else data.etat[num] = JAUNE ;
		}else{ //sinon pas parent
			/*sprintf((char*)g_string, "./roms/%s.zip", data.zip[num] );
			printf("%s",g_string);
			if ((fp = fopen(g_string, "r")) != NULL){
				data.etat[num] +=9 ;
				++data.nb_rom;
				++flag_rom;
				printf("[");
				fclose(fp);
			}
			if ( flag_rom == 1){*/
				sprintf((char*)g_string, "./roms/%s.zip", data.parent[num] );
				//printf("%s",g_string);

				if ((fp = fopen(g_string, "r")) != NULL){
					data.etat[num] += 9;
					++flag_rom;
					printf("-");
					fclose(fp);
					test++;
				}
			//}
			if ( flag_rom == 1){
				sprintf((char*)g_string, "./cache/%s.cache", data.parent[num] );
				//printf("%s",g_string);
				if ((fp = fopen(g_string, "r")) != NULL){
					data.etat[num] += 9;
					//printf("]");
					fclose(fp);
				}
			}
		}
	}
	}
	printf("fin analyse set %d %d\n",test,test2);
}

char lecture_rominfo(void)
{
	unsigned int caractere;
	unsigned int temp;
	unsigned char flag_v0,flag_v1;

	char ligne[256];
	char arg1[256];
	char arg2[256];
	char arg3[256];

	int found=0;

	for ( ii=0 ; ii<data.nb_list[0] ; ++ii){
				    if (data.parent[ii])
				    {
				        free(data.parent[ii]);
				        data.parent[ii]=NULL;
				    }
	}

	printf("lecture fichier rominfo.fba\n");
	if ((fp = fopen("rominfo.fba", "r")) != NULL){
		printf("[");
		while(fgets(ligne,sizeof(ligne),fp) != NULL){
			sscanf(ligne, "%s %s %s", &arg1 , &arg2 , &arg3 );
			if ( strcmp( arg1 , "FILENAME(" ) == 0 ){
				found=0;
				for ( ii=0 ; ii<data.nb_list[0] ; ++ii){



					if ( data.parent[ii] == NULL )
					if ( strncmp( data.zip[ii] , arg2 , (strlen(arg2)) ) == 0 && (strlen(arg2)) == strlen(data.zip[ii]) ){
						data.parent[ii] = (char*) calloc( strlen(arg3) , sizeof(char));
						data.nb_parentlength[ii] =strlen(arg3);
						strncpy( data.parent[ii] , arg3 , (strlen(arg3)) );
//						printf("(%s->%s)", data.zip[ii], data.parent[ii]);
						found=1;
						break;
					}
				}
				if(found==0) printf("(%s->unknown)",arg2);

			}else printf("-");

		}fclose(fp);
		printf("]\n");

	}
	printf("fin lecture fichier rominfo.fba\n");

	//check parent rom absent
	for ( ii=0 ; ii<data.nb_list[0] ; ++ii)
		if ( data.parent[ii] == NULL ){
			data.parent[ii] = (char*) calloc( 7 +1 , sizeof(char));
			data.nb_parentlength[ii] =7+1;
			strncpy( data.parent[ii] , "unknown" , 7 );
			//strcpy( data.parent[ii] , "fba"  );
		}

	return 0;
}

void load_preview(unsigned int numero)
{
	//preview
	if ( strcmp( data.parent[listing_tri[capex.list][numero]] , "fba" ) == 0 )
		sprintf((char*)g_string, "./preview/%s.bmp" , data.zip[listing_tri[capex.list][numero]]);
	else sprintf((char*)g_string, "./preview/%s.bmp" , data.parent[listing_tri[capex.list][numero]]);

	if ((fp = fopen(g_string, "r")) != NULL){
	    fclose(fp);
		Tmp = SDL_LoadBMP(g_string);
		preview = SDL_DisplayFormat(Tmp);
		SDL_FreeSurface(Tmp);
		flag_preview = 1;
		drawSprite( bg , bg_temp , 204 , 3 , 204 , 3 , 192 , 112 );
		drawSprite(preview, bg_temp, 0, 0, 300-Tmp->w/2, 3, 192, 112 );

	}else{
		drawSprite( bg , bg_temp , 204 , 3 , 204 , 3 , 192 , 112 );

		sprintf((char*)g_string, "PREVIEW %s.bmp" , data.zip[listing_tri[capex.list][numero]]);
		put_string(g_string , 240 , 49 , ROUGE , bg_temp );
		put_string( "NOT AVAILABLE" , 261 , 59 , ROUGE , bg_temp );

		flag_preview = 0;
	}
}
