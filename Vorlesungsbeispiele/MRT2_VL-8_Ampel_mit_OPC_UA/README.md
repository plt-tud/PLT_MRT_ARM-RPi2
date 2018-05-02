#Ampel (ohne IoT Schnittstelle)

Die Ampel mit IoT-Schnittstelle (VL-8) als Eclipse-Projekt.

Das Projekt produziert eines von zwei Binaries:
  * ampel_server:       Die Ampel (auf X86 nur ASCII)
  * ampel_controller:   Ein Steuerprogramm, dass sich mit der opc.tcp://192.168.0.240:4840 verbindet, sich als Controller registriert und beim betätigen der Ampel die Ampelphase toggelt.

Der Server sollte auf dem Raspberry Pi laufen, der Controller kann wahlweise auf einem (anderen oder dem gleichen) Pi oder einem Rechner laufen.

Das Projekt verwendet die libopen62541 als OPC UA Server und Client - zur einfacheren Kompilierung und damit man per Eclipse nur ein Binary transferieren muss, liegen sowohl open62541 wie auch Automaton als Quellcode bei und werden mit dem Projekt kompiliert. Daher müssen auch C-Compiler-Optionen für open62541 eingestellt werden.

# Einstellungen für Eclipse

Die Nachfolgenden Einstellungen sind zur Vollständigkeit dokumentiert. Einige der Einstellungen (etwa der C/C++ Dialekt) gehen beim umschalten der Toolchains verlohren.

## Auswahl des Build-Ziels

Eclipse beherrscht nur eine Main-Funktion pro Projekt, kann also nicht mehrere Binaries aus in einem Projekt produzieren. Man muss zwischen Server und Controller entscheiden.

### Um nur den Controller zu bauen

1. Rechtsklich auf die ampel_server Datei > Ressource Configurations > Exlude from build > Alle Haekchen setzen.
1. Rechtsklich auf die ampel_controller Datei > Ressource Configurations > Exlude from build > Alle Haekchen entfernen.

### Um nur den Server zu bauen

1. Rechtsklich auf die ampel_server Datei > Ressource Configurations > Exlude from build > Alle Haekchen entfernen.
1. Rechtsklich auf die ampel_controller Datei > Ressource Configurations > Exlude from build > Alle Haekchen setzen.

## Für ARM/Raspberry Pi

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Linux GCC

### Dialects
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Dialect > ISO C++11
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Dialect > ISO C99

### Preprocessor
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Preprocessor > Defined Symbols > `BUILD_RPI`

### Includes
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/src`

1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/src`

### Libraries
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `pthread`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `bcm2835_arm-eabi`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`


## Für x86/x86_64 (native)

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Linux GCC

### Dialects
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Dialect > ISO C++11
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Dialect > ISO C99

### Preprocessor
keine Optionen

### Includes
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/src`

1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/include/Automaton`
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/src`

### Libraries
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `pthread`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
