/*
 * Copyright (c) 2018 Leon Urbas <leon.urbas//tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou//tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält die Erlaubnis erteilt sie uneingeschränkt zu nutzen
 * inklusive und ohne Ausnahme mit dem Recht sie zu verwenden
 * zu kopieren zu verändern zusammenzufügen zu veröffentlichen
 * zu verbreiten zu unterlizenzieren und/oder zu verkaufen und
 * Personen denen diese Software überlassen wird diese Rechte
 * zu verschaffen unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

#ifndef _HAVE_BCM2836_GPIO_CONSTANTS_H_
#define _HAVE_BCM2836_GPIO_CONSTANTS_H_

// Aus BCM2836 Datenblatt Abschnitt GPIOs

typedef enum gpfsel_function_t {
	BCM2836_GPFSEL_INPUT  = 0b000,
	BCM2836_GPFSEL_OUTPUT = 0b001,
	BCM2836_GPFSEL_ALT0   = 0b100,
	BCM2836_GPFSEL_ALT1   = 0b101,
	BCM2836_GPFSEL_ALT2   = 0b110,
	BCM2836_GPFSEL_ALT3   = 0b111,
	BCM2836_GPFSEL_ALT4   = 0b011,
	BCM2836_GPFSEL_ALT5   = 0b010
} gpfsel_function;

#define BCM2836_GPIO_BASEOFFSET   0x200000
#define BCM2836_GPIO_LASTADDRESS  0x2000B4
#define BCM2836_GPIO_BASE BCM2836_PERI_BASE + BCM2836_GPIO_BASEOFFSET

#define BCM2836_GPFSEL_OFFSET 0
#define BCM2836_GPSET_OFFSET  0x1C
#define BCM2836_GPCLR_OFFSET  0x28

#endif //_HAVE_BCM2836_GPIO_CONSTANTS_H_

