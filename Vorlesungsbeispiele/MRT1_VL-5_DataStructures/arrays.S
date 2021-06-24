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

.data
.balign 4
.word 0xAAAAAAAA // Namenslose Variable fuer Anfang, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel
FIELD:      .skip ARRAY_SIZE*FIELD_TYPE_SIZE, 0
.word 0xEEEEEEEE // Namenslose Variable fuer Ende, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel

 .text
 .global array_example
.balign 4

 .func array_example
 array_example:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // Access array element at predefined index, e.g. FIELD[4] = FIELD[4] + 4
  // using ldr with immediate offset
  array_example_staticAddress:
  .equ FIELD_INDEX, 4
  ldr r3, =FIELD                              	// r3: addr_base
  ldr r0, [r3, #(FIELD_INDEX*FIELD_TYPE_SIZE)]  // r0: element = mem(base + index * 4)
  												// ldr Rt, [Rn, #n] : load with immediate offset n
  add r0,  r0, #FIELD_INDEX                   	// r0: element = element + 4
  str r0, [r3, #(FIELD_INDEX*FIELD_TYPE_SIZE)]  // mem(base + index * 4) = element

  // Access element at dynamic index in array of abritary size using multiplication.
  // E.g. FIELD[i] = FIELD[i] + 3
  .equ FIELD_INDEX, 3
  mov r2, #FIELD_INDEX                  // r2 <- 3 (index)
  array_example_dynamicAddress_general:
    ldr r0, =FIELD_TYPE_SIZE
    mul r0, r2, r0							// r0 <- addr_relative = index * type_size
    ldr r1, =FIELD							// r1 <- addr_base
    add r1, r0, r1							// r1 <- r0 + r1
    										// r1 <- addr_element = addr_relative + addr_base

    ldr r0, [r1]     // r0 <- [addr_element]     : load the value
    add r0, r0, #42  // r0 <- r0 + 42 : modify the value
    str r0, [r1]     // r0 -> [base + index * 4] : store the changed value back in memory
  array_example_dynamicAddress_general_end:

  // Access element at dynamic index in array of size 2^x using bit shifting.
  array_example_dynamicAddress_optimal:
  .equ FIELD_INDEX, 3
    mov r2, #FIELD_INDEX                  	// r2: index = 3
    ldr r3, =FIELD   						// r3 = addr_base
    ldr r0, [r3, r2, LSL #FIELD_TYPE_LSL] 	// r0: element = mem(addr_base + index << 2)  (LSL - left shift logical)
    										//   		   = mem(addr_base + index * 4)
    										// ldr Rt, [Rn, Rm, LSL n] : load with register offset and shift n bits
    add r0, r0, #FIELD_INDEX              	// r0: element = element + 3
    str r0, [r3, r2, LSL #FIELD_TYPE_LSL] 	// mem(addr_base + index * 4) = element
  array_example_dynamicAddress_optimal_end:

  // Iterate over array with immediate post-indexed loading
  // for (r2=addr_base, r3=0; r3<FIELDELEMENTS, r3+=1)
  array_example_dynamicAddress_iterate_init:
    ldr r2, =FIELD			// r2: addr_base
    mov r3, #0				// r3: i = 0	(counter of for loop and index for accessing array)s
  array_example_dynamicAddress_iterate_condition:
    cmp r3,#ARRAY_SIZE
    bge array_example_dynamicAddress_iterate_end

    // calculate array element's address
    ldr r0, =FIELD_TYPE_SIZE
    mul r1, r0, r3			// r1 = i * FIELD_TYPE_SIZE
    ldr r0, =FIELD			// r0 = addr_base
    add r1, r1, r0  		// r1: addr_element = i * FIELD_TYPE_SIZE + addr_base

    // access and modify element
    ldr r0,[r1]             // r0: element = mem(addr_element)
    add r0, r0, r3          // r0: element += i
    str r0,[r1]             // mem(addre_element) = element

  array_example_dynamicAddress_iterate_update:
    add r3, r3, #1			// i++
    b array_example_dynamicAddress_iterate_condition
  array_example_dynamicAddress_iterate_end:

  ldmfd sp!,{r4-r11,lr}
  bx lr
 .endfunc
