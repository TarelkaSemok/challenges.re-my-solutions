/*
gcc.exe -masm=intel -c Main.c
gcc.exe Main.o -o Main.exe
*/

#include <conio.h>
#include <stdio.h>

char* arr = "aaabbcdaaaacdaaa";
void chall()
{
	asm(
		"mov ecx, 0x10;\
		mov esi, 0x10;\
		mov rdx, arr;\
		push	rbx;\
		mov	rax, rdi;\
		mov	rbx, rdi;\
		sub	rsp, 32;\
		test	rcx, rcx;\
		jne	.L21;\
		add	rsp, 32;\
		pop	rbx;\
		ret;\
	.L21:\
		lea	rdi, [4+rcx*4];\
		mov	QWORD PTR [rsp+24], rdx;\
		mov	QWORD PTR [rsp+16], rsi;\
		mov	QWORD PTR [rsp+8], rcx;\
		call	malloc;\
		mov	rcx, QWORD PTR [rsp+8];\
		mov	r9d, 1;\
		mov	DWORD PTR [rax], -1;\
		mov	DWORD PTR [rax+4], 0;\
		mov	rsi, QWORD PTR [rsp+16];\
		mov	rdx, QWORD PTR [rsp+24];\
		cmp	r9, rcx;\
		je	.L22;\
	.L8:\
		mov	edi, DWORD PTR [rax+r9*4];\
		lea	r8d, [rdi+1];\
		test	r8d, r8d;\
		mov	DWORD PTR [rax+4+r9*4], r8d;\
		jle	.L5;\
		movzx	r10d, BYTE PTR [rdx+r9];\
		movsx	r8, r8d;\
		cmp	r10b, BYTE PTR [rdx-1+r8];\
		jne	.L7;\
		jmp	.L5;\
	.L23:\
		movsx	r8, r8d;\
		cmp	BYTE PTR [rdx-1+r8], r10b;\
		je	.L5;\
	.L7:\
		mov	r8d, DWORD PTR [rax-4+r8*4];\
		add	r8d, 1;\
		test	r8d, r8d;\
		mov	DWORD PTR [rax+4+r9*4], r8d;\
		jg	.L23;\
	.L5:\
		add	r9, 1;\
		cmp	r9, rcx;\
		jne	.L8;\
	.L22:\
		xor	r8d, r8d;\
		xor	r10d, r10d;\
		xor	edi, edi;\
	.L9:\
		cmp	rdi, rsi;\
		jae	.L24;\
	.L14:\
		test	r8d, r8d;\
		js	.L10;\
		movsx	r9, r8d;\
		movzx	r11d, BYTE PTR [rdx+r9];\
		cmp	BYTE PTR [rbx+rdi], r11b;\
		je	.L10;\
		cmp	rdi, rsi;\
		mov	r8d, DWORD PTR [rax+r9*4];\
		jb	.L14;\
	.L24:\
		xor	ebx, ebx;\
	.L13:\
		mov	rdi, rax;\
		call	free;\
		add	rsp, 32;\
		mov	rax, rbx;\
		pop	rbx;\
		ret;\
	.L10:\
		add	r8d, 1;\
		add	r10d, 1;\
		movsx	rdi, r8d;\
		cmp	rdi, rcx;\
		je	.L18;\
		movsx	rdi, r10d;\
		jmp	.L9;\
	.L18:\
		movsx	r10, r10d;\
		sub	r10, rcx;\
		add	rbx, r10;\
		jmp	.L13;"
	);
}

int main(int argc, char *argv[])
{
	chall();
	printf("Hell");
    return 0;
}
