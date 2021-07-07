#Ampel (ohne IoT Schnittstelle)

Die Ampel mit IoT-Schnittstelle (VL-8) als Eclipse-Projekt.

Das Projekt produziert den `ampel_server`, der als Ampel durch den `ampel_controller` ferngesteuert wird. Der Zugriff auf die Ampel passiert durch die IP-Adresse des Gerätes, auf dem der `ampel_server` läuft: Sollte die Ampel auf dem Raspberry Pi und die Steuerung in der VM laufen, so ist die Ampel über die Adresse "192.168.0.240" erreichbar. Sollte beides, Steuerung und Ampel, auf dem Raspberry Pi laufen, so ist die Ampel zusätzlich auch über "127.0.0.1" (localhost) erreichbar.  
 
Das Projekt verwendet die libopen62541 als OPC UA Server und Client - zur einfacheren Kompilierung und damit man per Eclipse nur ein Binary transferieren muss, liegen sowohl open62541 wie auch Automaton als Quellcode bei und werden mit dem Projekt kompiliert. Daher müssen auch C-Compiler-Optionen für open62541 eingestellt werden.

**NOTE:** The src and include folder contain the entire API Code for the traffic light. If you intend to turn this API into a library... use this project!

# Projekteinstellungen für  ARM/Raspberry Pi

Per Rechtsklick auch das Projekt unter dem Menüpunkt "Eigenschaften" sollten die nachfolgenden Einstellungen getroffen werden.

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Cross GCC

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
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `bcm2835`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `rt`
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
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `rt`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
