/*
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
 *  @brief: ThermalLightFlat: Reacts to temperature changes by changing an LED output.
 *
 * ThermalLightFlat is a demo program using both SPI to sample an Analog Devices TMP35
 * Temperature sensor using anb MCP3008 ADC. The lowest value aquired is interpreted as
 * ambient temperature (compensates for starting the application with a warm sensor).
 *
 * The parameter DC_SENSE gives a range for PWM Modulation of the green and red led.
 * As the Tcurrent-Tambient approaches 0, the green LED will become darker and the
 * red LED brighter.
 */

#include "BCM2836.h"

//#define USE_BOARDLEDS

#ifndef USE_BOARDLEDS
  #define GPIO_GREEN  27
#else
  #define GPIO_GREEN  47
#endif

#if (GPIO_GREEN > 53)
   #error "That is not a valid LED!"
#endif

#define DC_SENSE 10

char mcp_request[3] = {0x01,0x80,0x00};
char mcp_reply[3]   = {0x00,0x00,0x00};

int main(void) {
	BCM2836_Open();
	BCM2836_GPIO_PinSelFun(GPIO_GREEN, BCM2836_GPFSEL_OUTPUT);
	BCM2836_SPI0_Init();

	unsigned int pwmcount 		    = 0;
	unsigned int ambientTemperature = 1024;
	while (1) {
		BCM2836_SPI0_Send(3, &mcp_request, &mcp_reply);

		pwmcount++;
		if (pwmcount>DC_SENSE) {
			pwmcount=0;
		}

		unsigned currentTemperature = mcp_reply[1] << 8 | mcp_reply[2];
		if (ambientTemperature > currentTemperature ) {
			ambientTemperature = currentTemperature;
		}

		if (currentTemperature - ambientTemperature > DC_SENSE) {
			BCM2836_GPIO_PinClr(GPIO_GREEN);
		}
		else {
			BCM2836_GPIO_PinSet(GPIO_GREEN);
		}
	}
	BCM2836_Close();
	return 0;
}
