/* Calculate Fibonachi numbers in assembler
 * Example function call
 *
 * Created: 12.10.2015
 * Author:  Chris Iatrou (Chris_Paul.Iatrou@tu-dresden.de)
 */
.data
.balign 4
FIBONACHI_OF:
.word 123

// this directive allows the linker to see the "main" label which is our entry point
.text
.global main
.func main

main:
	mov r0, #1	// return 1
	bx lr
