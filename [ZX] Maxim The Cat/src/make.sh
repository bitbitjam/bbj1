#!/bin/bash

GAMENAME=gatete

rm ../$GAMENAME.tap &> /dev/null
rm -rf build &> /dev/null
mkdir -p build

echo "-----------------------------------"
echo "### REGENERANDO MAPA y SPRITES ###"
posterizezx gfx/sprites.png build/sprites.png
posterizezx gfx/tiles.png build/tiles.png

posterizezx gfx/loading.png build/loading.png
png2rcs build/loading.png build/loading.rcs
zx7b build/loading.rcs build/loading.rcs.zx7b

posterizezx gfx/ending.png build/ending.png
png2rcs build/ending.png build/ending.rcs
zx7b build/ending.rcs build/ending.rcs.zx7b

posterizezx gfx/menu.png build/menu.png
png2rcs build/menu.png build/menu.rcs
zx7b build/menu.rcs build/menu.rcs.zx7b

#  util/gentmx 3 3 10 10 map.tmx
tmxcompress gfx/mapa.tmx build/map_compressed.bin > defmap.asm
step1 # genera sprites, tiles, bullet, ...

echo " "
echo "--------------------------"
echo "### REGENERANDO ENGINE ###"
cd build
sjasmplus --nologo ../mus/WYZproPlay47aZX.asm
playsiz=$(wc -c "player.bin"  | cut -f 1 -d ' ')
echo "        DEFINE  player $playsiz" >> ../define.asm

sjasmplus --nologo ../engine0.asm
sjasmplus --nologo ../engine1.asm
sjasmplus --nologo ../engine2.asm
cd ..
step2
zx7b build/block.bin build/block.zx7b

echo " "
echo "########################"
echo "### COMPILANDO GUEGO ###"
cd build
zcc +zx -O3 -vn ../main.c -o main.bin -lndos
zx7b main.bin main.zx7b
cat map_compressed.bin main.zx7b block.zx7b > engine.zx7b
cp ../defload.asm ndefload.asm

en7size=$(wc -c "engine.zx7b" | cut -f 1 -d ' ')
ma7size=$(wc -c "main.zx7b"   | cut -f 1 -d ' ')
mansize=$(wc -c "main.bin"    | cut -f 1 -d ' ')
echo "        DEFINE  engicm  $en7size " >> ndefload.asm
echo "        DEFINE  maincm  $ma7size " >> ndefload.asm
echo "        DEFINE  mainrw  $mansize " >> ndefload.asm
echo "        DEFINE  player  $playsiz " >> ndefload.asm


sjasmplus --nologo ../loader.asm
gentape ../../$GAMENAME.tap           \
    basic "'GAME'" 0  loader.bin  \
     data           engine.zx7b   \
     data           player.bin

