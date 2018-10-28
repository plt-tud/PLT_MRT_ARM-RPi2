/*
 * main.S
 *
 *  Created on: 01.11.2017
 *      Author: mrt
 */

.global main
.func main
.balign 4

fib:
  // r0 = Parameter
  CMP r0, #0		// if (n==0) {
  MOVEQ r0, #0
  BXEQ LR           // return 0; }
  CMP r0, #1		// if (n==1) {
  MOVEQ r0, #1
  BXEQ LR           // return 1;}
  MOV R1, R0 		// lokale Kopie von n
  MOV R2, #0 		// temp = 0
  SUB R0, #1
  push {r1-r11, lr}
  BL fib
  pop {r1-r11, lr}
  MOV R2, R0 		// temp = fib(n-1)
  MOV R0, R1
  SUB R0, #2
  push {r1-r11, lr}
  BL fib
  pop {r1-r11, lr}
  ADD R2, R0 		// temp = temp + fib(n-2)
  MOV R0, R2 		// return temp
  BX LR

main:
  push {r1-r11, lr}
  MOV r0, #4
  BL fib
  pop {r1-r11, lr}
  BX  LR
