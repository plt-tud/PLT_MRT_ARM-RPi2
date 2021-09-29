# OPC UA Server Firststeps

Dieses Programm startet den open62541 OPC UA Server auf dem Raspberry Pi. Der Server enthält keine
Variablen oder Interaktionsmöglichkeiten - er dient als erster Schritt, um sich mit UA Expert und dem
nachfolgenden Client-Beispiel mit dem Pi verbinden zu können.

Das Programm kann wahlweise auf dem Pi oder in der VM laufen. Dafür muss die Zieladresse in OPCUA_FirstSteps_client.cpp im Client Projekt aber entsprechend angepasst werden. Die Projekte sind standardmäßig so eingestellt, dass der Server auf dem Pi läuft.

**NOTE:** This project only contains the used API header and sources. For the complete project, please check out the `Ampel_mit_IoT`-project.

# Projeteinstellungen für  ARM/Raspberry Pi

Per Rechtsklick auch das Projekt unter dem Menüpunkt "Eigenschaften" sollten die nachfolgenden Einstellungen getroffen werden.

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Cross GCC

### Cross Compiler Settings
1. Project Properties >  C/C++ Build > Tool Chain Editor > Settings > Cross Settings 
  1. Prefix: arm-linux-gnueabi-hf
  1. Path: <leer lassen> (Wird durch die run-eclipse Skripte und in der VM automatisch ermittelt) 

### Dialects
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Dialect > ISO C++11
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Dialect > ISO C99

### Includes
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Compiler > Includes > `${workspce_loc:}${ProjName}/src`

1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/include`
1. Project Properties >  C/C++ Build > Settings > GCC C Compiler > Includes > `${workspce_loc:}${ProjName}/src`

### Libraries
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `pthread`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `bcm2835`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Libraries (-l)> `rt`
1. Project Properties >  C/C++ Build > Settings > GCC C++ Linker > Libraries > Library Search Path (-L) > `${workspce_loc:}${ProjName}/lib`
