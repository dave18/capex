CAPEX frontend by JYCET
for CPS2EMU emulator by Ell

UP/DOWN/LEFT/RIGHT = scroll in the list
A = Launch a rom (all except RED)
X = help screen
SELECT = options window
START (double) = quit

ROMS COLOR:
RED = missing
ORANGE = clone rom detected
YELLOW = parent rom detected or clone rom detected & parent rom detected
GREEN = clone rom detected & parent rom detected & cache detected
BLUE = parent rom detected & cache detected

Extract all in your CPS2EMU folder and launch CAPEX.GPE !
CAPEX.GPE need:
-file zipname.cps2
-file rominfo.cps2
-folder ./preview/ (empty if you want)
-folder ./conf/
Optional
-file capex.png (icon)
-file info.txt (this file)
-folder and files ./skin/... (but better :) )

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

v0.6:
-capex.gpe compressed with rlyeh's gpecomp v0.4 
-add (little) help press X
-add credit info at exit
-add skin by pedator
-add icon by pedator
-add integrated ram tweak option (normal, high, aggressive)
-add message when preview xxx.bmp is not available
-fix a control bug in the windows swap
-fix a very small error in *.cf file generating (supress a X to CAPEXX :))
and finally now under GPL :)

v0.5 (no public release):
-chg default capex speed from 80MHz to 66MHz
-add background shadow option
-add loop scrolling list for games and options
-add external skin option
-fix some gfx superposition error
-fix TV-OUT rendering and resolution
-fix freeze browsing when game are in zipnames.cps2 but not in rominfo.cps2
-del internal background for (futur) GPL edition
-cleaning sources

v0.4:
-chg backgroung and reorganize display
-add external background support (if you dont like it, put a capex.bmp file)
-fix hide/show title option in *cf file.
-add --extinput, --no-extinput option support
-add --xorrom, --no-xorrom option support
-add --tweak, --no-tweak option support
-add --cpuspeed [clock] option support
-add --hiscore, --no-hiscore option support

Beta 3:
-add 3 last missing preview (choco & hsf2a & rckmanj)
-add launching menu
-add dedicated config file by parent rom (*.cf in ./conf/)
-add --hwho-rescale option support
-add --linescroll option support
-add --frontend= option support
-add --showtitle option support
-add --screen-position= option support (only for no rescaled mode)
-add --fullcache option support
-chg launching rom (add ORANGE & YELLOW for unmerged roms)
...(lot of small things here and here ... but forgot)

Beta 2:
-chg SDL lib.
-fix some surface initialisation pb
-chg capex speed from 100MHz to 80MHz
-add rom analysis from rominfo.cps2
-add save options (capex.cfg)
-add missing roms filter
-add available roms filter
-add playable roms filter
-add 3 capex options (clock, delay, repeat)
-add Parent rom info (useful for clone)
-add more font color for analysis
-del external picture for no preview
-chg internal background picture
-add all preview (exept choco & hsf2a & rckmanj)

Beta 1 (intial release):
-game list import from zipname.cps2
-screenshot support
-full command line option support
-capex speed 100MHz
