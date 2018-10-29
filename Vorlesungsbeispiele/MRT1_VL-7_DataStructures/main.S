.global main
.type main, %function

// Textdefinitions
.equ VECTOR_TYPE_SIZE, 4
.equ VECTOR_TYPE_LSL, 2
.equ VECTOR_SIZE, 24
.data
vector: .skip VECTOR_SIZE*VECTOR_TYPE_SIZE, 0
.balign 4

.text
main:
	push {r4,r5,fp,lr}
	add fp,sp,#(4-1)*4

@ Zugriff auf zur Laufzeit bekanntes Feldelement, e.g. R0 <- vector[4]
staticAddress:
.equ VECTOR_INDEX, 4
	ldr r3, =vector	@ r3 <- base address
	ldr r0, [r3,#(VECTOR_INDEX*VECTOR_TYPE_SIZE)]	@ r0 <- [base + index * 4]
	add r0, r0, #VECTOR_INDEX						@ r0 <- r0 + 4
	str r0, [r3,#(VECTOR_INDEX*VECTOR_TYPE_SIZE)]	@ r0 -> [base + index * 4]


@ Zugriff auf zur Laufzeit unbekanntes Feldelement
dynamicAddress:
.equ VECTOR_INDEX, 3
	mov r2, #VECTOR_INDEX					@ r2 <- 3 (index)
	ldr r0, [r3,r2,LSL #VECTOR_TYPE_LSL]	@ r0 <- [base + index * 4]
	add r0, r0, #VECTOR_INDEX				@ r0 <- r0 + 3
	str r0, [r3,r2,LSL #VECTOR_TYPE_LSL]	@ r0 -> [base + index * 4]

@ Iteriere über ein Feld mit immediate post-indexed
iterationByBasePointer:
	ldr r3, =vector				@ r3 <- base address
	mov r0, #0					@ start at zero
1:
	cmp r0,#VECTOR_SIZE			@ stop at VECTOR_SIZE
	bge 2f

	str r0,[r3],#VECTOR_TYPE_SIZE @ r0 -> [r3] then r3 <- r3+4
	add r0,r0,#1				@ r0 <- r0 + 1
	bal 1b
2:

@ Adressberechnung für Feldgrößen ungleich 4,8,16,...
calcAddressWithShiftAddMult:
.equ V2_TYPE_SIZE,12
.equ V2_SIZE, VECTOR_SIZE / V2_TYPE_SIZE
.equ V2_SRC_INDEX, 3
.equ V2_DST_INDEX, 5

	ldr r3, =vector				@ r3 <- base address
	mov r2, #V2_SRC_INDEX		@ r2 <- index
	rsb r4, r2, #V2_DST_INDEX	@ r4 <- #V2_DST_INDEX - r2
.if V2_TYPE_SIZE==12			@ this code is valid for type size = 12 only
	ADD R4,R4,R4,LSL #1			@ calculate distance between SRC and DST
	LSL R4, R4, #2

	ADD R2,R2,R2,LSL #1			@ 12*i = (i*2+i)*4
	LDR R0,[R3,R2,LSL#2]!		@ r0 <- [r3+r2*V2_TYPE_SIZE], then r3<-r3+r2*V2_TYPE_SIZE
	STR R0,[R3,R4]				@ r0 -> [r3+r2*V2_TYPE_SIZE + Distance]

	LDR R0,[R3,#4]!				@ r0 <- next four bytes
	STR R0,[R3,R4]				@ r0 -> [r3+r2*V2_TYPE_SIZE + Distance]

	LDR R0,[R3,#4]!				@ r0 <- next four bytes
	STR R0,[R3,R4]				@ r0 -> [r3+r2*V2_TYPE_SIZE + Distance]
.else
	.err
.endif

@ Mehrdimensionale Felder int[8][3]
calcAddress2DArray:
.equ V3_TYPE_SIZE,4				@ int
.equ V3_DIM1,8					@ [8]
.equ V3_DIM2,3					@ [3]
.equ V3_DIM2_SIZE,V3_DIM2*V3_TYPE_SIZE
.equ V3_INDEX1, 4
.equ V3_INDEX2, 2
	mov r0, #V3_INDEX1
	mov r1, #V3_INDEX2
	ldr r3, =vector
.if V3_DIM2_SIZE==12			@ this code is valid for type size = 12 only
	ADD R2,R0,R0,LSL #1			@ R2 <-  (index1*2 + index1)
	ADD R2,R1,R2,LSL #2			@ R2 <- ((index1*2 + index1) * 4) + index2
	LDR R0,[R3,R2,LSL #2]		@ R0 <- [R3 + R2*4]
	MOV R0,#(V3_INDEX1<<4+V3_INDEX2) @ R0 <- 0x0<index1><index2>
	STR R0,[R3,R2,LSL #2]		@ R0 -> [R3 + R2*4]
.else
	.err
.endif



	pop {r4,r5,fp,pc}
