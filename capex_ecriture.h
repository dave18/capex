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

void write_cfg()
{
	printf("ecriture capex.cfg debut\n");
	fp = fopen("capex.cfg", "w");

	fputs("# CAPEX config file v1.1\n",fp);
	fputs("\n",fp);

	fputs("# FBA2X OPTIONS\n",fp);
	fputs("\n",fp);
	sprintf((char*)g_string, "fba2x_clock %d\n",options.cpu);
	fputs(g_string,fp);
/*	sprintf((char*)g_string, "fba2x_68k_clock %d\n",options.cpu68k);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_z80_clock %d\n",options.cpuz80);
	fputs(g_string,fp);*/
	sprintf((char*)g_string, "fba2x_sound %d\n",options.sound);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_samplerate %d\n",options.samplerate);
	fputs(g_string,fp);
/*	sprintf((char*)g_string, "fba2x_rescale %d\n",options.rescale);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_showfps %d\n",options.showfps);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_linescroll %d\n",options.linescroll);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_frontend %d\n",options.frontend);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_showtitle %d\n",options.showtitle);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_screenposition %d\n",options.screenposition);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_fullcache %d\n",options.fullcache);
	fputs(g_string,fp);

	sprintf((char*)g_string, "fba2x_extinput %d\n",options.extinput);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_xorrom %d\n",options.xorrom);
	fputs(g_string,fp);*/
	sprintf((char*)g_string, "fba2x_tweak %d\n",options.tweak);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_hiscore %d\n",options.hiscore);
	fputs(g_string,fp);
	sprintf((char*)g_string, "z80_core %d\n",options.z80core);
	fputs(g_string,fp);
	sprintf((char*)g_string, "rotate %d\n",options.rotate);
	fputs(g_string,fp);

	sprintf((char*)g_string, "filter %d\n",options.filter);
	fputs(g_string,fp);

	sprintf((char*)g_string, "fba2x_rescale %d\n",options.rescale);
	fputs(g_string,fp);

	sprintf((char*)g_string, "sensitivity %d\n",options.sense);
	fputs(g_string,fp);

	fputs("\n",fp);

	fputs("# CAPEX OPTIONS\n",fp);
	fputs("\n",fp);
	sprintf((char*)g_string, "capex_deadzone %d\n",capex.deadzone);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_clock %d\n",capex.clock);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_tweak %d\n",capex.tweak);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_delay_speed %d\n",capex.delayspeed);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_repeat_speed %d\n",capex.repeatspeed);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_list %d\n",capex.list);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_shadow %d\n",capex.FXshadow);
	fputs(g_string,fp);
	sprintf((char*)g_string, "capex_skin %d\n",capex.skin);
	fputs(g_string,fp);

	fclose(fp);
	sync();
	printf("ecriture capex.cfg fin\n");
}

void write_cf()
{
	sprintf((char*)g_string, "conf/%s.cf", conf.cf);
	printf("ecriture %s debut\n", g_string);

	fp = fopen(g_string, "w");

	fputs("# Config V2 file generate by CAPEX\n",fp);
	sprintf((char*)g_string, "# %s\n", conf.cf );
	fputs(g_string,fp);
	fputs("\n",fp);
	sprintf((char*)g_string, "fba2x_clock %d\n",options.cpu);
	fputs(g_string,fp);
/*	sprintf((char*)g_string, "fba2x_68k_clock %d\n",options.cpu68k);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_z80_clock %d\n",options.cpuz80);
	fputs(g_string,fp);*/
	sprintf((char*)g_string, "fba2x_sound %d\n",options.sound);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_samplerate %d\n",options.samplerate);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_rescale %d\n",options.rescale);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_rotate %d\n",options.rotate);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_sensitivity %d\n",options.sense);
	fputs(g_string,fp);
/*	sprintf((char*)g_string, "fba2x_showfps %d\n",options.showfps);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_linescroll %d\n",options.linescroll);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_showtitle %d\n",options.showtitle);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_screenposition %d\n",options.screenposition);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_fullcache %d\n",options.fullcache);

	sprintf((char*)g_string, "fba2x_extinput %d\n",options.extinput);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_xorrom %d\n",options.xorrom);
	fputs(g_string,fp);*/
	sprintf((char*)g_string, "fba2x_tweak %d\n",options.tweak);
	fputs(g_string,fp);
	sprintf((char*)g_string, "fba2x_hiscore %d\n",options.hiscore);
	fputs(g_string,fp);

	sprintf((char*)g_string, "z80_core %d\n",options.z80core);
	fputs(g_string,fp);

    sprintf((char*)g_string, "rotate %d\n",options.rotate);
	fputs(g_string,fp);

	sprintf((char*)g_string, "filter %d\n",options.filter);
	fputs(g_string,fp);
/*
	sprintf((char*)g_string, "spare_1 %d\n",options.spare1);
	fputs(g_string,fp);
	sprintf((char*)g_string, "spare_2 %d\n",options.spare2);
	fputs(g_string,fp);
	sprintf((char*)g_string, "spare_3 %d\n",options.spare3);
	fputs(g_string,fp);
	sprintf((char*)g_string, "spare_4 %d\n",options.spare4);
	fputs(g_string,fp);
	sprintf((char*)g_string, "spare_5 %d\n",options.spare5);
	fputs(g_string,fp);*/

	fclose(fp);
	sync();

	sprintf((char*)g_string, "conf/%s.cf", conf.cf);
	printf("ecriture %s fin\n", g_string);
}
