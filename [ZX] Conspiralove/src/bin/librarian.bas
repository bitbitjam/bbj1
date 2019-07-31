' Librarian.bas
' Copyleft 2012 The Mojon Twins

Dim as Integer f1, f2, fl
Dim mempointer as Integer
Dim currentMem as Integer
Dim ramPage as Integer
Dim ramPages (3) as Integer
Dim myBin (16384) as uByte
Dim currentBin (16384) as uByte
Dim linea as String
Dim d as uByte
Dim i as Integer
Dim thisOffset as Integer
Dim resId as Integer
Dim comma as String

ramPages (0) = 3
ramPages (1) = 4
ramPages (2) = 6
ramPages (3) = 7

ramPage = 0
mempointer = 0
resId = 0

Print "THE LIBRARIAN"
Print
Print "Processing list.txt"

f1 = FreeFile
Open "list.txt" For Input as f1
fl = FreeFile
Open "librarian.h" For Output as fl

Print #fl, "// librarian.h"
Print #fl, "// Generated by The Librarian"
Print #fl, "// Copyleft 2012 The Mojon Twins"
Print #fl, " "
Print #fl, "typedef struct {"
Print #fl, "   unsigned char ramPage;"
Print #fl, "   unsigned int ramOffset;"
Print #fl, "} RESOURCE;"
Print #fl, " "
Print #fl, "RESOURCE resources [] = {"

While Not Eof (f1)
	Line Input #f1, linea
	linea = Trim (linea)
	
	f2 = FreeFile
	currentMem = 0
	Open linea For Binary as #f2
	While Not Eof (f2)
		Get #f2, , d
		currentBin (currentMem) = d
		currentMem = currentMem + 1
	Wend
	Close f2
	
	' Append or adding a new one?
	If currentMem + mempointer > 16384 Then
		' new
		' First write binary
		f2 = FreeFile
		Print "Writing RAM" & Trim (Str (ramPages (ramPage))) & ".bin"
		Open "RAM" & Trim (Str (ramPages (ramPage))) & ".bin" For Binary as #f2
		For i = 0 To mempointer - 1
			Put #f2, , myBin (i)
		Next i
		Close f2
		' Move to new RAM page
		ramPage = ramPage + 1
		mempointer = 0
	End If

	Print " + File " & linea
	
	thisOffset = mempointer
	
	' add
	For i = 0 To currentMem - 1
		myBin (mempointer) = currentBin (i)
		mempointer = mempointer + 1
	Next i
	
	' Write resource to librarian .h
	if eof(f1) then comma = " " else comma = ","
	
	Print #fl, "   {" & Trim (Str (ramPages (ramPage))) & ", " & Trim (Str (49152 + thisOffset)) & "}" & comma & "   // " & Trim (Str (resId)) & ": " & linea
	resId = resId + 1
Wend

' Final
If mempointer <> 0 Then
	f2 = FreeFile
	Print "Writing RAM" & Trim (Str (ramPages (ramPage))) & ".bin"
	Open "RAM" & Trim (Str (ramPages (ramPage))) & ".bin" For Binary as #f2
	For i = 0 To mempointer - 1
		Put #f2, , myBin (i)
	Next i
	Close f2	
End If

Print #fl, "};"
Print #fl, " "

Print #fl, "void get_resource (unsigned char res, unsigned int dest) {"
Print #fl, "   unpack_RAMn (resources [res].ramPage, resources [res].ramOffset, dest);"
Print #fl, "}"
Print #fl, " "

Close f1, fl 
