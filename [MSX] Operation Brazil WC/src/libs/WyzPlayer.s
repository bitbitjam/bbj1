; ******************************************************
; **       Librer�a de rutinas para Amstrad CPC       **
; **	   Ra�l Simarro, 	  Artaburu 2010           **
; **	   PLAYER programado por  WYZ		          **
; **       Adaptada a MSX by B4rret :P 2014           **
; **       B4: Es la �nica adaptaci�n para SDCC       **
;**            que he encontrado del Wyzplayer        **
;**            Ojeando los foros de Karoshi y alg�n   **
;**            otro sitio, parece que ya hay          **
;**            adaptaciones para MSX, pero no las     **
;**            encuentro... :/                        **
;**            De todos modos creo q con              **
;**            4 cambios (bueno, 4 m�s, 4 menos :P)   **
;**            pueda funcionar en MSX ^_^             **
;**            ... Bueno, eso espero ^v^U             **
; ******************************************************

;XLIB msx_WyzPlayer
;XDEF CARGA_CANCION_WYZ
;XDEF INICIA_EFECTO_WYZ
;XDEF msx_WyzSetPlayerOn0
;XDEF msx_WyzSetPlayerOff0
;XDEF TABLA_SONG
;XDEF TABLA_EFECTOS
;XDEF TABLA_PAUTAS
;;XDEF TABLA_SONIDOS
;XDEF INTERRUPCION
;XDEF BUFFER_MUSICA
;XDEF direcc_tempo
;DEFINE BUFFER_DEC  = #0x100
; CPC PSG proPLAYER - WYZ 2010
;XREF INTERRUPCION

.globl _msx_WyzConfigurePlayer
_msx_WyzConfigurePlayer::
	LD HL,#2
    ADD HL,SP
    LD a,(HL)
	LD (#INTERR),A
	RET

.globl _msx_WyzInitPlayer
_msx_WyzInitPlayer::
; la entrada indica las tablas de canciones, pautas, efectos,... s�lo hay que inicializar esos datos
; en la librer�a
	LD IX,#2
	ADD IX,SP
	LD L,6 (IX)
	LD H,7 (IX)
	LD (#TABLA_SONG0),HL
	LD L,4 (IX)
	LD H,5 (IX)
	LD (#TABLA_EFECTOS0),HL
	LD L,2 (IX)
	LD H,3 (IX)
	LD (#TABLA_PAUTAS0),HL
	LD L,0 (IX)
	LD H,1 (IX)
	LD (#TABLA_SONIDOS0),HL
	RET

.globl _msx_WyzLoadSong
_msx_WyzLoadSong::
	LD HL,#2
	ADD HL,SP
	LD A,(HL)
	JP CARGA_CANCION_WYZ0

.globl _msx_WyzSetTempo
_msx_WyzSetTempo::
	LD HL,#2
	ADD HL,SP
	LD A,(HL)
	ld (#dir_tempo+1),a
	ret

.globl _msx_WyzStartEffect
_msx_WyzStartEffect::
	LD HL,#2
	ADD HL,SP
	LD c,(HL)
	INC HL
	LD b,(HL)
	;AHORA TIENE 2 par�metros: C:canal, B:numero efecto
	JP INICIA_EFECTO_WYZ0

;.globl _msx_WyzStartSound
;_msx_WyzStartSound::
;	LD HL,#2
;	ADD HL,SP
;	LD A,(HL)
;	JP INICIA_SONIDO_WYZ

.globl _msx_WyzTestPlayer
_msx_WyzTestPlayer::
	LD HL,#INTERR
	LD A,(HL)
	LD L,A
	LD H,#0
	RET

_msx_WyzPlayer::
.globl	_msx_WyzSetPlayerOn
_msx_WyzSetPlayerOn::
	;El player funcionar� por interrupciones.
	di
	ld	de, #datos_int
	ld	hl, #0xFD9A
	ld	bc, #5
	ldir

	ld	hl, #INICIO
    ld	(#0xFD9A+1), HL
	ld	a, #0xC3
	ld	(#0xFD9A), a
	ei	; brotheeeeeeeeeeeeeeeer
	ret

.globl _msx_WyzSetPlayerOff
_msx_WyzSetPlayerOff::
	;apago todos los sonidos poniendo los registros a 0
	call PLAYER_OFF
	;Restaura salto original
	di
	ld	de, #0xFD9A
	ld	hl, #datos_int	
	ld	bc, #5
	ldir

	ld a,(#datos_int)	;guardo el salto original
	ld (#0x0038),A
	ld a,(#datos_int+1)	;guardo el salto original
	ld (#0x0039),A
	ld a,(#datos_int+2)	;guardo el salto original
	ld (#0x003a),A

	ei	; sisteeeeeeeeeeeeeeeeer
	ret
;___________________________________________________________
;   .db     "PSG PROPLAYER BY WYZ'10"
;___________________________________________________________

INICIO:
		;primero mira si toca tocar :P
		push af
		LD A,(#contador)
		DEC A
		LD (#contador),A
		;cp #0
		or a
		JP NZ,termina_int
dir_tempo:
		LD A,#6
		LD (#contador),A

		PUSH BC
		PUSH HL
		PUSH DE
		PUSH IX
		PUSH IY

		CALL	ROUT
		LD		HL,#PSG_REG
		LD		DE,#PSG_REG_SEC
		LD		BC,#14
		LDIR
		
		; B4: Uhhhm, esto cambia con respecto al Wyzplayer original... Misa no saber... :/
		CALL	PLAY
		CALL	REPRODUCE_SONIDO

		LD		HL,#PSG_REG_SEC
		LD		DE,#PSG_REG_EF
		LD		BC,#14
		LDIR

		;De este modo, prevalece el efecto
		CALL	REPRODUCE_EFECTO_A
		CALL	REPRODUCE_EFECTO_B
		CALL	REPRODUCE_EFECTO_C
		CALL    ROUT_EF

		POP IY
		POP IX
		POP DE
		POP HL
		POP BC

termina_int:
		pop af
		ei

contador: 
		.db #0
datos_int: 
		.db #0,#0,#0,#0,#0		; Se guardan 3 BYTES!!!! (Dedicado a Na_th_an, por los desvelos) (B4: En MSX guardamos 5 ;D )

;INICIA EL SONIDO N� (A)

INICIA_EFECTO_WYZ0:

;INICIA EL SONIDO N� (B) EN EL CANAL (C)
		LD	A,C
		CP	#0
		JP	Z,INICIA_EFECTO_A
		CP	#1
		JP	Z,INICIA_EFECTO_B
		CP	#2
		JP	Z,INICIA_EFECTO_C
		;JP INICIA_EFECTO_A
		RET


;REPRODUCE EFECTOS

;REPRODUCE EFECTOS CANAL A

REPRODUCE_EFECTO_A:
		LD      HL,#INTERR
		BIT     3,(HL)          ;ESTA ACTIVADO EL EFECTO?
		RET     Z
		LD      HL,(#PUNTERO_EFECTO_A)
		LD      A,(HL)
		CP      #0xFF
		JR      Z,FIN_EFECTO_A
		CALL 	BLOQUE_COMUN
		LD      (#PUNTERO_EFECTO_A),HL
		LD      0 (IX),B
		LD      1 (IX),C
		LD      8 (IX),A
		RET
FIN_EFECTO_A:
		LD      HL,#INTERR
		RES     3,(HL)
		XOR     A
		LD      (#PSG_REG_EF+0),A
		LD      (#PSG_REG_EF+1),A
		LD		(#PSG_REG_EF+8),A
		RET

REPRODUCE_EFECTO_B:
		LD      HL,#INTERR
		BIT     5,(HL)          ;ESTA ACTIVADO EL EFECTO?
		RET     Z
		LD      HL,(#PUNTERO_EFECTO_B)
		LD      A,(HL)
		CP      #0xFF
		JR      Z,FIN_EFECTO_B
		CALL 	BLOQUE_COMUN
		LD      (#PUNTERO_EFECTO_B),HL
		LD      2 (IX),B
		LD      3 (IX),C
		LD      9 (IX),A
		RET
FIN_EFECTO_B:
		LD      HL,#INTERR
		RES     5,(HL)
		XOR     A
		LD      (#PSG_REG_EF+2),A
		LD      (#PSG_REG_EF+3),A
		LD		(#PSG_REG_EF+9),A
		RET

REPRODUCE_EFECTO_C:
		LD      HL,#INTERR
		BIT     6,(HL)          ;ESTA ACTIVADO EL EFECTO?
		RET     Z
		LD      HL,(#PUNTERO_EFECTO_C)
		LD      A,(HL)
		CP      #0xFF
		JR      Z,FIN_EFECTO_C
		CALL 	BLOQUE_COMUN
		LD      (#PUNTERO_EFECTO_C),HL
		LD      4 (IX),B
		LD      5 (IX),C
		LD      10 (IX),A
		RET
FIN_EFECTO_C:
		LD      HL,#INTERR
		RES     6,(HL)
		XOR     A
		LD      (#PSG_REG_EF+4),A
		LD      (#PSG_REG_EF+5),A
		LD		(#PSG_REG_EF+10),A
		RET

BLOQUE_COMUN:
		LD IX,#PSG_REG_EF
		LD B,A
		INC     HL
		LD      A,(HL)
		RRCA
		RRCA
		RRCA
		RRCA
		AND     #0b00001111
		LD C,A
		LD      A,(HL)
		AND     #0b00001111
		INC     HL
		RET

INICIA_EFECTO_A:
		LD		A,B
		LD      HL,(#TABLA_EFECTOS0)
		CALL    EXT_WORD
		LD      (#PUNTERO_EFECTO_A),HL
		LD      HL,#INTERR
		SET     3,(HL)
		RET

INICIA_EFECTO_B:
		LD		A,B
		LD      HL,(#TABLA_EFECTOS0)
		CALL    EXT_WORD
		LD      (#PUNTERO_EFECTO_B),HL
		LD      HL,#INTERR
		SET     5,(HL)
		RET

INICIA_EFECTO_C:
		LD		A,B
		LD      HL,(#TABLA_EFECTOS0)
		CALL    EXT_WORD
		LD      (#PUNTERO_EFECTO_C),HL
		LD      HL,#INTERR
		SET     6,(HL)
		RET



INICIA_SONIDO:
		LD       HL,(#TABLA_SONIDOS0)
		CALL    EXT_WORD
		LD      (#PUNTERO_SONIDO),HL
		LD      HL,#INTERR
		SET     2,(HL)
		RET
;PLAYER OFF

PLAYER_OFF:
		LD	HL,#INTERR
		RES	1,(HL)

		XOR	A
		LD	HL,#PSG_REG
		LD	DE,#PSG_REG+1
		LD	BC,#14
		LD	(HL),A
		LDIR

		LD	HL,#PSG_REG_SEC
		LD	DE,#PSG_REG_SEC+1
		LD	BC,#14
		LD	(HL),A
		LDIR

		CALL	ROUT
		CALL	FIN_SONIDO
		RET




CARGA_CANCION_WYZ0:
        DI
        push af
		CALL	PLAYER_OFF
		pop af
; MUSICA DATOS INICIALES




				LD		DE,#0x0010					;  N� BYTES RESERVADOS POR CANAL
                LD      HL,#BUFFER_DEC       	;* RESERVAR MEMORIA PARA BUFFER DE SONIDO!!!!!
                LD      (#CANAL_A),HL

                ADD     HL,DE
                LD      (#CANAL_B),HL

                ADD     HL,DE
                LD      (#CANAL_C),HL

                ADD     HL,DE
                LD      (#CANAL_P),HL

                ;LD      A,#0             	;* CANCION N� 0
                CALL    CARGA_CANCION

               	LD A,#6
 				LD (#contador),A

;PANTALLA
		EI
		ret



;CARGA UNA CANCION
;IN:(A)=N� DE CANCION

CARGA_CANCION:
				LD      HL,#INTERR       ;CARGA CANCION

                SET     1,(HL)          ;REPRODUCE CANCION
                LD      HL,#SONG
                LD      (HL),A          ;N� A



;DECODIFICAR
;IN-> INTERR 0 ON
;     SONG

;CARGA CANCION SI/NO

DECODE_SONG:
			    LD      A,(#SONG)

;LEE CABECERA DE LA CANCION
;BYTE 0=TEMPO

                ;LD      HL,TABLA_SONG
                LD      HL,(#TABLA_SONG0)
                CALL    EXT_WORD
                LD      A,(HL)
                LD      (#TEMPO),A
		XOR	A
		LD	(#TTEMPO),A

;HEADER BYTE 1
;(-|-|-|-|-|-|-|LOOP)

                INC	HL		;LOOP 1=ON/0=OFF?
                LD	A,(HL)
                BIT	0,A
                JR	Z,NPTJP0
                PUSH	HL
                LD	HL,#INTERR
                SET	4,(HL)
                POP	HL


NPTJP0:
		        INC	HL		;2 BYTES RESERVADOS
                INC	HL
                INC	HL

;BUSCA Y GUARDA INICIO DE LOS CANALES EN EL MODULO MUS


		LD	(#PUNTERO_P_DECA),HL
		LD	E,#0x3F			;CODIGO INTRUMENTO 0
		LD	B,#0xFF			;EL MODULO DEBE TENER UNA LONGITUD MENOR DE #0xFF00 ... o_O!
BGICMODBC1:
		XOR	A			;BUSCA EL BYTE 0
		CPIR
		DEC	HL
		DEC	HL
		LD	A,E			;ES EL INSTRUMENTO 0??
		CP	(HL)
		INC	HL
		INC	HL
		JR	Z,BGICMODBC1

		LD	(#PUNTERO_P_DECB),HL

BGICMODBC2:
		XOR	A			;BUSCA EL BYTE 0
		CPIR
		DEC	HL
		DEC	HL
		LD	A,E
		CP	(HL)			;ES EL INSTRUMENTO 0??
		INC	HL
		INC	HL
		JR	Z,BGICMODBC2

		LD	(#PUNTERO_P_DECC),HL

BGICMODBC3:
		XOR	A			;BUSCA EL BYTE 0
		CPIR
		DEC	HL
		DEC	HL
		LD	A,E
		CP	(HL)			;ES EL INSTRUMENTO 0??
		INC	HL
		INC	HL
		JR	Z,BGICMODBC3
		LD	(#PUNTERO_P_DECP),HL


;LEE DATOS DE LAS NOTAS
;(|)(|||||) LONGITUD\NOTA

INIT_DECODER:
			    LD      DE,(#CANAL_A)
                LD      (#PUNTERO_A),DE
                LD	HL,(#PUNTERO_P_DECA)
                CALL    DECODE_CANAL    ;CANAL A
                LD	(#PUNTERO_DECA),HL

                LD      DE,(#CANAL_B)
                LD      (#PUNTERO_B),DE
                LD	HL,(#PUNTERO_P_DECB)
                CALL    DECODE_CANAL    ;CANAL B
                LD	(#PUNTERO_DECB),HL

                LD      DE,(#CANAL_C)
                LD      (#PUNTERO_C),DE
                LD	HL,(#PUNTERO_P_DECC)
                CALL    DECODE_CANAL    ;CANAL C
                LD	(#PUNTERO_DECC),HL

                LD      DE,(#CANAL_P)
                LD      (#PUNTERO_P),DE
                LD	HL,(#PUNTERO_P_DECP)
                CALL    DECODE_CANAL    ;CANAL P
                LD	(#PUNTERO_DECP),HL

                RET


;DECODIFICA NOTAS DE UN CANAL
;IN (DE)=DIRECCION DESTINO
;NOTA=0 FIN CANAL
;NOTA=1 SILENCIO
;NOTA=2 PUNTILLO
;NOTA=3 COMANDO I

DECODE_CANAL:
			    LD      A,(HL)
                AND     A               ;FIN DEL CANAL?
                JR      Z,FIN_DEC_CANAL
                CALL    GETLEN

                CP      #0b00000001       ;ES SILENCIO?
                JR      NZ,NO_SILENCIO
                SET     6,A
                JR      NO_MODIFICA

NO_SILENCIO:
			    CP      #0b00111110        ;ES PUNTILLO?
                JR      NZ,NO_PUNTILLO
                OR      A
                RRC     B
                XOR     A
                JR      NO_MODIFICA

NO_PUNTILLO:
			    CP      #0b00111111        ;ES COMANDO?
                JR      NZ,NO_MODIFICA
                BIT     0,B             ;COMADO=INSTRUMENTO?
                JR      Z,NO_INSTRUMENTO
                LD      A,#0b11000001      ;CODIGO DE INSTRUMENTO
                LD      (DE),A
                INC     HL
                INC     DE
                LD      A,(HL)          ;N� DE INSTRUMENTO
                LD      (DE),A
                INC     DE
                INC	HL
                JR      DECODE_CANAL

NO_INSTRUMENTO:
				BIT     2,B
                JR      Z,NO_ENVOLVENTE
                LD      A,#0b11000100      ;CODIGO ENVOLVENTE
                LD      (DE),A
                INC     DE
                INC	HL
                JR      DECODE_CANAL

NO_ENVOLVENTE:
				BIT     1,B
                JR      Z,NO_MODIFICA
                LD      A,#0b11000010      ;CODIGO EFECTO
                LD      (DE),A
                INC     HL
                INC     DE
                LD      A,(HL)
                CALL    GETLEN

NO_MODIFICA:
			    LD      (DE),A
                INC     DE
                XOR     A
                DJNZ    NO_MODIFICA
		SET     7,A
		SET 	0,A
                LD      (DE),A
                INC     DE
                INC	HL
                RET			;** JR      DECODE_CANAL

FIN_DEC_CANAL:
				SET     7,A
                LD      (DE),A
                INC     DE
                RET

GETLEN:
		         LD      B,A
                AND     #0b00111111
                PUSH    AF
                LD      A,B
                AND     #0b11000000
                RLCA
                RLCA
                INC     A
                LD      B,A
                LD      A,#0b10000000
DCBC0:
	          RLCA
                DJNZ    DCBC0
                LD      B,A
                POP     AF
                RET






;PLAY __________________________________________________


PLAY:
	          	LD      HL,#INTERR       ;PLAY BIT 1 ON?
                BIT     1,(HL)
                RET     Z
;TEMPO
                LD      HL,#TTEMPO       ;CONTADOR TEMPO
                INC     (HL)
                LD      A,(#TEMPO)
                CP      (HL)
                JR      NZ,PAUTAS
                LD      (HL),#0

;INTERPRETA
                LD      IY,#PSG_REG
                LD      IX,#PUNTERO_A
                LD      BC,#PSG_REG+8
                CALL    LOCALIZA_NOTA
                LD      IY,#PSG_REG+2
                LD      IX,#PUNTERO_B
                LD      BC,#PSG_REG+9
                CALL    LOCALIZA_NOTA
                LD      IY,#PSG_REG+4
                LD      IX,#PUNTERO_C
                LD      BC,#PSG_REG+10
                CALL    LOCALIZA_NOTA
                LD      IX,#PUNTERO_P    ;EL CANAL DE EFECTOS ENMASCARA OTRO CANAL
                CALL    LOCALIZA_EFECTO

;PAUTAS

PAUTAS:
		        LD      IY,#PSG_REG+0
                LD      IX,#PUNTERO_P_A
                LD      HL,#PSG_REG+8
                CALL    PAUTA           ;PAUTA CANAL A
                LD      IY,#PSG_REG+2
                LD      IX,#PUNTERO_P_B
                LD      HL,#PSG_REG+9
                CALL    PAUTA           ;PAUTA CANAL B
                LD      IY,#PSG_REG+4
                LD      IX,#PUNTERO_P_C
                LD      HL,#PSG_REG+10
                CALL    PAUTA           ;PAUTA CANAL C

                RET



;REPRODUCE EFECTOS DE SONIDO

REPRODUCE_SONIDO:

				LD      HL,#INTERR
                BIT     2,(HL)          ;ESTA ACTIVADO EL EFECTO?
                RET     Z
                LD      HL,(#PUNTERO_SONIDO)
                LD      A,(HL)
                CP      #0xFF
                JR      Z,FIN_SONIDO
                LD      (#PSG_REG_SEC+4),A
                INC     HL
                LD      A,(HL)
                RRCA
                RRCA
                RRCA
                RRCA
                AND     #0b00001111
                LD      (#PSG_REG_SEC+5),A
                LD      A,(HL)
                AND     #0b00001111
                LD      (#PSG_REG_SEC+10),A
                INC     HL
                LD      A,(HL)
                AND     A
                JR      Z,NO_RUIDO
                LD      (#PSG_REG_SEC+6),A
                LD      A,#0b10011000
                JR      SI_RUIDO
NO_RUIDO:
		        LD      A,#0b10111000
SI_RUIDO:
		        LD      (#PSG_REG_SEC+7),A

                INC     HL
                LD      (#PUNTERO_SONIDO),HL
                RET
FIN_SONIDO:
			    LD      HL,#INTERR
                RES     2,(HL)

FIN_NOPLAYER:
				LD      A,#0b10111000 		;2 BITS ALTOS PARA MSX / AFECTA AL CPC???
       			LD      (#PSG_REG+7),A
                RET

;VUELCA BUFFER DE SONIDO AL PSG

ROUT:
		xor		a
		ld		c, #0xA0
		ld		hl, #PSG_REG_SEC
LOUT:
		out		(c), a
		inc		c
		outi
		dec		c
		inc		a
		cp		#13
		jr		nz, LOUT
		out		(c), a
		ld		a, (hl)
		and		a
		ret		z
		inc		c
		out		(c), a
		xor		a
		ld		(#PSG_REG_SEC+13), a
		LD		(#PSG_REG+13), a
		ret

ROUT_EF:
		xor		a
		ld		c, #0xA0
		ld		hl, #PSG_REG_SEC
LOUT_EF:
		out		(c), a
		inc		c
		outi
		dec		c
		inc		a
		cp		#13
		jr		nz, LOUT_EF
		out		(c), a
		ld		a, (hl)
		and		a
		ret		z
		inc		c
		out		(c), a
		xor		a
		ld		(#PSG_REG_EF+13), a
		ret

;LOCALIZA NOTA CANAL A
;IN (PUNTERO_A)

LOCALIZA_NOTA:
		LD      L,0 (IX)       		;HL=(PUNTERO_A_C_B)
		LD      H,1 (IX)
		LD      A,(HL)
		AND     #0b11000000       		;COMANDO?
		CP      #0b11000000
		JR      NZ,LNJP0

;BIT(0)=INSTRUMENTO

COMANDOS:
		LD      A,(HL)
		BIT     0,A             	;INSTRUMENTO
		JR      Z,COM_EFECTO

		INC     HL
		LD      A,(HL)          	;N� DE PAUTA
		INC     HL
		LD      0 (IX),L
		LD      1 (IX),H
		;LD      HL,(#TABLA_PAUTAS) ; B4: �? Otro cambio al original :?
		LD      HL,(#TABLA_PAUTAS0)
		CALL    EXT_WORD
		LD      18 (IX),L
		LD      19 (IX),H
		LD      12 (IX),L
		LD      13 (IX),H
		LD      L,C
		LD      H,B
		RES     4,(HL)        		;APAGA EFECTO ENVOLVENTE
		XOR     A
		LD      (#PSG_REG_SEC+13),A
		LD	(#PSG_REG+13),A
		JR      LOCALIZA_NOTA

COM_EFECTO:
		BIT     1,A             	;EFECTO DE SONIDO
		JR      Z,COM_ENVOLVENTE

		INC     HL
		LD      A,(HL)
		INC     HL
		LD      0 (IX),L
		LD      1 (IX),H
		CALL    INICIA_SONIDO
		RET

COM_ENVOLVENTE:
		BIT     2,A
		RET     Z               	;IGNORA - ERROR
; B4: Faltaban estas lineas del WyzPlayer original...
;     las vuelvo a poner, que me dan buen rollito ^_^U
		INC     HL
		LD	A, (HL)			;CARGA CODIGO DE ENVOLVENTE
		LD	(ENVOLVENTE), A
; B4: F�n lineas faltantes
		INC     HL
		LD      0 (IX),L
		LD      1 (IX),H
		LD      L,C
		LD      H,B
		LD	(HL),#0b00010000           ;ENCIENDE EFECTO ENVOLVENTE
		JR      LOCALIZA_NOTA

LNJP0:
		LD      A,(HL)
		INC     HL
		BIT     7,A
		JR      Z,NO_FIN_CANAL_A
		BIT	0,A
		JR	Z,FIN_CANAL_A

FIN_NOTA_A:
		LD  E,6 (IX)
		LD	D,7 (IX)	;PUNTERO BUFFER AL INICIO
		LD	0 (IX),E
		LD	1 (IX),D
		LD	L,30 (IX)	;CARGA PUNTERO DECODER
		LD	H,31 (IX)
		PUSH	BC

		CALL    DECODE_CANAL    ;DECODIFICA CANAL
		POP	BC
		LD	30 (IX),L	;GUARDA PUNTERO DECODER
		LD	31 (IX),H
		JP	LOCALIZA_NOTA

FIN_CANAL_A:
		LD	HL,#INTERR	;LOOP?
		BIT	4,(HL)
		JR      NZ,FCA_CONT
		CALL	PLAYER_OFF
		RET

FCA_CONT:
		LD	L,24 (IX)	;CARGA PUNTERO INICIAL DECODER
		LD	H,25 (IX)
		LD	30 (IX),L
		LD	31 (IX),H
		JR      FIN_NOTA_A

NO_FIN_CANAL_A:
		LD      0 (IX),L        ;(PUNTERO_A_B_C)=HL GUARDA PUNTERO
		LD      1 (IX),H
		AND     A               ;NO REPRODUCE NOTA SI NOTA=0
		JR      Z,FIN_RUTINA
		BIT     6,A             ;SILENCIO?
		JR      Z,NO_SILENCIO_A
		LD	A,(BC)
		AND	#0b00010000
		JR	NZ,SILENCIO_ENVOLVENTE
		XOR     A
		LD	(BC),A		;RESET VOLUMEN
		LD	0 (IY),A
		LD	1 (IY),A
		RET

SILENCIO_ENVOLVENTE:
		LD	A,#0xFF
		LD	(#PSG_REG+11),A
		LD	(#PSG_REG+12),A
		XOR	A
		LD	(#PSG_REG+13),A
		LD	0 (IY),A
		LD	1 (IY),A
		RET

NO_SILENCIO_A:

; B4: Otra instrucci�n que falta :/
		;LD	(IX+REG_NOTA_A-PUNTERO_A),A	;REGISTRO DE LA NOTA DEL CANAL
		LD	36 (IX), A
; B4: F�n instruccion que faltaba :/
		CALL    NOTA            ;REPRODUCE NOTA
		LD      L,18 (IX)       ;HL=(PUNTERO_P_A0) RESETEA PAUTA
		LD      H,19 (IX)
		LD      12 (IX),L       ;(PUNTERO_P_A)=HL
		LD      13 (IX),H
FIN_RUTINA:
		RET

;LOCALIZA EFECTO
;IN HL=(PUNTERO_P)

LOCALIZA_EFECTO:
		LD      L,0 (IX)       ;HL=(PUNTERO_P)
		LD      H,1 (IX)
		LD      A,(HL)
		CP      #0b11000010
		JR      NZ,LEJP0

		INC     HL
		LD      A,(HL)
		INC     HL
		LD      0 (IX),L
		LD      1 (IX),H
		CALL    INICIA_SONIDO
		RET


LEJP0:
		INC     HL
		BIT     7,A
		JR      Z, NO_FIN_CANAL_P
		BIT	0,A
		JR	Z,FIN_CANAL_P
FIN_NOTA_P:
		LD      DE,(#CANAL_P)
		LD	0 (IX),E
		LD	1 (IX),D
		LD	HL,(#PUNTERO_DECP)	;CARGA PUNTERO DECODER
		PUSH	BC
		CALL    DECODE_CANAL    	;DECODIFICA CANAL
		POP	BC
		LD	(#PUNTERO_DECP),HL	;GUARDA PUNTERO DECODER
		JP      LOCALIZA_EFECTO

FIN_CANAL_P:
		LD	HL,(#PUNTERO_P_DECP)	;CARGA PUNTERO INICIAL DECODER
		LD	(#PUNTERO_DECP),HL
		JR      FIN_NOTA_P

NO_FIN_CANAL_P:
		LD      0 (IX),L        ;(PUNTERO_A_B_C)=HL GUARDA PUNTERO
		LD      1 (IX),H
		RET

; PAUTA DE LOS 3 CANALES
; IN:(IX):PUNTERO DE LA PAUTA
;    (HL):REGISTRO DE VOLUMEN
;    (IY):REGISTROS DE FRECUENCIA

; FORMATO PAUTA
;	    7    6     5     4   3-0                     3-0
; BYTE 1 (LOOP|OCT-1|OCT+1|SLIDE|VOL) - BYTE 2 ( | | | |PITCH)

PAUTA:
		BIT     4,(HL)        ;SI LA ENVOLVENTE ESTA ACTIVADA NO ACTUA PAUTA
		RET     NZ

		LD	A,0 (IY)
		LD	B,1 (IY)
		OR	B
		RET	Z

		PUSH	HL

PCAJP4:
		LD      L,0 (IX)
		LD      H,1 (IX)
		LD	A,(HL)

		BIT     7,A		;LOOP / EL RESTO DE BITS NO AFECTAN
		JR      Z,PCAJP0
		AND     #0b00011111        ;LOOP PAUTA (0,32)X2!!!-> PARA ORNAMENTOS
		RLCA			;X2
		LD      D,#0
		LD      E,A
		SBC     HL,DE
		LD      A,(HL)

PCAJP0:
		BIT	6,A		;OCTAVA -1
		JR	Z,PCAJP1
		LD	E,0 (IY)
		LD	D,1 (IY)

		AND	A
		RRC	D
		RR	E
		LD	0 (IY),E
		LD	1 (IY),D
		JR	PCAJP2

PCAJP1:
		BIT	5,A		;OCTAVA +1
		JR	Z,PCAJP2
		LD	E,0 (IY)
		LD	D,1 (IY)

		AND	A
		RLC	E
		RL	D
		LD	0 (IY),E
		LD	1 (IY),D


PCAJP2:
; B4: �Eins? No est� el c�digo de ornamentos... :S
;	  Pos yo lo meto (pq yo lo valgo! ^_^)
		ld	a, (HL)
		bit	4, a
		jr	nz, PCAJP6	;ORNAMENTOS SELECCIONADOS
; B4: F�n ornamentos

		INC     HL		;______________________ FUNCION PITCH DE FRECUENCIA__________________		
		PUSH	HL
		LD	E,A
		LD	A,(HL)		;PITCH DE FRECUENCIA
		LD	L,A
		AND	A
		LD	A,E
		JR	Z,ORNMJP1

		LD	A,0 (IY)	;SI LA FRECUENCIA ES 0 NO HAY PITCH
		ADD	A,1 (IY)
		AND	A
		LD	A,E
		JR	Z,ORNMJP1

		BIT	7,L
		JR	Z,ORNNEG
		LD	H,#0xFF
		JR	PCAJP3
ORNNEG:
		LD	H,#0

PCAJP3:
		LD	E,0 (IY)
		LD	D,1 (IY)
		ADC	HL,DE
		LD	0 (IY),L
		LD	1 (IY),H
; B4: Faltaba:
		jr	ORNMJP1
PCAJP6:		
		inc	hl			;______________________ FUNCION ORNAMENTOS__________________
		push	hl
		push	af
		ld	a, 24 (IX)	;RECUPERA REGISTRO DE NOTA EN EL CANAL
		ld	e, (HL)
		adc	e			;+- NOTA
		call	TABLA_NOTAS
		pop	af
; B4: F�n de lo que faltaba
ORNMJP1:
		POP	HL

		INC	HL
		LD      0 (IX),L
		LD      1 (IX),H
PCAJP5:
		POP	HL
		AND	#0b00001111 	;VOLUMEN FINAL
		LD      (HL),A
		RET

;NOTA : REPRODUCE UNA NOTA
;IN (A)=CODIGO DE LA NOTA
;   (IY)=REGISTROS DE FRECUENCIA

NOTA:
		;ADD	6		;*************************
		ld      l, c
		ld      h, b
		bit     4, (hl)
		ld      b, a
		jr	    nz, EVOLVENTES
		ld	    a, b
TABLA_NOTAS:
		LD      hl, #DATOS_NOTAS
; B4: M�s c�digo cambiado. Aqu� creo que ha metido directamente
;     el c�digo de EXT_WORD. Prefiero dejarlo como estaba
		;RLCA                    ;X2
		;LD      D,#0
		;LD      E,A
		;ADD     HL,DE
		;LD      A,(HL)
		;LD      0 (IY),A
		;INC     HL
		;LD      A,(HL)
		;LD      1 (IY),A
		call    EXT_WORD
		ld      0 (iy), l
		ld      1 (iy), h
; B4: F�n cambios
		ret

;IN (A)=CODIGO DE LA ENVOLVENTE
;   (IY)=REGISTRO DE FRECUENCIA

EVOLVENTES:
; B4: Aqu� tambi�n cambian muchas cosas... 
;     Prefiero dejar el c�digo original...
		ld		hl, #DATOS_NOTAS	;BUSCA FRECUENCIA
		call	EXT_WORD
				
		ld		a, (#ENVOLVENTE)	;FRECUENCIA DEL CANAL ON/OFF
LOCALIZA_ENV:
		rra
		jr		nc, FRECUENCIA_OFF
		ld		0 (IY), l
		ld		1 (IY), h
		jr		CONT_ENV
				
FRECUENCIA_OFF:
		ld		hl, #0x0000
		ld      0 (IY), l
		ld		1 (IY), h
									;CALCULO DEL RATIO (OCTAVA ARRIBA)
CONT_ENV:
		push	af
		push	BC
		and		#0b00000011
		ld		b, a
		inc		b
		xor		a
OCTBC01:
		add		a, #12				;INCREMENTA OCTAVAS
		djnz	OCTBC01
		pop		bc					;RECUPERA CODIGO DE LA NOTA
		add		b					;EN REGISTRO A CODIGO NOTA
		
		ld		hl, #DATOS_NOTAS	;BUSCA FRECUENCIA
		call	EXT_WORD
				
ENV_PSG_EXT:	
		ld		a, l
		ld		(#PSG_REG+11), a
		ld		a, h
		and		#0xb00000011
		ld      (#PSG_REG+12), a
		pop		af					;SELECCION FORMA DE ENVOLVENTE

		rra
		and		#0xb00000110		;$08,$0A,$0C,$0E
		add		#8                
		ld		(#PSG_REG+13), a
		ld		(#PSG_REG_SEC+13), a
		ret

; B4: C�digo como estaba en la funci�n de CPC
	;PUSH	AF
	;CALL	ENV_RUT1
	;LD	DE,#0x0000
	;LD      0 (IY),E
	;LD     1 (IY),D

	;POP	AF
	;ADD	A,#48
	;CALL	ENV_RUT1


	;LD	A,E
	;LD      (#PSG_REG+11),A
	;LD	A,D
	;LD      (#PSG_REG+12),A
	;LD      A,#0x0E
	;LD      (#PSG_REG+13),A
	;RET

;IN(A) NOTA
;ENV_RUT1:
	;LD      HL,#DATOS_NOTAS
	;RLCA                    ;X2
	;LD      D,#0
	;LD      E,A
	;ADD     HL,DE
	;LD	E,(HL)
	;INC	HL
	;LD	D,(HL)
	;RET
; B4: F�n cambios

EXT_WORD:
		ld		d, #0
; B4: Otro cambio
		;SLA     A               ;*2
		rlca
; B4: F�n cambio
		ld		e, a
		add		hl, de
		ld		e, (hl)
		inc		hl
		ld		d, (hl)
		ex		de, hl
		ret

;BANCO DE INSTRUMENTOS 2 BYTES POR INT.

;(0)(RET 2 OFFSET)
;(1)(+-PITCH)

;BANCO DE INSTRUMENTOS 2 BYTES POR INT.

;(0)(RET 2 OFFSET)
;(1)(+-PITCH)

;.TABLA_PAUTAS .dw 	PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5,PAUTA_6,PAUTA_7;,PAUTA_8,PAUTA_9,PAUTA_10,PAUTA_11,PAUTA_12,PAUTA_13,PAUTA_14,PAUTA_15,PAUTA_16,PAUTA_17,PAUTA_18

;DATOS DE LOS EFECTOS DE SONIDO

;EFECTOS DE SONIDO

;TABLA_SONIDOS	.dw    SONIDO1,SONIDO2,SONIDO3,SONIDO4,SONIDO5;,SONIDO6,SONIDO7;,SONIDO8
TABLA_PAUTAS0:	.dw 0
TABLA_SONIDOS0:	.dw 0

;DATOS MUSICA

;TABLA_SONG:     .dw    SONG_0;,SONG_1,SONG_2;,SONG_3          ;******** TABLA DE DIRECCIONES DE ARCHIVOS MUS

DATOS_NOTAS:
	    .dw #0x0000,#0x0000
		; B4 Esta tabla me la ha generado el WyzTracker
		.dw #1699, #1603, #1514, #1428, #1349, #1272, #1202, #1134, #1071, #1010
		.dw #954, #900, #849, #802, #757, #714, #674, #637, #601, #567
		.dw #535, #506, #477, #450, #425, #401, #378, #358, #337, #318
		.dw #300, #283, #267, #252, #238, #225, #213, #201, #189, #179
		.dw #169, #159, #150, #142, #134, #126, #119, #112, #106, #100
		.dw #94, #89, #84, #79, #75, #71, #67, #64, #60, #57

;		.dw	#0x41D,#0x3E2,#0x3AA,#0x376,#0x344,#0x315,#0x2E9,#0x2BF,#0x297,#0x272,#0x24F,#0x22E,#0x20E,#0x1F1,#0x1D5,#0x1BB
;		.dw	#0x1A2,#0x18A,#0x174,#0x15F,#0x14B,#0x139,#0x127,#0x117,#0x107,#0xF8,#0xEA,#0xDD
;		.dw	#0xD1,#0xC5,#0xBA,#0xAF,#0xA5,#0x9C,#0x93,#0x8B,#0x83,#0x7C,#0x75,#0x6E
;		.dw	#0x68,#0x62,#0x5D,#0x57,#0x52,#0x4E,#0x49,#0x45,#0x41,#0x3E,#0x3A,#0x37
;		.dw	#0x34,#0x31,#0x2E,#0x2B,#0x29,#0x27,#0x24,#0x22,#0x20,#0x1F,#0x1D,#0x1B
;		.dw	#0x1A,#0x18,#0x17,#0x15,#0x14,#0x13,#0x12,#0x11,#0x10,#0xF,#0xE,#0xD

; B4: Estas ven�an en la funci�n de la librer�a para cpc
;.DW #1711,#1614,#1524,#1438,#1358,#1281,#1210,#1142,#1078,#1017
;.DW #960,#906,#855,#807,#762,#719,#679,#641,#605,#571
;.DW #539,#509,#480,#453,#428,#404,#381,#360,#339,#320
;.DW #302,#285,#269,#254,#240,#227,#214,#202,#190,#180
;.DW #170,#160,#151,#143,#135,#127,#120,#113,#107,#101
;.DW #95,#90,#85,#80,#76,#71,#67,#64,#60,#57




SONG_0:
		;INCBIN	"WYAZOW.MUS"



; VARIABLES__________________________


INTERR:			.db	#00				;INTERRUPTORES 1=ON 0=OFF
									;BIT 0=CARGA CANCION ON/OFF
									;BIT 1=PLAYER ON/OFF
									;BIT 2=SONIDOS ON/OFF
									;BIT 3=EFECTOS ON/OFF

;MUSICA **** EL ORDEN DE LAS VARIABLES ES FIJO ******

TABLA_SONG0:	.dw #0
TABLA_EFECTOS0: .dw #0

.db      'P','S','G',' ','P','R','O','P','L','A','Y','E','R',' ','B','Y',' ','W','Y','Z','-','1','0'

SONG:			.db	#00				;DB N� DE CANCION
TEMPO:			.db	#00				;DB TEMPO
TTEMPO:			.db	#00				;DB CONTADOR TEMPO

PUNTERO_A:		.dw	#00				;DW	PUNTERO	DEL	CANAL A
PUNTERO_B:		.dw	#00				;DW PUNTERO DEL CANAL B
PUNTERO_C:		.dw	#00				;DW	PUNTERO	DEL	CANAL C

BUFFER_MUSICA:
CANAL_A:		.dw	#BUFFER_DEC		;DW	DIRECION DE	INICIO DE LA MUSICA	A
CANAL_B:		.dw	#00				;DW	DIRECION DE	INICIO DE LA MUSICA	B
CANAL_C:		.dw	#00				;DW	DIRECION DE	INICIO DE LA MUSICA	C

PUNTERO_P_A:	.dw	#00				;DW	PUNTERO	PAUTA CANAL	A
PUNTERO_P_B:	.dw	#00				;DW	PUNTERO	PAUTA CANAL	B
PUNTERO_P_C:	.dw	#00				;DW	PUNTERO	PAUTA CANAL	C

PUNTERO_P_A0:	.dw	#00				;DW	INI	PUNTERO	PAUTA CANAL	A
PUNTERO_P_B0:	.dw	#00				;DW	INI	PUNTERO	PAUTA CANAL	B
PUNTERO_P_C0:	.dw	#00				;DW	INI	PUNTERO	PAUTA CANAL	C

PUNTERO_P_DECA:	.dw	#00				;DW	PUNTERO	DE INICIO DEL DECODER CANAL	A
PUNTERO_P_DECB:	.dw	#00				;DW	PUNTERO	DE INICIO DEL DECODER CANAL	B
PUNTERO_P_DECC:	.dw	#00				;DW	PUNTERO	DE INICIO DEL DECODER CANAL	C

PUNTERO_DECA:	.dw	#00				;DW	PUNTERO	DECODER	CANAL A
PUNTERO_DECB:	.dw	#00				;DW	PUNTERO	DECODER	CANAL B
PUNTERO_DECC:	.dw	#00				;DW	PUNTERO	DECODER	CANAL C

; B4: Faltaban estas 3 :/ :
REG_NOTA_A:		.db #00				;DB REGISTRO DE LA NOTA EN EL CANAL A
									;VACIO
REG_NOTA_B:		.db #00				;DB REGISTRO DE LA NOTA EN EL CANAL B
									;VACIO
REG_NOTA_C:		.db #00				;DB REGISTRO DE LA NOTA EN EL CANAL C
									;VACIO
; B4: Espero que no me jodan los NN(IX) :/

;CANAL DE EFECTOS - ENMASCARA OTRO CANAL

PUNTERO_P:		.dw	#00			;DW PUNTERO DEL CANAL EFECTOS
CANAL_P:		.dw	#00			;DW DIRECION DE INICIO DE LOS EFECTOS
PUNTERO_P_DECP:	.dw	#00			;DW PUNTERO DE INICIO DEL DECODER CANAL P
PUNTERO_DECP:	.dw	#00			;DW PUNTERO DECODER CANAL P

; B4: No estoy seguro de donde sale el valor del medio... En el player
;     original no lo veo... :/
PSG_REG:		.db	#00, #00, #00, #00, #00, #00, #00, #0b10111000, #00, #00, #00, #00, #00, #00, #00    ;.db(11) BUFFER DE REGISTROS DEL PSG
PSG_REG_SEC:	.db	#00, #00, #00, #00, #00, #00, #00, #0b10111000, #00, #00, #00, #00, #00, #00, #00    ;.db(11) BUFFER SECUNDARIO DE REGISTROS DEL PSG
; B4: Este es nuevo :/
PSG_REG_EF:		.db	#00, #00, #00, #00, #00, #00, #00, #0b10111000, #00, #00, #00, #00, #00, #00, #00    ;.db(11) BUFFER DE REGISTROS DEL PSG
; B4: Y este faltaba :/
ENVOLVENTE:		.db #00			;DB : FORMA DE LA ENVOLVENTE
								;BIT 0	  : FRECUENCIA CANAL ON/OFF
								;BIT 1-2  : RATIO
								;BIT 3-3  : FORMA

; B4: Y estos comentados no se de donde han salido :/
;ENVOLVENTE_A    EQU	#0xD033	;DB
;ENVOLVENTE_B    EQU	#0xD034	;DB
;ENVOLVENTE_C    EQU	#0xD035	;DB

;EFECTOS DE SONIDO

N_SONIDO:		.db	#00			;DB  NUMERO DE SONIDO
PUNTERO_SONIDO: .dw	#00			;DW  PUNTERO DEL SONIDO QUE SE REPRODUCE

;EFECTOS
N_EFECTO:		.db	#00			;DB  NUMERO DE SONIDO

; B4: Otro que tampoco s� de donde sale... :/
;PUNTERO_EFECTO	.dw	0			;DW  PUNTERO DEL SONIDO QUE SE REPRODUCE

; B4: y estos tambi�n son nuevos :/
PUNTERO_EFECTO_A:	.dw	#00		;DW : PUNTERO DEL SONIDO QUE SE REPRODUCE
PUNTERO_EFECTO_B:	.dw	#00		;DW : PUNTERO DEL SONIDO QUE SE REPRODUCE
PUNTERO_EFECTO_C:	.dw	#00		;DW : PUNTERO DEL SONIDO QUE SE REPRODUCE


BUFFER_DEC:			; defs #0x40
					.dw	#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0		; 16 bytes
					.dw	#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0		; 32 bytes
					.dw	#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0		; 48 bytes
					.dw	#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0,#0		; 64 bytes

;					.db	#0x00	;************************* mucha atencion!!!!
;.BUFFER_DEC defs 2048			; space dinamically asigned in source code compilation!!
								; aqui se decodifica la cancion hay que dejar suficiente espacio libre.
								;*************************

;DEFC CARGA_CANCION_WYZ = CARGA_CANCION_WYZ0
;DEFC INICIA_EFECTO_WYZ = INICIA_EFECTO_WYZ0
;DEFC msx_WyzSetPlayerOn0 = msx_WyzSetPlayerOn1
;DEFC msx_WyzSetPlayerOff0 = msx_WyzSetPlayerOff1
;DEFC TABLA_SONG = TABLA_SONG0
;DEFC TABLA_EFECTOS = TABLA_EFECTOS0
;DEFC TABLA_PAUTAS = TABLA_PAUTAS0
;DEFC TABLA_SONIDOS = TABLA_SONIDOS0
;DEFC INTERRUPCION = INTERR
;DEFC direcc_tempo = dir_tempo
