@echo off
echo "ESTA ES LA VERSION 1.10"
set Z88DK_PATH=c:\z88dk10
set PATH=%Z88DK_PATH%\bin;%PATH%
set Z80_OZFILES=%Z88DK_PATH%\Lib\
set ZCCCFG=%Z88DK_PATH%\Lib\Config\
rem Cambia "%1" por el nombre de tu güego.
echo ### COMPILANDO SCRIPT ###
cd ..\script
rem no olvides cambiar el 24 por el nº de pantallas
msc lubitjam.spt msc.h 24
copy *.h ..\dev
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### REGENERANDO MAPA ###
cd ..\map
rem cambia ANCHO y ALTO por los valores de tu mapa:
..\utils\mapcnv mapa.map 8 3 15 10 15 packed
copy mapa.h ..\dev
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### COMPILANDO GUEGO ###
zcc +zx -vn lubitjam.c -o lubitjam.bin -lndos -lsplib2 -zorg=24200
echo -------------------------------------------------------------------------------
echo ### CONSTRUYENDO CINTA ###
rem cambia LOADER por el nombre que quieres que salga en Program:
..\utils\bas2tap -a10 -sLOADER loader.bas loader.tap
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 lubitjam.bin
copy /b loader.tap + screen.tap + main.tap lubitjam.tap
echo -------------------------------------------------------------------------------
echo ### LIMPIANDO ###
del loader.tap
del screen.tap
del main.tap
del lubitjam.bin
echo -------------------------------------------------------------------------------
echo ### DONE ###
pause
