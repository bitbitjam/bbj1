###############################################################
###                   SAVE THE HUMOR                        ###
###---------------------------------------------------------###
### A 1-week fast game made exclusively for #bitbitjam 2014 ###
###---------------------------------------------------------###
###		    by FREMOS SOLDIERS                      ###
###             (c) FREMOS / CHEESETEA 2014                 ###
###############################################################

## HOW TO COMPILE
##################

This game uses a modification of the CPCITOR framework to build a .DSK 
for Amstrad CPCfile from sources. For building it you need to do the
following steps

* Under Windows:
------------------------------
*1 Install Cygwin on your system if you do not have it already installed
** Note: for this, a 32bits version of cygwin has been used

*2 Unpack the ZIP file just below your $HOME directory 
*** This will create a $HOME/$GAME folder

*3 Ensure that you have these files UNDER the $HOME/$GAME/tool folder (1)
*** HEX2BIN 1.0.10: 
**** hex2bin/Hex2bin-1.0.10/hex2bin.exe
*** IDSK      0.13: 
**** idsk/iDSK.0.13/iDSK/src
*** SDCC     3.4.0: 
**** sdcc/sdcc-3.4.0.installtree/bin/sdasz80.exe
**** sdcc/sdcc-3.4.0.installtree/bin/sdcc.exe
**** sdcc/sdcc-3.4.0.installtree/bin/sdcpp.exe
**** sdcc/sdcc-3.4.0.installtree/bin/sdldz80.exe
**** sdcc/sdcc-3.4.0.installtree/share/sdcc/lib/z80/z80.lib

*4 Enter into $HOME/$GAME through your cygwin console

*5 Typein "make"

(1) These files may not have been distributed to you along with the ZIP file: 
    they are external tools whose rights belong solely to their authors.
    You may download them by downloading HEX2BIN, IDSK and SDCC packs from
    the Internet. You may need to compile some of them from sources. If you
    want to get them fast, you may want to have a look to CPCITOR framework,
    which would get all of them for you

## THE AUTHORS
###############

ronaldo/Fremos/Cheesetea (ronaldo@cheesetea.com, @FranGallegoBR)
Pote/Cheesetea 		 (potevif@gmail.com)

http://fremos.cheesetea.com
http://cheesetea.com

