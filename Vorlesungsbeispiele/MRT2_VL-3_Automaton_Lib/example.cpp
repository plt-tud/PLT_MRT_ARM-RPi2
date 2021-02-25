/*
 * example.cpp
 *
 *  Created on: 16.04.2018
 *      Author: mrt
 */

#include <unistd.h>
#include <iostream>
#include <list>
#include <map>


#include "Automaton.h"
#include "bcm2835.h"

using namespace std;

// Remove definition when building on x86!!
#define BUILD_RPI
#define RPI_GPIO_GREEN  5
#define RPI_GPIO_YELLOW 4
#define RPI_GPIO_RED    2

static void behavior_red(const AutomatonElement& ae, const string& ActionID)
{
	cout << ae << ":" << ActionID << endl;

	#ifdef BUILD_RPI // Sehr sehr sehr schlechter, nicht wartbarer Platzhalter um IOs zu testen
      bcm2835_gpio_set(RPI_GPIO_RED);
	  bcm2835_gpio_clr(RPI_GPIO_GREEN);
	#endif
}

static void behavior_green(const AutomatonElement& ae, const string& ActionID)
{
	cout << ae << ":" << ActionID << endl;
	#ifdef BUILD_RPI // Sehr sehr sehr schlechter, nicht wartbarer Platzhalter um IOs zu testen
      bcm2835_gpio_set(RPI_GPIO_GREEN);
	  bcm2835_gpio_clr(RPI_GPIO_RED);
	#endif
}

static void piInit() {
#ifndef BUILD_RPI
	return;
#else
	// Wird nur kompiliert, wenn wir ein Pi haben und fuer ARM bauen
	bcm2835_init();
	bcm2835_gpio_fsel(RPI_GPIO_RED,    BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_GPIO_YELLOW, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_GPIO_GREEN,  BCM2835_GPIO_FSEL_OUTP);
#endif
}

static void piClose() {
#ifndef BUILD_RPI
	return;
#else
	// Wird nur kompiliert, wenn wir ein Pi haben und fuer ARM bauen
	bcm2835_close();
#endif
}

int main()
{
	piInit();

	std::map<std::string, State*> states;

	states["red"]   = new State("red",    behavior_red,  defaultBehavior,  defaultBehavior, nullptr);
	states["green"] = new State("green",  behavior_green,  defaultBehavior,  defaultBehavior, nullptr);

	std::list<Transition*> transitions;

	transitions.push_back(new Transition(*states["red"],  *states["green"], defaultGuard, defaultBehavior, nullptr));
	transitions.push_back(new Transition(*states["green"],*states["red"],   defaultGuard, defaultBehavior, nullptr));

	Automaton  stateMachine(*states["red"], transitions);

#ifndef BUILD_RPI
	while (true)
	{
		stateMachine.run();
		usleep(1000*500);
	}
#else
	for (int i=0; i<100; i++ )
	{
		stateMachine.run();
		usleep(1000*500);
	}
#endif

	cout << "bye" << endl;

	piClose();
	return 0;
}
