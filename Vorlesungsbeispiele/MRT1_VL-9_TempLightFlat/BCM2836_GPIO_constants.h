/*
 * Copyright (c) 2018 Leon Urbas <leon.urbas@tu-dresden.de>
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

// GPFSEL Codes (BCM2835 ARM Peripherals, 2012, Table 6-1, p. 92)
.equ BCM2836_GPFSEL_INPUT,  0b000
.equ BCM2836_GPFSEL_OUTPUT, 0b001
.equ BCM2836_GPFSEL_ALT0,   0b100
.equ BCM2836_GPFSEL_ALT1,   0b101
.equ BCM2836_GPFSEL_ALT2,   0b110
.equ BCM2836_GPFSEL_ALT3,   0b111
.equ BCM2836_GPFSEL_ALT4,   0b011
.equ BCM2836_GPFSEL_ALT5,   0b010

// Aus BCM2836 Datenblatt, Abschnitt GPIOs
.equ BCM2836_GPIO_BASEOFFSET,   0x200000
.equ BCM2836_GPIO_LASTADDRESS,  0x2000B4
.equ BCM2836_GPIO_MEMSIZE,      0x4100 // Must be >=4k according to manual !
.equ BCM2836_GPIO_BASE, BCM2836_PERI_BASE + BCM2836_GPIO_BASEOFFSET

.equ BCM2836_GPFSEL_OFFSET, 0
.equ BCM2836_GPSET_OFFSET,  0x1C
.equ BCM2836_GPCLR_OFFSET,  0x28

.equ BCM2836_SPI0_BASEOFFSET, 0x204000
.equ BCM2836_SPI1_BASEOFFSET, 0x215000
.equ BCM2836_SPI2_BASEOFFSET, 0x215080
