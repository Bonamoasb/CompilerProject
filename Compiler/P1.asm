sys_exit equ 1
sys_read equ 3
sys_write equ 4
stdin equ 0
stdout equ 1
stderr equ 3

section .data ;used to declare constants

	userMsg db 'Enter an integer(less than 32,765): '
	lenUserMsg equ $-userMsg
	displayMsg db 'You entered: '
	lenDisplayMsg equ $-displayMsg
	newline db 0xA
	Ten DW 10
	printTempchar db 'Tempchar = : '
	lenprintTempchar equ $-printTempchar
	Result db 'Ans = '
	ResultValue db 'aaaaa'
	db	0xA
	ResultEnd equ $-Result
	num times 6 db 'ABCDEF'
	numEnd equ $-num


section .bss ;used to declare uninitialized variables

	TempChar RESB 1
	testchar RESB 1
	ReadInt RESW 1
	tempint RESW 1
	negflag RESB 1

	X RESW 1
	Y RESW 1
	T1 RESW 1

section .text
global _start
_start: nop

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [X], ax
	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [Y], ax
	mov ax, [X]
	cmp ax, [Y]
	JL L1
	mov ax, [X]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h
	Jmp L2
	L1: NOP
	mov ax, [Y]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h
	L2: NOP

Jmp finish

PrintString:
	push ax
	push dx
	mov eax, 4
	mov ebx, 1
	mov ecx, userMsg
	mov edx, lenUserMsg
	int 80h
	pop dx
	pop ax
	ret

GetAnInteger:
	mov eax, 3 ;Read
	mov ebx, 2 ;Device
	mov ecx, num ;Buffer Address
	mov edx, 6 ;Max Characters
	int 0x80
	mov edx, eax
	mov eax, 4
	mov ebx, 1
	mov ecx, num
	int 80h

ConvertStringToInteger:
	mov ax, 0 ;Hold Integer
	mov [ReadInt], ax
	mov ecx, num ;Read
	mov bx, 0 ;Read
	mov bl, byte [ecx] ;Read

Next:
	sub bl, '0'
	mov ax, [ReadInt]
	mov dx, 10
	mul dx
	add ax, bx
	mov [ReadInt], ax
	mov bx, 0
	add ecx, 1
	mov bl, byte[ecx]
	cmp bl, 0xA
	jne Next
	ret

ConvertIntegerToString:
	mov ebx, ResultValue + 4

ConvertLoop:
	sub dx, dx
	mov cx, 10
	div cx
	add dl, '0'
	mov [ebx], dl
	dec ebx
	cmp ebx, ResultValue
	jge ConvertLoop
	ret

Terminate:
finish:

	mov eax, sys_exit
	xor ebx, ebx
	int 80h

