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

	Lit10 DW 10
	Lit2 DW 2
	Lit4 DW 4

section .bss ;used to declare uninitialized variables

	TempChar RESB 1
	testchar RESB 1
	ReadInt RESW 1
	tempint RESW 1
	negflag RESB 1

	a RESW 1
	b RESW 1
	c RESW 1
	Bob RESW 1
	Jane RESW 1
	ans RESW 1
	T1 RESW 1
	T2 RESW 1
	T3 RESW 1
	T4 RESW 1
	T5 RESW 1
	T6 RESW 1
	T7 RESW 1

section .text
global _start
_start: nop

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [a], ax
	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [b], ax
	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [c], ax
	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [Bob], ax
	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [Jane], ax
	mov ax, [Bob]
	add ax, [Jane]
	mov [T1], ax
	mov ax, [T1]
	sub ax, [Lit10]
	mov [T2], ax
	mov dx, 0
	mov ax, [T2]
	mov bx, [Lit2]
	div bx
	mov [T3], eax
	mov ax, [T3]
	mov bx, [Lit4]
	mul bx
	mov [T4], eax
	mov ax, [a]
	mov bx, [T4]
	mul bx
	mov [T5], eax
	mov ax, [b]
	add ax, [c]
	mov [T6], ax
	mov dx, 0
	mov ax, [T5]
	mov bx, [T6]
	div bx
	mov [T7], eax
	mov ax, [T7]
	mov [ans], ax
	mov ax, [ans]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h

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

