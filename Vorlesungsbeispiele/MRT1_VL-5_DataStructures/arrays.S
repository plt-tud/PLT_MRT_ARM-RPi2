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
  * @file: DataStructures/array.S
  *
  * @brief: Enthaelt Beispiel fuer 1d-Felder
  */

.equ FIELD_TYPE_LSL,  2
.equ FIELD_TYPE_SIZE, 4
.equ ARRAY_SIZE,      24

.equ WIERDFIELD_TYPE_SIZE, 12
.equ WIERDFIELD_SIZE,      8

.data
.balign 4
.word 0xAAAAAAAA // Namenslose Variable fuer Anfang, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel
FIELD:      .skip ARRAY_SIZE*FIELD_TYPE_SIZE, 0
.word 0xEEEEEEEE // Namenslose Variable fuer Ende, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel
WIERDFIELD: .skip WIERDFIELD_SIZE*WIERDFIELD_TYPE_SIZE, 0

 .text
 .global array_example
.balign 4

 .func array_example
 array_example:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // Zugriff auf zur Laufzeit bekanntes Feldelement, e.g. R0 <- FIELD[4]
  //using immediate offset
  array_example_staticAddress:
  .equ FIELD_INDEX, 4
  ldr r3, =FIELD                              // r3 <- base address
  ldr r0, [r3, #(FIELD_INDEX*FIELD_TYPE_SIZE)]  // r0 <- [base + index * 4]
  add r0,  r0, #FIELD_INDEX                   // r0 <- r0 + 4
  str r0, [r3, #(FIELD_INDEX*FIELD_TYPE_SIZE)]  // r0 -> [base + index * 4]

  // Zugriff auf zur Laufzeit unbekanntes Feldelement
  //   mit Feldelementen arbitraerer Groesse
  //using multiplication
  .equ FIELD_INDEX, 3
  mov r2, #FIELD_INDEX                  // r2 <- 3 (index)
  array_example_dynamicAddress_general:
    ldr r0, =FIELD_TYPE_SIZE
    mul r0, r2, r0							//r0 <- index * type_size
    ldr r1, =FIELD							//r1 <- base
    add r1, r0, r1							//r1 <- r0 + r1 i.e (index * type_size) + base

    ldr r0, [r1]     // r0 <- [base + index * 4]  : load the value
    add r0, r0, #42  // r0 <- r0 + 3 // r0 <- r0 + 42 : work on the value
    str r0, [r1]     // r0 -> [base + index * 4] : storet he changed value back in memory
  array_example_dynamicAddress_general_end:

  // Zugriff auf zur Laufzeit unbekanntes Feldelement
  //   mit Feldelementgroesse %2
  //using shift
  array_example_dynamicAddress_optimal:
  .equ FIELD_INDEX, 3
    mov r2, #FIELD_INDEX                  // r2 <- 3 (index)
    ldr r3, =FIELD   					// r3 <- base
    ldr r0, [r3, r2, LSL #FIELD_TYPE_LSL] // r0 <- [base + index * 4]
    add r0, r0, #FIELD_INDEX              // r0 <- r0 + 3
    str r0, [r3, r2, LSL #FIELD_TYPE_LSL] // r0 -> [base + index * 4]
  array_example_dynamicAddress_optimal_end:

  // Iteriere über ein Feld mit immediate post-indexed
  // Template: for-Schleife
  // for (r2=BASEADDR, r3=0, r3<FIELDELEMENTS, r3+=1)
  array_example_dynamicAddress_iterate_init:
    ldr r2, =FIELD
    mov r3, #0				//counter or the index to be accessed
  array_example_dynamicAddress_iterate_condition:
    cmp r3,#ARRAY_SIZE
    bge array_example_dynamicAddress_iterate_end

    // Berechne Element-Addresse
    ldr r0, =FIELD_TYPE_SIZE
    mul r1, r0, r3
    ldr r0, =FIELD
    add r1, r1, r0  // r1 = FIELD_TYPE_SIZE*i + BASE_ADDR

    // Greife auf Element zu
    ldr r0,[r1]             // r0 -> [r3] then r3 <- r3+4
    add r0, r0, r3          // Wert aendern
    str r0,[r1]             // r0 -> [r3] then r3 <- r3+4

  array_example_dynamicAddress_iterate_update:
    add r3, r3, #1
    b array_example_dynamicAddress_iterate_condition
  array_example_dynamicAddress_iterate_end:

  ldmfd sp!,{r4-r11,lr}
  bx lr
 .endfunc
