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

/* @brief: Header fuer Programme, die unsere libBCM nutzen wollen.
 *
 * Der Header definiert unsere Bibliotheksfunktionen als "extern"
 * und stellt die einheitlichen Definitionsheader zur Verfuegung.
 */

#ifndef _HAVE_BCM2836_H_
#define _HAVE_BCM2836_H_

#include "BCM2836_constants.h"
#include "BCM2836_GPIO_constants.h"
#include "BCM2836_SPI_constants.h"
#include <unistd.h>
#include <stdint.h>

int  BCM2836_Open();
void BCM2836_Close();
void BCM2836_GPIO_PinSelFun(unsigned int gpiono, gpfsel_function fun);
void BCM2836_GPIO_PinSet(unsigned int gpiono);
void BCM2836_GPIO_PinClr(unsigned int gpiono);


#define BCM2836_SPI0_RELOFFSET BCM2836_SPI0_BASEOFFSET-BCM2836_GPIO_BASEOFFSET
#define BCM2836_SPI_REGADDR(x) bcm2836_baseaddr_ptr + BCM2836_SPI0_RELOFFSET + x

void BCM2836_SPI0_Send(size_t dataSz, uint8_t *txdata_ptr, uint8_t *rxdata_ptr);
void BCM2836_SPI0_Init();

#endif // _HAVE_BCM2836_H_
