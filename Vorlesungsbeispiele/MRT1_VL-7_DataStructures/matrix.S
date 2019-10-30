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

 /**
  * @file: DataStructures/matrix.S
  *
  * @brief: Enthaelt Beispiel fuer 2d-Felder
  */

/*  MATRIX[4,3] aus VL:
 *      ---j--->
 *     +--+--+--+
 *     |  |  |  |  |
 *     +--+--+--+  |
 *     |  |  |  |  |
 *     +--+--+--+  | i
 *     |  |  |  |  |
 *     +--+--+--+  |
 *     |  |  |  |  V
 *     +--+--+--+
 */
.equ P_MATRIX_DIM_I, 4        // i 0..3
.equ P_MATRIX_DIM_J, 3        // j 0..2
.equ P_MATRIX_ELEMENT_SIZE, 4 // 4 Byte

 .data
 .balign 4
.word 0xAAAAAAAA // Nur Marker fuer Speicher
MATRIX: .skip P_MATRIX_DIM_I*P_MATRIX_DIM_J*P_MATRIX_ELEMENT_SIZE, 0
.word 0xEEEEEEEE // Nur Marker fuer Speicher


 .text
 .global matrix_example
.balign 4

 .func matrix_example
 matrix_example:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // Greife zu auf MATRIX[2,1]
  .equ P_ACCESS_J, 2
  .equ P_ACCESS_I, 1

  mov r9,  #P_ACCESS_J
  mov r10, #P_ACCESS_I

  // Template: Sektion
  matrix_example_calc2daddress:
    // Berechne:    P_MATRIX_ELEMENT_SIZE*P_MATRIX_DIM_I*j + P_MATRIX_ELEMENT_SIZE*i
    //           =  4*3*j + 4*i
    //           =  12*j  + (4*i)
    //           =  4*(2j+j)  + (4*i)
    .if P_MATRIX_DIM_I != 4 || P_MATRIX_DIM_I==3
      // Safeguard gegen versehentliches Zahlendrehen
      .error "Indexberechnung ist fuer geg. Matrixgroesse nicht gueltig"
    .endif

    lsl r1, R10, #2         // r1 = 4i
    add r0, r9, r9, LSL #1  // r0 = r9 + r9 * 2
    add r0, r1, r0, LSL #2  // r0 = 4i + (2i+i)*4
    ldr r1, =MATRIX
    add r1, r0, r1          // r1 = addrof(feld[i,j]) = BASE + 4*4*j + 4*i
  matrix_example_calc2daddress_end:

  // Template: Sektion
  // Zugriff auf Feld[2,1]
  matrix_example_accessdata:
    ldr r0, [r1]
    add r0, #42 // Veraendere Wert
    str r0, [r1]
  matrix_example_accessdata_end:

  ldmfd sp!,{r4-r11,lr}
  bx lr
 .endfunc
