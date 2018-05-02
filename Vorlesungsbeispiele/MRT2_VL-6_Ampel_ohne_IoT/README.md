#Ampel (ohne IoT Schnittstelle)

Die Ampel ohne IoT-Schnittstelle (VL-6) als Eclipse-Projekt. Das Projekt implementiert eine Ampel, mit multithreaded tasks, die auf Knopdruck (Sensor) die Ampelphase umschaltet. Ampel, Automat und Peripherieklassen dienen als Vorlesungsbeispiele.

Das Programm besitzt einen Preprocessor-Schalter (BUILD_PI), um die Peripherie-Funktionen des Raspberry Pis zu de-/aktivieren.

# Einstellungen für Eclipse

Die Nachfolgenden Einstellungen sind zur Vollständigkeit dokumentiert. Einige der Einstellungen (etwa der C/C++ Dialekt) gehen beim umschalten der Toolchains verlohren.

## Für ARM/Raspberry Pi

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Linux GCC

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
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `bcm2835_arm-eabi`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`


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
