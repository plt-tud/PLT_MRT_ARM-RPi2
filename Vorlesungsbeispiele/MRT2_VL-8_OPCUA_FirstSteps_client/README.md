# Erster OPC UA Client

Dieses Program erstellt einen neuen Client mit dem open62541 Stack und verbindet sich mit unserem Server auf dem Pi (der Server darf die Ampel oder das Erste-Schritte-Beispiel sein).

Der Client macht nichts, außer mit dem Stack verbunden zu bleiben. Er dient als erster Schritt für weitere Interaktionen, wenn wir einmal verbunden sind.

Der CLient kann wahlweise local oder auf dem Pi laufen.

**NOTE:** This project only contains the used API header and sources. For the complete project, please check out the `Ampel_mit_IoT`-project.

# Projeteinstellungen für  ARM/Raspberry Pi

Per Rechtsklick auch das Projekt unter dem Menüpunkt "Eigenschaften" sollten die nachfolgenden Einstellungen getroffen werden.

### Toolchain

1. Project Properties >  C/C++ Build > Tool Chain Editor > (DropDown) Cross GCC

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
