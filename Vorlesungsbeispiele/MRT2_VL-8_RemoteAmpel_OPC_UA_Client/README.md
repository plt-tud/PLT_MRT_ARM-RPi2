#RemoteAmpel-Controller

Der IoT Ampel-Controller (VL-8) als Eclipse-Projekt.

Der Ampel-Controller ist ein OPC UA Client, der als API lokal die gleichen Schnittstellen anbietet wie unsere Ampel. Der Client verbindet sich mit einer IoT-Ampel per OPC UA und erlaubt so die "Fernsteuerung".

Der Raspberry Pi ist standardmäßig über die Addresse "192.168.0.240" erreichbar. Sollten Steurung und Ampel auf der selben Maschine laufen, so ist die Ampel auch über "127.0.0.1" (localhost) erreichbar. Die Zieladresse kann in ampel_controller.cpp geändert werden.

Das Programm erfüllt die selbe Funktion wie dies Vorlesungsbeispiele vorangegangener Vorlesungen: Es prüft, ob der Sensor ausgelöst wurde und wechselt die Ampelphasen von Rot auf Grün und zurück. 

**NOTE:** This project only contains the used API header and sources. For the complete project, please check out the `Ampel_mit_IoT`-project.

# Einstellungen für Eclipse

Das Programm ist in erster Linie als PC-seitiger Client vorgesehen. 
Es kann Cross-kompiliert werden und vom Raspberry Pi as agieren. Hierfür können die gleichen Einstellungen wie für den Server benutzt werden (siehe Einstellungen im Projekt `Ampel_mit_IoT`).

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
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `rt`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
