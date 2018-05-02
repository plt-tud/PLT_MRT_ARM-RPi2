# CMake Scaffold

Das CMake Scaffold 
für die IoT Ampel (VL-8)
ermöglicht das Eclipse-unabhängige Kompilieren des Vorlesungsbeispiels. CMake ersetzt in dem Fall gänzlich Eclipse.

Das Nachfolgende Vorgehen ist für den Fall vorgesehen, dass Sie das Programm oder Komponenten des Programms "as is" verwenden möchten, ohne es debuggen zu wollen.

## Vorgehen 

Alle Verzeichnisse sind relativ zum Git-Repository angegeben.

  1. Navigieren Sie in das Projektverzeichnis  
  `$ cd Vorlesungsbeispiele/MRT2_VL-8_Ampel_mit_OPC_UA`
  1.  Kopieren Sie die CMakeLists.txt-Datei in das Verzeichnis   
  `$ cp Vorlesungsbeispiele/MRT2_VL-8_Ampel_mit_OPC_UA_CMakeScaffold/CMakeLists.txt ./`
  1. Erstellen Sie einen build-Ordner und navigieren Sie in den Ordner  
  `$ mkdir build && cd build`
  1. Erstellen Sie das Projekt
     1. Falls Sie das Projekt *nicht* auf dem Raspberry Pi bauen
    ` $ cmake ../`
     1. Falls Sie das Projekt auf dem Raspberry Pi bauen
     `$ cmake -DBUILD_RPI=On ../`
  1. Kompilieren Sie das Projekt
    `$ make`

Sie erhalten zwei Ausführbare Dateien:

  * ampel_server:       Die Ampel (auf X86 nur ASCII)
  * ampel_controller:   Ein Steuerprogramm, dass sich mit der opc.tcp://192.168.0.240:4840 verbindet, sich als Controller registriert und beim betätigen der Ampel die Ampelphase toggelt.
