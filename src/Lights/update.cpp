/*

Autore: Cavallo Gabriele
Versione: 1.1

Descrizione: Fornisce funzionalità per accendere le luci del progetto

*/
#ifndef LIGHTS_UPDATE_CPP
#define LIGHTS_UPDATE_CPP

// Header di arduino
#include <Arduino.h>

// Header per le funzioni seriali
#include "../Serial/update.cpp"

/// Effettua il test di una luce grossa fancendola blinkare 3 volte
static void LIGHTS_BenchBigLight(int pin, bool log){
    if(pin >= 0){
            // Invio le notifiche di log
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Avvio test luce grossa. Pin utilizzato: ", log);
        SERIAL_SendMessage(pin, log);
        // Avvio il ciclo
        for(int x = 0; x < 3; x++){
            // Spengo e accendo il led
            digitalWrite(pin, LOW);
            delay(1000);
            digitalWrite(pin, HIGH);
            delay(1000);
        }
        digitalWrite(pin, LOW);
        SERIAL_SendMessage("Test luce grossa terminato.", log);
    }
}

/// Accende una luce generica
static void LIGHTS_TurnOnLight(int pin){
    if(pin >= 0){
        digitalWrite(pin, HIGH);
    }
}

static void LIGHTS_TurnBigLightOn(int pin, bool log){
    SERIAL_SendMessage("Accensione luce grossa.", log);
    LIGHTS_TurnOnLight(pin);
}

static void LIGHTS_TurnReadLightOn(int pin, bool log){
    SERIAL_SendMessage("Accensione luce lettura.", log);
    LIGHTS_TurnOnLight(pin);
}

static void LIGHTS_TurnSeeLightOn(int pin, bool log){
    SERIAL_SendMessage("Accensione luce vista.", log);
    LIGHTS_TurnOnLight(pin);
}
#endif // LIGHTS_UPDATE_CPP


