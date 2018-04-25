# CMake Scaffold fuer Ampel_ohne_IoT

Sofern Eclipse zu viele Probleme bereitet, steht hier zum Testen als Alternative das CMakeFile des Projektes zur Verfügung.

## Kompilieren

1. Die CMakeFile.txt-Datei in den Ampel_ohne_IoT-Projektordner kopieren.
2. x86: Mit ´mkdir build´ einen Build-Ordner erzeugen
 2.1 Im Build-Ordner cmake ../ ausfuehren
 2.2 make ausfuehren
 2.3 Ampel mit gdb debuggen
3. arm:  Mit ´mkdir build_pi´ einen Build-Ordner erzeugen (auf Raspberry Pi)
 3.1 Im Build-Ordner cmake -DBUILD_RPI ../ ausfuehren
 3.2 make ausfuehren
 2.3 Ampel mit gdb debuggen
