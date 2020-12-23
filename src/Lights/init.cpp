#ifndef LIGHTS_INIT
#define LIGHTS_INIT
/*
    Autore: Cavallo Gabriele
    Fornisce funzioni per inizializzare le luci
*/
// Header di Arduino
#include <Arduino.h>

/// Inizializza una nuova luce grossa e da un output se l'utente lo vuole
static void initBigLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, HIGH);
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void initReadLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void initSeeLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
}

#endif // LIGHTS_INIT