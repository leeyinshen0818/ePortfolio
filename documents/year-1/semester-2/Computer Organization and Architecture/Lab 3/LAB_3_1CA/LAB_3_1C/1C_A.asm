TITLE Lab 3 Part 1C

; Authors: LEE YIN SHEN / BRENDAN CHIA YAN FEI
; Date: 21 JUNE 2024
; LAB 2 Part 1CB

INCLUDE Irvine32.inc

.data
message BYTE "Calculate Perimeter 2-Hexagon (LOOP and ADD instructions): ", 0
prompt1 BYTE "Input hexagon 1 (side length) : ", 0
prompt2 BYTE "Input hexagon 2 (side length) : ", 0
result1 BYTE "Result of Perimeter Hexagon 1 and 2: ", 0
totalPerimeterMsg BYTE "Total Perimeter Hexagon 1 and 2: ", 0
sideHex1 DWORD ?
sideHex2 DWORD ?
Perimeter_hexagon1 DWORD ?
Perimeter_hexagon2 DWORD ?
TotalPerimeter DWORD ?

.code
main PROC
; Display initial message
mov edx, OFFSET message
call WriteString
call Crlf
call Crlf

; Get side length for hexagon 1
mov edx, OFFSET prompt1
call WriteString
call ReadDec
mov sideHex1, eax

; Get side length for hexagon 2
mov edx, OFFSET prompt2
call WriteString
call ReadDec
mov sideHex2, eax
call Crlf

; Calculate perimeter of hexagon 1
mov ecx, 6; Loop 6 times for 6 sides
mov eax, 0; Initialize perimeter accumulator
mov ebx, sideHex1; Load side length of hexagon 1
calcPerimeter1:
add eax, ebx; Add side length to perimeter
loop calcPerimeter1
mov Perimeter_hexagon1, eax

; Calculate perimeter of hexagon 2
mov ecx, 6; Loop 6 times for 6 sides
mov eax, 0; Initialize perimeter accumulator
mov ebx, sideHex2; Load side length of hexagon 2
calcPerimeter2:
add eax, ebx; Add side length to perimeter
loop calcPerimeter2
mov Perimeter_hexagon2, eax

; Calculate total perimeter
mov eax, Perimeter_hexagon1
add eax, Perimeter_hexagon2
mov TotalPerimeter, eax

; Display results
mov edx, OFFSET result1
call WriteString
call Crlf

mov eax, Perimeter_hexagon1
call WriteDec
call Crlf

mov eax, Perimeter_hexagon2
call WriteDec
call Crlf
call Crlf

mov edx, OFFSET totalPerimeterMsg
call WriteString
mov eax, TotalPerimeter
call WriteDec
call Crlf

exit
main ENDP
END main