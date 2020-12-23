/*
* Autore: Cavallo Gabriele
* Versione: 1.1
* Descrizione: Insieme di funzionalit� utili per le stringhe
* Progetto: Sveglia Arduino
*
*/

#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

// Header di Arduino
#include <Arduino.h>

/// Converte una stringa in intero
static int stringToInt(char *source){
    // Creo una stringa arduino
    String str = source;
    // Restituisco il valore intero
    return (int) str.toInt();
}

/// Converte il valore intero value in una stringa
static void intToString(int value, char *output){
    String r = String(value);
    // Copio la stringa ottenuta nella stringa di output
    strcpy(output, r.c_str());
}

#endif // STRING_UTILS_CPP
