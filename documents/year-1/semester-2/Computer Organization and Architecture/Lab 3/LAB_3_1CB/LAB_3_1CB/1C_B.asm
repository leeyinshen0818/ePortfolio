TITLE Lab 3 Part 1C

; Authors: LEE YIN SHEN / BRENDAN CHIA YAN FEI
; Date: 21 JUNE 2024
; LAB 3 Part 1C B

INCLUDE Irvine32.inc

.data
titlemsg BYTE "Calculate SUM (unsign INT) index (Odd or Even) in array Hello[6] : ", 0
prompt BYTE "Integer Input: ", 0
hello DWORD 6 DUP(? )
resultMsg BYTE "Result Sum Hello[index]:", 0
promptEVEN BYTE "Sum Hello[even] index location : ", 0
promptODD BYTE "Sum Hello[odd] index location : ", 0
TotalEVEN DWORD ?
TotalODD DWORD ?

.code
main PROC
; Display the title message
mov edx, OFFSET titlemsg
call WriteString
call Crlf
call Crlf

; Initialize TotalEVEN and TotalODD to 0
mov TotalEVEN, 0
mov TotalODD, 0

; Loop to read 6 integers from user and store in hello array
mov ecx, 6; loop counter
mov esi, OFFSET hello; array index
input_loop :
mov edx, OFFSET prompt
call WriteString; display prompt
call ReadInt; read integer input
mov[esi], eax; store input in hello array
add esi, 4; move to next array element
loop input_loop
call Crlf

; Calculate TotalEVEN(values at even indices : HELLO[0], HELLO[2], HELLO[4])
mov ecx, 3; loop counter
mov esi, OFFSET hello; array index
mov edi, 0; element index for even positions
countEVEN :
mov eax, [esi + edi]
add TotalEVEN, eax
add edi, 8; move to next even position
loop countEVEN

; Calculate TotalODD(values at odd indices : HELLO[1], HELLO[3], HELLO[5])
mov ecx, 3; loop counter
mov esi, OFFSET hello; array index
mov edi, 4; element index for odd positions
countODD :
mov eax, [esi + edi]
add TotalODD, eax
add edi, 8; move to next odd position
loop countODD

; Display results
mov edx, OFFSET resultMsg
call WriteString
call Crlf
call Crlf

; Display TotalEVEN
mov edx, OFFSET promptEVEN
call WriteString
mov eax, TotalEVEN
call WriteDec
call Crlf

; Display TotalODD
mov edx, OFFSET promptODD
call WriteString
mov eax, TotalODD
call WriteDec
call Crlf

; Exit program
exit
main ENDP
END main