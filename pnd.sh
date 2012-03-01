#!/bin/sh
cd built
/usr/pandora/scripts/pnd_make.sh -d . -c -p fba.pnd -x capex.pxml -i fba.png
cp ./fba.pnd /media/MAINSYSTEM/pandora/apps
rm fba.pnd
cd ..