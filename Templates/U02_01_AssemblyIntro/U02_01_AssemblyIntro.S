/* Assembly Intro
 * Simple assembler testbed with data and text section
 *
 * Created: 12.10.2015
 * Author:  Chris Iatrou (Chris_Paul.Iatrou@tu-dresden.de)
 */

/* Data Section */
.data
.balign 4
MYVAR1:
.word 0x89ABCDEF

/* Code Section */
/* Code Section */
.text
.balign 4
.global main
.func   main

main:
        ldr r1, MYVAR1_ADDR // r1 = &MYVAR
        ldr r1, [r1]        // r1 = *MYVAR
        mov r2, #16
        str r2, [r1]		// *MYVAR = 16
        bx lr


/* Address lables */
MYVAR1_ADDR: .word MYVAR1
