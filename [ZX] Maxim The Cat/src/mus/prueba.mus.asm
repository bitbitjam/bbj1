
; Tabla de instrumentos
TABLA_PAUTAS: DW 0,PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5,PAUTA_6,PAUTA_7,PAUTA_8

; Tabla de efectos
TABLA_SONIDOS: DW SONIDO0,SONIDO1,SONIDO2,SONIDO3,SONIDO4,SONIDO5,SONIDO6

;Pautas (instrumentos)
;Instrumento 'Piano -1'
PAUTA_1:	DB	46,0,13,0,12,0,11,0,10,0,9,0,8,0,129
;Instrumento 'Inc vol piano -1'
PAUTA_2:	DB	40,0,8,0,8,0,8,0,9,0,9,0,9,0,9,0,9,0,10,0,10,0,10,0,10,0,10,0,11,0,11,0,11,0,11,0,11,0,12,0,12,0,12,0,12,0,12,0,13,0,13,0,13,0,13,0,13,0,14,0,14,0,129
;Instrumento 'Eco 1 piano -1'
PAUTA_3:	DB	45,0,12,0,11,0,10,0,9,0,0,129
;Instrumento 'Eco 2 piano -1'
PAUTA_4:	DB	42,0,9,0,9,0,8,0,8,0,0,129
;Instrumento 'Eco 3 piano -1'
PAUTA_5:	DB	41,0,8,0,8,0,7,0,6,0,0,129
;Instrumento 'Techno +1'
PAUTA_6:	DB	70,0,5,0,4,0,4,0,5,0,5,0,4,0,4,0,129
;Instrumento 'Trompeta'
PAUTA_7:	DB	12,0,13,0,13,0,14,0,14,0,13,0,12,0,11,0,10,0,9,0,8,0,129
;Instrumento 'Piano'
PAUTA_8:	DB	14,0,13,0,12,0,11,0,10,0,9,0,8,0,129

;Efectos
;Efecto 'bass drum'
SONIDO0:	DB	139,63,0,162,108,0,255
;Efecto 'drum'
SONIDO1:	DB	232,46,0,0,91,12,255
;Efecto 'hithat'
SONIDO2:	DB	0,13,1,255
;Efecto 'bass drum vol 2'
SONIDO3:	DB	186,57,0,0,102,0,162,131,0,255
;Efecto 'Hit hat 2'
SONIDO4:	DB	0,9,5,255
;Efecto 'Bongo 1'
SONIDO5:	DB	186,31,0,232,30,0,0,45,0,69,44,0,255
;Efecto 'Bongo 2'
SONIDO6:	DB	69,47,0,186,46,0,46,61,0,232,60,0,255

;Frecuencias para las notas
DATOS_NOTAS:
          DW 0,0
          DW 1711,1614,1524,1438,1358,1281,1210,1142,1078,1017
          DW 960,906,855,807,762,719,679,641,605,571
          DW 539,509,480,453,428,404,381,360,339,320
          DW 302,285,269,254,240,227,214,202,190,180
          DW 170,160,151,143,135,127,120,113,107,101
          DW 95,90,85,80,76,71,67,64,60,57
