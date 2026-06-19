INCLUDE Irvine32.inc

; TITLE: FINAL PROJECT PART 2
; EXPLAINER: LEE YIN SHEN
; POLYNOMIAL EQUATION: y = 12 * x ^ 3 + 18 * x ^ 2 + 28 * x + 4

.data	
coef1 DWORD 12                   
coef2 DWORD 18                   
coef3 DWORD 28                   
coef4 DWORD 4                    
max_loop DWORD ?                 
capture_msec_before DWORD ?      ; Variable to store time before benchmark
capture_msec_after DWORD ?       ; Variable to store time after benchmark
sum DWORD ?                      
x DWORD ?                        

msg1 BYTE "Welcome to CPU Benchmark Program", 0Dh, 0Ah, 0   
msg2 BYTE "Benchmark CPU time Using Equation y = 12*x^3 + 18*x^2 + 28*x + 4", 0 
msg3 BYTE "(with delay coef1,coef2,coef3,coef4 = 12,18,28,4 msec)", 0Ah, 0Dh, 0 
msg4 BYTE "Enter Number of Looping (N) = ", 0 
msg5 BYTE "CPU time Stress Test in progress...", 0Dh, 0Ah, 0 
msg6 BYTE "Result:", 0Dh, 0Ah, 0 ; Result message
msg7 BYTE "First Capture Execution time in milliseconds: ", 0 
msg8 BYTE "Second Capture Execution time in milliseconds: ", 0 
msg9 BYTE "Difference Execution time in milliseconds: ", 0 
msg10 BYTE "Value of Sum from the Stress Test (polynomial) = ", 0 
msg11 BYTE "Press 'y' to continue or 'n' to exit the benchmark: ", 0 

.code
main PROC

main_menu:
call Clrscr                     ; Clear the screen
mov edx, OFFSET msg1            ; Load address of msg1 into edx
call WriteString                ; Display msg1
call Crlf                       ; Print a newline

mov edx, OFFSET msg2            ; Load address of msg2 into edx
call WriteString                ; Display msg2
call Crlf                       ; Print a newline

mov edx, OFFSET msg3            ; Load address of msg3 into edx
call WriteString                ; Display msg3
call Crlf                       ; Print a newline

mov edx, OFFSET msg4            ; Load address of msg4 into edx
call WriteString                ; Display msg4
call ReadDec                    ; Read user input (number of loops)
mov[max_loop], eax              ; Store user input in max_loop

mov edx, OFFSET msg5            ; Load address of msg5 into edx
call WriteString                ; Display msg5
call Crlf                       ; Print a newline

call BenchmarkLoop              ; Call BenchmarkLoop procedure

mov edx, OFFSET msg6            ; Load address of msg6 into edx
call WriteString                ; Display msg6
call Crlf                       ; Print a newline

mov edx, OFFSET msg7            ; Load address of msg7 into edx
call WriteString                ; Display msg7
mov eax, [capture_msec_before]  ; Load capture_msec_before into eax
call WriteDec                   ; Display the time before benchmark
call Crlf                       ; Print a newline

mov edx, OFFSET msg8            ; Load address of msg8 into edx
call WriteString                ; Display msg8
mov eax, [capture_msec_after]   ; Load capture_msec_after into eax
call WriteDec                   ; Display the time after benchmark
call Crlf                       ; Print a newline

mov edx, OFFSET msg9            ; Load address of msg9 into edx
call WriteString                ; Display msg9
mov eax, [capture_msec_after]   ; Load capture_msec_after into eax
sub eax, [capture_msec_before]  ; Subtract capture_msec_before from eax
call WriteDec                   ; Display the time difference
call Crlf                       ; Print a newline

mov edx, OFFSET msg10           ; Load address of msg10 into edx
call WriteString                ; Display msg10
mov eax, [sum]                  ; Load sum into eax
call WriteDec                   ; Display the sum
call Crlf                       ; Print a newline

mov edx, OFFSET msg11           ; Load address of msg11 into edx
call Crlf                       ; Print a newline
call WriteString                ; Display msg11
call ReadChar                   ; Read a character from user
cmp al, 'y'                     ; Compare character with 'y'
je main_menu                  ; If 'y', jump to main_menu
cmp al, 'n'                     ; Compare character with 'n'
je terminate                    ; If 'n', jump to terminate

terminate:
call Crlf                       ; Print a newline
call WaitMsg                    ; Wait for a key press
exit                            ; Exit program
main ENDP

BenchmarkLoop PROC
call GetMseconds                ; Get the current time in milliseconds
mov[capture_msec_before], eax   ; Store the time in capture_msec_before

mov ecx, [max_loop]             ; Load max_loop into ecx (loop counter)
mov[sum], 0                     ; Initialize sum to 0
mov ebx, 1                      ; Initialize x to 1

polynomial_loop:
mov[x], ebx                     ; Store loop counter (ebx) in x
call CalculatePolynomial        ; Call CalculatePolynomial procedure

inc ebx                         ; Increment loop counter (ebx)
loop polynomial_loop            ; Loop until ecx is 0

call GetMseconds                ; Get the current time in milliseconds
mov[capture_msec_after], eax    ; Store the time in capture_msec_after

ret                             ; Return from BenchmarkLoop procedure
BenchmarkLoop ENDP

CalculatePolynomial PROC
; Polynomial calculation y = 12*x^3 + 18*x^2 + 28*x + 4

; Delay for coef1
mov eax, coef1
call Delay

mov eax, [x]                    ; Load x into eax
imul eax, eax                   ; eax = x^2
imul eax, [x]                   ; eax = x^3
imul eax, [coef1]               ; eax = coef1 * x^3
mov edx, eax                    ; Store the result in edx

; Delay for coef2
mov eax, coef2
call Delay

mov eax, [x]                    ; Load x into eax
imul eax, eax                   ; eax = x^2
imul eax, [coef2]               ; eax = coef2 * x^2
add edx, eax                    ; Add to edx

; Delay for coef3
mov eax, coef3
call Delay

mov eax, [x]                    ; Load x into eax
imul eax, [coef3]               ; eax = coef3 * x
add edx, eax                    ; Add to edx

; Delay for coef4
mov eax, coef4
call Delay

add edx, [coef4]                ; Add coef4 to edx
add[sum], edx                   ; Add the result to sum
ret                             ; Return from CalculatePolynomial procedure
CalculatePolynomial ENDP

END main