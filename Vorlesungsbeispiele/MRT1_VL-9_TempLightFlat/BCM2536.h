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

// Register/Offset-Definitionen und Konstanten fuer GPIOs
.extern BCM2536_GPIO_Open, BCM2536_GPIO_Close, BCM2536_GPIO_PinSelFun, BCM2536_GPIO_PinSet, BCM2536_GPIO_PinClr
.include "BCM2536_GPIO_constants.h"

// Register/Offset-Definitionen und Konstanten fuer SPI
.extern BCM2536_SPI0_GetBase, BCM2536_SPI0_Init, BCM2536_SPI0_Send
.include "BCM2536_SPI_constants.h"

