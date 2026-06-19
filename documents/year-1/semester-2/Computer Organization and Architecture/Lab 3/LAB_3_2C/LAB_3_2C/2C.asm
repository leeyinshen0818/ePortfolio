TITLE Lab 3

; Authors: LEE YIN SHEN / BRENDAN CHIA YAN FEI
; Date: 21 JUNE 2024
; Program: Part 2C

INCLUDE Irvine32.inc

.data
menu BYTE "Welcome to Simple Math Activities:", 0Dh, 0Ah, 0Dh, 0Ah, 0Dh, 0Ah, 0
menu1 BYTE "Main Menu:", 0Dh, 0Ah, 0Dh, 0Ah, 0
menu2 BYTE "1. To calculate Perimeter Hexagon (Loop and ADD instructions)", 0Dh, 0Ah, 0
menu3 BYTE "2. To calculate SUM (unsigned int) index (Odd or Even) in an Array Matrix", 0Dh, 0Ah, 0Dh, 0Ah, 0
menu4 BYTE "Select Your Input: ", 0
hexagon_prompt1 BYTE "Calculate Perimeter 2-Hexagon (LOOP and ADD instructions):", 0Dh, 0Ah, 0Dh, 0Ah, 0
hexagon_prompt2 BYTE "Input Hexagon 1 (side length): ", 0
hexagon_prompt3 BYTE "Input Hexagon 2 (side length): ", 0
hexagon_result1 BYTE 0Dh, 0Ah, "Result of Perimeter Hexagon 1 and 2:", 0
total_perimeter BYTE 0Dh, 0Ah, "Total Perimeter Hexagon 1 and 2: ", 0Dh, 0Ah, 0
sum_prompt BYTE "Calculate the SUM (unsigned INT) index (Odd or Even) in array Hello[6]:", 0Dh, 0Ah, 0Dh, 0Ah, 0
integer_input BYTE "Integer Input: ", 0
result_sum BYTE 0Dh, 0Ah, "Result Sum Hello[index]:", 0Dh, 0Ah, 0Dh, 0Ah, 0
even_result BYTE "Sum Hello[even] index location: ", 0
odd_result BYTE "Sum Hello[odd] index location: ", 0
yes_no BYTE 0Dh, 0Ah, "Press 'y' to Main Menu or 'n' to Exit the benchmark: ", 0
bye BYTE "Thank you ... BYE!!!", 0
invalid BYTE "Invalid input, please enter again", 0

sideHex1 DWORD ?
sideHex2 DWORD ?
Perimeter_hexagon1 DWORD ?
Perimeter_hexagon2 DWORD ?
TotalPerimeter DWORD ?
HELLO DWORD 6 DUP(? )
TotalEVEN DWORD ?
TotalODD DWORD ?
selection BYTE ?
YesNo_choice BYTE ?

.code
main PROC

call Clrscr; clear screen
mov edx, OFFSET menu
call WriteString; display output
call Crlf; create new line

main_menu :
call Clrscr
mov edx, OFFSET menu1
call WriteString
mov edx, OFFSET menu2
call WriteString
mov edx, OFFSET menu3
call WriteString
mov edx, OFFSET menu4
call WriteString
call ReadChar
mov selection, al
call Crlf

cmp selection, '1'
je perimeter_HexLoop
cmp selection, '2'
je calSum_oddeven
jmp invalid_input

invalid_input :
mov edx, OFFSET invalid
call WriteString
call Crlf
jmp main_menu

perimeter_HexLoop :
call Clrscr
mov edx, OFFSET hexagon_prompt1
call WriteString

mov edx, OFFSET hexagon_prompt2
call WriteString
call ReadDec
mov sideHex1, eax

mov edx, OFFSET hexagon_prompt3
call WriteString
call ReadDec
mov sideHex2, eax

; Calculate Perimeter for Hexagon 1
mov eax, sideHex1
mov ecx, 6
xor edx, edx
hex1_loop :
add edx, eax
loop hex1_loop
mov Perimeter_hexagon1, edx

; Calculate Perimeter for Hexagon 2
mov eax, sideHex2
mov ecx, 6
xor edx, edx
hex2_loop :
add edx, eax
loop hex2_loop
mov Perimeter_hexagon2, edx

; Calculate Total Perimeter
mov eax, Perimeter_hexagon1
add eax, Perimeter_hexagon2
mov TotalPerimeter, eax

; Display Results
mov edx, OFFSET hexagon_result1
call WriteString
call Crlf

; Perimeter Hexagon 1
mov eax, Perimeter_hexagon1
call WriteDec
call Crlf

; Perimeter Hexagon 2
mov eax, Perimeter_hexagon2
call WriteDec
call Crlf

; Total Perimeter
mov edx, OFFSET total_perimeter
call WriteString
mov eax, TotalPerimeter
call WriteDec
call Crlf

; Ask for continuation
jmp YesNo_menu

YesNo_menu :
mov edx, OFFSET yes_no
call WriteString
call ReadChar
mov YesNo_choice, al
call Crlf

cmp YesNo_choice, 'y'
je main_menu
jmp exit_program

calSum_oddeven :
call Clrscr
mov edx, OFFSET sum_prompt
call WriteString

; Read 6 integers into HELLO array
mov ecx, 6
mov esi, OFFSET HELLO
sum_input_loop :
mov edx, OFFSET integer_input
call WriteString
call ReadDec
mov[esi], eax
add esi, 4
loop sum_input_loop

; Calculate TotalEVEN and TotalODD
xor eax, eax
xor ebx, ebx
mov esi, OFFSET HELLO

; Sum even indices
mov ecx, 3
mov edi, 0; hello[0], hello[8], hello[16]
sum_even_loop:
mov eax, [esi + edi]
add TotalEVEN, eax
add edi, 8
loop sum_even_loop

; Sum odd indices
mov ecx, 3
mov edi, 4; hello[4], hello[12], hello[20]
sum_odd_loop:
mov eax, [esi + edi]
add TotalODD, eax
add edi, 8
loop sum_odd_loop

; Display Results
mov edx, OFFSET result_sum
call WriteString
call Crlf

mov edx, OFFSET even_result
call WriteString
mov eax, TotalEVEN
call WriteDec
call Crlf

mov edx, OFFSET odd_result
call WriteString
mov eax, TotalODD
call WriteDec
call Crlf

; Ask for continuation
jmp YesNo_menu

exit_program :
mov edx, OFFSET bye
call WriteString
call Crlf
exit
main ENDP
END main
