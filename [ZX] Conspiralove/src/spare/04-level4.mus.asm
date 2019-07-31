
; Tabla de instrumentos
TABLA_PAUTAS: DW 0,PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5,PAUTA_6,PAUTA_7,PAUTA_8

; Tabla de efectos
TABLA_SONIDOS: DW SONIDO0,SONIDO1,SONIDO2,SONIDO3

;Pautas (instrumentos)
;Instrumento 'Wave'
PAUTA_1:	DB	9,0,76,0,11,0,9,0,8,4,8,4,8,0,8,0,8,-4,8,-4,8,0,8,0,136
;Instrumento 'Orn 0-3-7'
PAUTA_2:	DB	8,0,8,0,24,3,24,3,24,7,24,7,134
;Instrumento 'Orn 0-4-7'
PAUTA_3:	DB	8,0,8,0,24,4,24,4,24,7,24,7,134
;Instrumento 'Orn 0-4-8'
PAUTA_4:	DB	8,0,8,0,24,4,24,4,24,8,24,8,134
;Instrumento 'Bass'
PAUTA_5:	DB	45,0,44,0,10,0,8,0,7,0,129
;Instrumento 'Clip'
PAUTA_6:	DB	72,0,72,0,40,0,8,2,8,2,7,0,7,0,8,-2,8,-2,7,0,7,0,136
;Instrumento 'AlarmUp'
PAUTA_7:	DB	8,0,8,0,8,0,8,0,8,-1,129
;Instrumento 'AlarmDown'
PAUTA_8:	DB	8,0,8,0,8,0,8,0,8,1,129

;Efectos
;Efecto 'bass drum'
SONIDO0:	DB	209,63,0,69,173,0,255
;Efecto 'drum'
SONIDO1:	DB	23,62,0,93,92,6,0,9,3,255
;Efecto 'hithat'
SONIDO2:	DB	0,11,1,0,6,1,255
;Efecto 'bass drum vol 2'
SONIDO3:	DB	186,58,0,0,102,0,162,131,0,255

;Frecuencias para las notas
DATOS_NOTAS: DW 0,0
DW 1711,1614,1524,1438,1358,1281,1210,1142,1078,1017
DW 960,906,855,807,762,719,679,641,605,571
DW 539,509,480,453,428,404,381,360,339,320
DW 302,285,269,254,240,227,214,202,190,180
DW 170,160,151,143,135,127,120,113,107,101
DW 95,90,85,80,76,71,67,64,60,57
