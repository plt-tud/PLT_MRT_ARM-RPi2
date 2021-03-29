# Automaton_Lib
Automaton_Lib kompiliert das Beispiel MRT2_VL-3_Automaton zu einer statischen Bibliothek. Das Projekt ist schon so voreingstellt, dass es für die Platformen x86 und arm kompiliert werden kann.

### "automaton" Bibliothek für x86 kompilieren

1. Beispielprojekt MRT2_VL-3_Automaton_Lib aus dem Repository importieren.
2. Die Build Configuration auf "Debug (x86)" umschalten: Neben dem Build Symbol (Hammer Icon) ist eine Drop-Down-Liste, in der die gewünschte Build Configuration ausgewählt werden kann. Mit Auswahl eines Eintrags kompiliert Eclipse die Bibliothek für die entsprechend Zielplatform automatisch.
3. Die kompilierte Bibliothek befindet sich unter "Debug (x86)/libautomaton.a". Unter Umständen muss zuerst der Project Explorer aktualisiert werden (Rechtsklick >> Refresh (F5)), um die Datei sichtbar zu machen.

### "automaton" Bibliothek für arm kompilieren

1. Beispielprojekt MRT2_VL-3_Automaton_Lib aus dem Repository importieren.
2. Die Build Configuration auf "Debug (arm)" umschalten: Neben dem Build Symbol (Hammer Icon) ist eine Drop-Down-Liste, in der die gewünschte Build Configuration ausgewählt werden kann. Mit Auswahl eines Eintrags kompiliert Eclipse die Bibliothek für die entsprechend Zielplatform automatisch.
3. Die kompilierte Bibliothek befindet sich unter "Debug (arm)/libautomaton.a". Unter Umständen muss zuerst der Project Explorer aktualisiert werden (Rechtsklick >> Refresh (F5)), um die Datei sichtbar zu machen.
