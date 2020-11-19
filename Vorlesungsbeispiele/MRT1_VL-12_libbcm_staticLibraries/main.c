/*
 * Copyright (c) 2018 Leon Urbas   <leon.urbas@tu-dresden.de>
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
 *  @brief: Blinken der GPIO27 oder 47 mit 3rd party libbcm2835
 *
 *  Schaltet wahlweise GPIO 47 (Boad Status LED) oder 27 (externe
 *  LED/Linker Kit) an/aus. Die LED kann mit der Definition
 *  USE_BOARDLED ausgewaehlt werden.
 *
 *  Nutzt die 3rd Party libbcm2835 **mit manuellem Patch fuer das Pi
 *  2B!** (liegt als binaeres Archiv im Projekt bei)
 */

#include <unistd.h>
#include "bcm2835.h"


#define USE_BOARDLEDS
#ifndef USE_BOARDLEDS
  #define GPIO_LED 27
#else
  #define GPIO_LED 47
#endif

int main() {
  bcm2835_init();
  
  bcm2835_gpio_fsel(GPIO_LED, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_set(GPIO_LED);
  sleep(1);
  bcm2835_gpio_clr(GPIO_LED);

  
  bcm2835_close();
  return 0;
}
