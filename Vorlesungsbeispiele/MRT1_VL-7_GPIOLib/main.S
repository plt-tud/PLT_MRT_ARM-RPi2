.global main
.type main, %function

.include "BCM2536.h"

.equ GPIO_RED,		26
.equ GPIO_YELLOW,	27
.equ GPIO_GREEN, 	22

.text
.align 4
main:
	push {fp,lr}		// safe relevant registers (2)
	add fp,sp,#((2-1)*4)// set frame pointer to lr at bottom of local stack

	bl BCM2536_GPIO_Open

	mov r0,#GPIO_RED
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_YELLOW
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_GREEN
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

loop: // clear all lights
	mov r0,#GPIO_RED
	bl BCM2536_GPIO_PinClr
	mov r0,#GPIO_YELLOW
	bl BCM2536_GPIO_PinClr
	mov r0,#GPIO_GREEN
	bl BCM2536_GPIO_PinClr

	// red for 2 seconds
	mov r0,#GPIO_RED
	bl BCM2536_GPIO_PinSet
	mov r0,#2
	bl sleep

	// red + yellow for 1 second
	mov r0,#GPIO_YELLOW
	bl BCM2536_GPIO_PinSet
	mov r0,#1
	bl sleep
	mov r0,#GPIO_RED
	bl BCM2536_GPIO_PinClr
	mov r0,#GPIO_YELLOW
	bl BCM2536_GPIO_PinClr


	// green for 2 seconds
	mov r0,#GPIO_GREEN
	bl BCM2536_GPIO_PinSet
	mov r0,#2
	bl sleep
	mov r0,#GPIO_GREEN
	bl BCM2536_GPIO_PinClr

	// yellow for 1 second
	mov r0,#GPIO_YELLOW
	bl BCM2536_GPIO_PinSet
	mov r0,#1
	bl sleep

	bal loop
done:

	bl BCM2536_GPIO_Close
	mov r0, #0
	pop {fp,pc} // restore & return
