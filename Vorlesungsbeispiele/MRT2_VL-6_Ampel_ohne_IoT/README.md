#Ampel (ohne IoT Schnittstelle)

Die Ampel ohne IoT-Schnittstelle (VL-6) als Eclipse-Projekt. Das Projekt implementiert eine Ampel, mit multithreaded tasks, die auf Knopdruck (Sensor) die Ampelphase umschaltet. Ampel, Automat und Peripherieklassen dienen als Vorlesungsbeispiele.

Das Programm besitzt einen Preprocessor-Schalter (BUILD_PI), um die Peripherie-Funktionen des Raspberry Pis zu de-/aktivieren.

Die GPIO Belegung für Lampen und Sensor wird in main.cpp definiert. Die standardmäßige Belegung ist in folgender Tabelle aufgelistet:

| Funktion     | BCM Pin    | Board Pin  |
| ------------ | ---------- | ---------- |
| Sensor       | 24         | 18         |
| Grün         | 17         | 11         |
| Gelb         | 27         | 13         |
| Rot          | 22         | 15         |


# Einstellungen für Eclipse

Die Nachfolgenden Einstellungen sind zur Vollständigkeit dokumentiert. Einige der Einstellungen (etwa der C/C++ Dialekt) gehen beim umschalten der Toolchains verlohren.

## Für ARM/Raspberry Pi

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Cross GCC

### Cross Compiler Settings
1. Project Properties >  C/C++ Build > Tool Chain Editor > Settings > Cross Settings 
  1. Prefix: arm-linux-gnueabi-hf
  1. Path: <leer lassen> (Wird durch die run-eclipse Skripte und in der VM automatisch ermittelt) 
      
### Dialects
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Dialect > ISO C++11

### Preprocessor
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Preprocessor > Defined Symbols > `BUILD_RPI`

### Includes
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/src`

### Libraries
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `pthread`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `bcm2835`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker
   1. Für die Library bcm2835 statisch zu linken, fügen Sie die Option -static im command line pattern: ${COMMAND} -static ${FLAGS} ${OUTPUT_FLAG} ${OUTPUT_PREFIX}${OUTPUT} ${INPUTS}

## Für x86/x86_64 (native)

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Linux GCC

### Dialects
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Dialect > ISO C++11

### Preprocessor
keine Optionen

### Includes
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/src`


### Libraries
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `pthread`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
