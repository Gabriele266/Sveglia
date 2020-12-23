/*

Autore: Cavallo Gabriele
Versione: 1.1

Descrizione: Fornisce funzionalit� per accendere le luci del progetto

*/
#ifndef LIGHTS_UPDATE_CPP
#define LIGHTS_UPDATE_CPP

// Header di arduino
#include <Arduino.h>

/// Accende una luce generica
static void LIGHTS_TurnOnLight(int pin){
    if(pin >= 0){
        digitalWrite(pin, HIGH);
    }
}

#endif // LIGHTS_UPDATE_CPP


