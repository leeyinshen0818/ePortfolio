TITLE Lab 3

; Authors: LEE YIN SHEN / BRENDAN CHIA YAN FEI
; Date: 21 JUNE 2024
; Program: Part 2C

INCLUDE Irvine32.inc

.data
str1 BYTE "Enter a decimal: ", 0
decNum DWORD ?
promptBad BYTE "Invalid input, please enter again", 0

.code
main PROC
mov edx, offset str1
call writestring
read : call ReadDec
jnc goodInput
mov edx, OFFSET promptBad
call WriteString
jmp read; go input again
goodInput :
mov decNum, eax; store good value
call WriteDec


exit

main ENDP
END main
