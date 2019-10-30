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
  * @file: DataStructures/structs.S
  *
  * @brief: Enthaelt Beispiel fuer Strukturen (structs)
  */

.equ FAKE_GPIOFSEL_FIELD_SIZE,   5
.equ FAKE_GPIOFSEL_ELEMENT_SIZE, 4

.equ FSEL_MASK,     0b111
.equ FSEL_MODE_XYZ, 6

.data
.balign 4
TESTWORD:           .word 0xFFAFFFFF
FAKE_GPIOFSEL_BASE: .skip FAKE_GPIOFSEL_FIELD_SIZE*FAKE_GPIOFSEL_ELEMENT_SIZE, 0

.text
.global structs_example
.balign 4

.func structs_example
structs_example:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip

  // Lade Testdaten damit wir unsere Operationen besser sehen koennen
  ldr r0, =FAKE_GPIOFSEL_BASE
  ldr r1, =TESTWORD
  ldr r1, [r1]
  str r1, [r0, #(4*2)] // Speichere Testmuster in "GPIOFSEL Register 2"

  // Wir wollen GPFSEL[27] veraendern
  .equ GPIONUMBER, 27
  mov r10, #GPIONUMBER
  mov r9,  #0 // DIVvalue GPIONUMBER/10
  mov r8,  #0 // MODvalue GPIONUMBER%10
  mov r7,  #0 // FELDAddresse

  // Bestimme Adresse der Struktur
  //   ADDR = floor(GPIONUMBER/10) + Base
  // ... wir kennen keine Division; subtrahiere in schleife. Im gleichen Zug bleibt Modulo als ergebniss uebrig.

  structs_example_calcFieldAddr: // template: Sektion
    structs_example_calcFieldAddr_divloop_init: // template: ablehnende schleife
    // while (r9:div=0, r0:mod=27)
    mov r0, r10;
    mov r9, #0
    structs_example_calcFieldAddr_divloop_test:
      // Subtrahiere, solange r0 positiv ist
      subs r0, r0, #10
      bmi  structs_example_calcFieldAddr_divloop_done
      add  r9, r9, #1
      b    structs_example_calcFieldAddr_divloop_test
    structs_example_calcFieldAddr_divloop_done:
    add r0, r0, #10 // r0 ist ins negative gerutsch, korrigiere letzte subraktion
    mov r8, r0

    ldr r0, =FAKE_GPIOFSEL_BASE
    add r7, r0, r9, LSL #2 // R9= 4*(GPIONR/10) +  FAKE_GPIOFSEL_BASE
  structs_example_calcFieldAddr_done:

  structs_example_accessBitfield: // Template: Struktur
    // Lese Element
    ldr r0, [r7]
    // Anzahl der Bits, die wir unser Feld nach rechts schieben muessen: 27%10 * 3
    mov r1, r8, lsl #1
    add r1, r1, r8    // r1 = 2*MODValue + MODValue --> GPIO27 -> 27%10 * 3 = 21

    lsr r0, r0, r1 // Richte unser Feld nach rechts aus
    and r0, r0, #FSEL_MASK

    // Schreibe eine Element
    mov r2, #FSEL_MODE_XYZ // Setze Feld auf Wert

    // Anzahl der Bits, die wir unser Feld nach Links schieben muessen: 27%10 * 3
    mov r1, r8, lsl #1
    add r1, r1, r8    // r1 = 2*MODValue + MODValue --> GPIO27 -> 27%10 * 3 = 21
    lsl r2, r2, r1    // Richte unser Bitfeld korrekt im Register aus

    mov r3, #FSEL_MASK
    lsl r3, r3, r1    // Richte unsere Maske im Bitfeld aus

    // Read-modify-update
    ldr r0, [r7]      // Lade unser aktuelles register
    bic r0, r0, r3    // Clear mit Maske
    orr r0, r0, r2    // Setze unsere Bits

    // Speichere Element
    str r0, [r7]
  structs_example_accessBitfield_done:

  ldmfd sp!,{r4-r11,lr}
  bx lr
.endfunc
