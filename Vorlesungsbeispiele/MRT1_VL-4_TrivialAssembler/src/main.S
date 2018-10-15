@ Assembly Intro
@ Simple assembler testbed with data and text section
@
@ Date: 14.10.2018
@ Author:  Leon Urbas (leon.urbas@tu-dresden.de)
@
@ Toolchain Setting:
@	Cross GCC Assembler: -adhlns="$@.lst"

.data			@ directive .data tells the assembler to open a Data Section
.balign 4 		@ data shall be word aligned (makes it faster)
source:         @ This label defines the name of the variable
	.word 0x2F534350 @ directive .word reserves 4 bytes (i.e. a word) and initializes it to some value
	.word 0x20455350
	.word 0x20445554
	.word 0x3154524D
	.word 0x38313032
	.word 0x20313055
	.word 0x204D5241
	.word 0x004D5341
dest:			@ a new variable begins
	.skip 32	@ reserves 32 bytes of free space

.text			@ directive .text tells the assembler to begin the Code Section
.balign 4		@ instructions must be word-alignd
.global main	@ directive .global exports the symbol for the linker

.func main		@ directive .func helps the debugger
main:
	stmfd sp!,{r0-r9,lr}@ save r0-r9,lr on the stack
	ldr r8,=source	  	@ r8 <- adresse von source
	ldr r9,=dest     	@ r9 <- adresse von ziel
	ldmia r8,{r0-r7} 	@ copy source into registers
	stmia r9,{r0-r7} 	@ copy registers into dest
	ldmfd sp!,{r0-r9,lr}@ restore r0-r9 from the stack

	ldr r0, =0			@ r0 <- #0
	bx lr				@ return from subroutine
.endfunc		@ directive .endfunc helps debugger
