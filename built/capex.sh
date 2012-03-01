#!/bin/sh

#sudo -n /usr/pandora/scripts/op_lcdrate.sh 50
mkdir -p ./preview
mkdir -p ./conf
mkdir -p ./roms
mkdir -p ./config
mkdir -p ./neocdiso
mkdir -p ./savestates
mkdir -p ./screenshots
mkdir -p ./support

export SDL_VIDEODRIVER=omapdss
export SDL_OMAP_LAYER_SIZE=800x480
export SDL_OMAP_VSYNC=1
LD_PRELOAD=./libSDL-1.2.so.0.11.3 ./capex

#sudo -n /usr/pandora/scripts/op_lcdrate.sh 60
