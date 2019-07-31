@set nombre_rom=OperationBrazilWorldcup
@if not exist "%nombre_rom%.rom" goto Sdcc
@if exist "%nombre_rom%.bak.rom" del %nombre_rom%.bak.rom
@ren %nombre_rom%.rom %nombre_rom%.bak.rom
:Sdcc
@sdcc -mz80 --no-std-crt0 --code-loc 0x4010 --data-loc 0xC000 libs\VDP_TMS9918_MSXBIOS.rel libs\VDP_SPRITE_MSXBIOS.rel %nombre_rom%.c
@if %ERRORLEVEL% neq 0 goto End
@bin\hex2bin -e bin %nombre_rom%.ihx > NUL
@copy /b rom_header.bin + /b %nombre_rom%.bin /b %nombre_rom%.rom > NUL
@bin\fillfile %nombre_rom%.rom 32768
:End
@if exist "%nombre_rom%.asm" @del %nombre_rom%.asm
@if exist "%nombre_rom%.bin" @del %nombre_rom%.bin
@if exist "%nombre_rom%.lk" @del %nombre_rom%.lk
@if exist "%nombre_rom%.lst" @del %nombre_rom%.lst
@if exist "%nombre_rom%.map" @del %nombre_rom%.map
@if exist "%nombre_rom%.noi" @del %nombre_rom%.noi
@if exist "%nombre_rom%.rel" @del %nombre_rom%.rel
@if exist "%nombre_rom%.sym" @del %nombre_rom%.sym
@if exist "%nombre_rom%.ihx" @del %nombre_rom%.ihx
:endend