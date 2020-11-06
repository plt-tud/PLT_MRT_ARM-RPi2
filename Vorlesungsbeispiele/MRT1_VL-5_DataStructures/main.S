/*
 * Copyright (c) 2018 Leon Urbas   <leon.urbas@tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen,
 * inklusive und ohne Ausnahme mit dem Recht, sie zu verwenden,
 * zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen,
 * zu verbreiten, zu unterlizenzieren und/oder zu verkaufen, und
 * Personen, denen diese Software überlassen wird, diese Rechte
 * zu verschaffen, unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */
// Textdefinitions
.equ FIELD_TYPE_SIZE, 4
.equ FIELD_TYPE_LSL,  2
.equ FIELD_SIZE,      24
.data
FIELD: .skip FIELD_SIZE*FIELD_TYPE_SIZE, 0
.balign 4

.text
.global main

.func main
main:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  bl array_example

    // Adressberechnung für Feldgrößen ungleich 4,8,16,...
  calcAddressWithShiftAddMult:
  .equ FIELD2_TYPE_SIZE,12
  .equ FIELD2_SIZE, FIELD_SIZE / FIELD2_TYPE_SIZE
  .equ FIELD2_SRC_INDEX, 3
  .equ FIELD2_DST_INDEX, 5

  ldr r3, =FIELD                 // r3 <- base address
  mov r2, #FIELD2_SRC_INDEX      // r2 <- index
  rsb r4, r2, #FIELD2_DST_INDEX  // r4 <- #FIELD2_DST_INDEX - r2 i.e. difference between source and destination
  .if FIELD2_TYPE_SIZE!=12         // this code is valid for type size = 12 only
    .error "Optimierter Zugriff nur fuer Elementgroesse 12 gueltig"
  .endif

    ADD R4,R4,R4,LSL #1            // calculate distance between SRC and DST
    LSL R4, R4, #2

    ADD R2,R2,R2,LSL #1        // 12*i = (i*2+i)*4
    LDR R0,[R3,R2,LSL#2]!      // r0 <- [r3+r2*FIELD2_TYPE_SIZE], then r3<-r3+r2*FIELD2_TYPE_SIZE
    STR R0,[R3,R4]             // r0 -> [r3+r2*FIELD2_TYPE_SIZE + Distance]

    LDR R0,[R3,#4]!            // r0 <- next four bytes
    STR R0,[R3,R4]             // r0 -> [r3+r2*FIELD2_TYPE_SIZE + Distance]

    LDR R0,[R3,#4]!            // r0 <- next four bytes
    STR R0,[R3,R4]             // r0 -> [r3+r2*FIELD2_TYPE_SIZE + Distance]
  calcAddressWithShiftAddMult_end:

  bl matrix_example

  bl structs_example

	stmfd sp!,{r4-r11,lr}
	bx    lr
.endfunc
