	.file	"ex1.c"
.globl _dst_rectbmp
	.data
	.align 2
_dst_rectbmp:
	.word	50
	.word	50
	.word	0
	.word	0
.globl _dst_rectpng
	.align 2
_dst_rectpng:
	.word	300
	.word	50
	.word	0
	.word	0
	.section .rdata,"dr"
LC0:
	.ascii "rb\0"
LC1:
	.ascii "pic1.bmp\0"
LC2:
	.ascii "pic2.png\0"
	.text
.globl _SDL_main
	.def	_SDL_main;	.scl	2;	.type	32;	.endef
_SDL_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$88, %esp
	movl	$0, -60(%ebp)
	movl	$32, (%esp)
	call	_SDL_Init
	movl	$0, 12(%esp)
	movl	$16, 8(%esp)
	movl	$480, 4(%esp)
	movl	$640, (%esp)
	call	_SDL_SetVideoMode
	movl	%eax, -12(%ebp)
	movl	$LC0, 4(%esp)
	movl	$LC1, (%esp)
	call	_SDL_RWFromFile
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	_SDL_LoadBMP_RW
	movl	%eax, _my_surfbmp
	movl	$LC2, (%esp)
	call	_IMG_Load
	movl	%eax, _my_surfpng
	movl	$_dst_rectbmp, 12(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	_my_surfbmp, %eax
	movl	%eax, (%esp)
	call	_SDL_UpperBlit
	movl	$_dst_rectpng, 12(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	_my_surfpng, %eax
	movl	%eax, (%esp)
	call	_SDL_UpperBlit
L2:
	cmpl	$0, -60(%ebp)
	jne	L3
L4:
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	call	_SDL_PollEvent
	testl	%eax, %eax
	je	L5
	cmpb	$12, -56(%ebp)
	jne	L4
	movl	$1, -60(%ebp)
	jmp	L4
L5:
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_SDL_Flip
	jmp	L2
L3:
	call	_SDL_Quit
	movl	$0, %eax
	leave
	ret
	.comm	_my_surfbmp, 16	 # 4
	.comm	_my_surfpng, 16	 # 4
