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

nub0="$(cat /proc/pandora/nub0/mode)"
nub1="$(cat /proc/pandora/nub1/mode)"
echo absolute > /proc/pandora/nub0/mode
echo absolute > /proc/pandora/nub1/mode

sleep 1

export SDL_VIDEODRIVER=omapdss
export SDL_OMAP_LAYER_SIZE=800x480
export SDL_OMAP_VSYNC=1
LD_PRELOAD=./libSDL-1.2.so.0 ./capex

#sudo -n /usr/pandora/scripts/op_lcdrate.sh 60

echo $nub0 > /proc/pandora/nub0/mode
echo $nub1 > /proc/pandora/nub1/mode
