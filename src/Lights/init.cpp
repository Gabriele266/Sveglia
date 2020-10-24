#ifndef LIGHTS_INIT
#define LIGHTS_INIT

/*
    Autore: Cavallo Gabriele
    Fornisce funzioni per inizializzare le luci

*/
// Header per il seriale
#include "../Serial/update.cpp"

/// Inizializza una nuova luce grossa e da un output se l'utente lo vuole
static void LIGHTS_InitBigLight(int pin, bool log){
    // Controllo che il pin esista
    if(pin >= 0){
        // Mando il log
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce grossa sul pin: ", log);
        // Scrivo il pin
        SERIAL_SendMessage(pin, log);
        SERIAL_ReturnToCarriage();
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, HIGH);
    }
    else{
        // Do errore
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce grossa: \n Il pin", log);
        SERIAL_SendMessage(pin, log);
        SERIAL_SendMessage(" non esiste.");
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void LIGHTS_InitReadingLight(int pin, bool log){
    // Controllo che il pin esista
    if(pin >= 0){
        // Mando il log
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce da lettura sul pin: ", log);
        // Scrivo il pin
        SERIAL_SendMessage(pin, log);
        SERIAL_ReturnToCarriage();
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
    else{
        // Do errore
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce da lettura: \n Il pin", log);
        SERIAL_SendMessage(pin, log);
        SERIAL_SendMessage(" non esiste.");
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void LIGHTS_InitSeeLight(int pin, bool log){
    // Controllo che il pin esista
    if(pin >= 0){
        // Mando il log
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce da vista sul pin: ", log);
        // Scrivo il pin
        SERIAL_SendMessage(pin, log);
        SERIAL_ReturnToCarriage();
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
    else{
        // Do errore
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce da vista: \n Il pin", log);
        SERIAL_SendMessage(pin, log);
        SERIAL_SendMessage(" non esiste.");
    }
}

#endif // LIGHTS_INIT


