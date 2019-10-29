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
.equ FIELD_SIZE,      24
.data
.balign 4
.word 0xAAAAAAAA // Namenslose Variable fuer Anfang, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel
FIELD: .skip FIELD_SIZE*FIELD_TYPE_SIZE, 0
.word 0xEEEEEEEE // Namenslose Variable fuer Ende, macht es einfacher unser Feld im Memory-Viewer zu erkennen, hat sonst keine Funktion im Code/Beispiel

 .text
 .global array_example
.balign 4

 .func array_example
 array_example:
  mov   ip, sp
  stmfd sp!,{r4-r11,lr}
  mov   fp, ip


  ldmfd sp!,{r4-r11,lr}
  bx lr
 .endfunc
