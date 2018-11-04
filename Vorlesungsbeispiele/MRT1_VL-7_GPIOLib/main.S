.global main
.type main, %function

.include "BCM2536.h"
.include "SYSCALL.h"

.equ GPIO_RED,		26
.equ GPIO_YELLOW,	27
.equ GPIO_GREEN, 	22

.data
.balign 4
bcm2536_msg_err_open: .asciz "error initializing bcm2536"
.set bcm2536_mln_err_open, . - bcm2536_msg_err_open

.text
.balign 4
main:
	push {fp,lr}		// safe relevant registers (2)
	add fp,sp,#((2-1)*4)// set frame pointer to lr at bottom of local stack

	bl BCM2536_GPIO_Open
	cmp r0,#0
	bne err_open

	bl BCM2536_GPIO_PinSelDump

	mov r0,#GPIO_RED
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_YELLOW
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	mov r0,#GPIO_GREEN
	mov r1,#BCM2536_GPFSEL_OUTPUT
	bl BCM2536_GPIO_PinSelFun

	bl BCM2536_GPIO_PinSelDump

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
exit:
	pop {fp,pc} // restore & return

err_open:
	push {r0,r7}
	mov r0,#1	// stdout
	ldr r1,=bcm2536_msg_err_open
	mov	r2,#bcm2536_mln_err_open
	mov r7,#SYSCALL_WRITE
	swi #0
	pop {r0,r7}
	bal exit
