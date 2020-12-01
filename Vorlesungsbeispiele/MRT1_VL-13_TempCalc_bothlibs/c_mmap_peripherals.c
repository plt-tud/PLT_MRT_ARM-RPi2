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
 *  @brief: Recap zur Bedienung unserer Peripherie in C.
 *
 *  Schaltet wahlweise GPIO 47 (Boad Status LED) oder 27 (externe
 *  LED/Linker Kit) an/aus. Die LED kann mit der Definition
 *  USE_BOARDLED ausgewaehlt werden.
 */

//#define USE_BOARDLEDS
#ifndef USE_BOARDLEDS
#define GPIO_LED 27
#else
#define GPIO_LED 47
#endif

#include <stdio.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>

#include "BCM2836.h"
#include "bcm2835.h"

static double spiData2Temp(char *spidata) {
	/**
	 *  Egal wie wir den ADC-Wert per SPI auslesen, wir konvertieren
	 *  ihn immer auf die gleiche Weise zu Celcius...
	 */
	double temp = (spidata[1] << 8) + spidata[2]; // To 10-bit value
	temp = temp / 1024 * 3.3; 					  // To Voltage

	// Die Konvertierung ergibt sich aus dem TMP36 Datenblatt
	temp = (temp - 0.5) / 0.01;				  // Umwandlung in Celsius

	return temp;
}

static void readTempUsingLibbcm2836() {
	/**
	 *  Diese Funktion nutzt unsere C-Bibliothek, die wir in der Vorlesung
	 *  hergeleitet haben.
	 */
	uint8_t spidata[] = { 0x01, 0x80, 0x00 };

	if (!BCM2836_Open()) {
		BCM2836_SPI0_Init();

		BCM2836_SPI0_Send(3, &spidata, &spidata);

		printf("Temp %f °C\n", spiData2Temp(&spidata));
	}

	BCM2836_Close();

	return;
}

static void readTempUsingLibbcm2835() {
	/**
	 *  Diese Funktion nutzt Mike McCauleys libbcm2835; die Bibliothek
	 *  ist maechtiger, aber ihre Funktionen sind uns nicht so vertraut.
	 */
	char spidata[] = { 0x01, 0x80, 0x00 };

	if (bcm2835_init()) {
		bcm2835_spi_begin();
		bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
		bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);
		bcm2835_spi_transfern(&spidata, 3);
		bcm2835_spi_end();
	}
	bcm2835_close();

	printf("Temp %f °C\n", spiData2Temp(&spidata));
	return;
}

int main(int argc, char **argv) {
	readTempUsingLibbcm2836();
	readTempUsingLibbcm2835();
	return 0;
}
