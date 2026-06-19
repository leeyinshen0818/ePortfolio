TITLE lab1
; Author: Group
; Date: 10 April

include Irvine32.inc

.data
val1 dword 10000h
val2 dword 40000h
val3 dword 20000h
finalVal dword ?

.code

main proc
	mov eax, val1
	add eax, val2
	sub eax, val3
	mov finalVal, eax
	call DumpRegs
exit

main ENDP
END main