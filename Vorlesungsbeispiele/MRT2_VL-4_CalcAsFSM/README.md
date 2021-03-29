# CalcAsFSM
CalcAsFSM implementiert den in Vorlesung 4 vorgestellten Taschenrechner als Zustandsmaschine. Das Projekt benötigt die Automaton_Lib Bibliothek.

CalcAsFSM ist so voreingestellt, dass die "automaton" Bibliothek aus MRT2_VL-3_Automaton_Lib automatisch eingebunden wird. Dazu muss sich das Projekt MRT2_VL-3_Automaton_Lib allerdings im Workspace befinden und bereits für die gewünschte Zielplatform kompiliert sein.

## CalcAsFSM in der Virtual Machine ausführen (x86)

### "automaton" Bibliothek für x86 konfigurieren

1. Beispielprojekt MRT2_VL-3_Automaton_Lib aus dem Repository importieren.
2. Die Build Configuration auf "Debug (x86)" umschalten: Neben dem Build Symbol (Hammer Icon) ist eine Drop-Down-Liste, in der die gewünschte Build Configuration ausgewählt werden kann. Mit Auswahl eines Eintrags kompiliert Eclipse die Bibliothek für die entsprechend Zielplatform automatisch.
3. Die kompilierte Bibliothek befindet sich unter "Debug (x86)/libautomaton.a". Unter Umständen muss zuerst der Project Explorer aktualisiert werden (Rechtsklick >> Refresh (F5)).

### CalsAsFSM unter x86 ausführen

1. Im Debug Configurations Dialog (Dropdown neben Debug Button >> Debug Configurations...) befindet sich mit Import von CalcAsFSM unter "C/C++ Application" der Eintrag "MRT2_VL-4_CalcAsFSM Debug (x86)". 
2. "MRT2_VL-4_CalcAsFSM_reduziert Debug (x86)" wählen und mit "Debug..." ausführen.

## CalcAsFSM auf dem Raspberry Pi ausführen (arm)

### "automaton" Bibliothek für arm konfigurieren

1. Beispielprojekt MRT2_VL-3_Automaton_Lib aus dem Repository importieren.
2. Die Build Configuration auf "Debug (arm)" umschalten: Neben dem Build Symbol (Hammer Icon) ist eine Drop-Down-Liste, in der die gewünschte Build Configuration ausgewählt werden kann. Mit Auswahl eines Eintrags kompiliert Eclipse die Bibliothek für die entsprechend Zielplatform automatisch.
3. Die kompilierte Bibliothek befindet sich unter "Debug (arm)/libautomaton.a". Unter Umständen muss zuerst der Project Explorer aktualisiert werden (Rechtsklick >> Refresh (F5)).

### CalsAsFSM unter arm ausführen

1. Im Debug Configurations Dialog (Dropdown neben Debug Button >> Debug Configurations...) befindet sich mit Import von CalcAsFSM unter "C/C++ Remote Application" der Eintrag "MRT2_VL-4_CalcAsFSM Debug (arm)". 
2. "MRT2_VL-4_CalcAsFSM_reduziert Debug (arm)" wählen und mit "Debug..." ausführen.

## FAQ

1. **Die Konsole zeigt "/usr/bin/ld: cannot find -lautomaton":** Das Projekt "MRT2_VL-3_Automaton_Lib" ist entweder noch nicht importiert oder die Bibliothek ist noch nicht für die gewünschte Zielplatform kompiliert worden. Die Zielplatform kann mit dem Dropdown neben dem Hammer Symbol geändert werden.
