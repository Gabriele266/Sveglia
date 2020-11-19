#ifndef LIGHTS_INIT
#define LIGHTS_INIT

/*
    Autore: Cavallo Gabriele
    Fornisce funzioni per inizializzare le luci

*/
// Header per il seriale
#include "../Serial/update.cpp"
// Header modalità di esecuzione
#include "../mode.cpp"

/// Inizializza una nuova luce grossa e da un output se l'utente lo vuole
static void initBigLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
        // Mando il log
#ifdef DEBUG_MODE
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce grossa sul pin: ");
        // Scrivo il pin
        SERIAL_SendMessage(pin);
        SERIAL_ReturnToCarriage();
#endif
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, HIGH);
    }
    else{
#ifdef DEBUG_MODE
        // Do errore
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce grossa: \n Il pin");
        SERIAL_SendMessage(pin);
        SERIAL_SendMessage(" non esiste.");
#endif
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void initReadLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
        // Mando il log
#ifdef DEBUG_MODE
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce da lettura sul pin: ");
        // Scrivo il pin
        SERIAL_SendMessage(pin);
        SERIAL_ReturnToCarriage();
#endif
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
    else{
        // Do errore
#ifdef DEBUG_MODE
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce da lettura: \n Il pin");
        SERIAL_SendMessage(pin);
        SERIAL_SendMessage(" non esiste.");
#endif
    }
}

/// Inizializza una luce da lettura su un pin e invia il log
static void initSeeLight(int pin){
    // Controllo che il pin esista
    if(pin >= 0){
#ifdef DEBUG_MODE
        // Mando il log
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Inizializzo luce da vista sul pin: ");
        // Scrivo il pin
        SERIAL_SendMessage(pin);
        SERIAL_ReturnToCarriage();
#endif
        // Inizializzo
        pinMode(pin, OUTPUT);
        // Azzeroil valore sul piede
        digitalWrite(pin, LOW);
    }
    else{
        // Do errore
#ifdef DEBUG_MODE
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("ERRORE durente l'inizializzazione della luce da vista: \n Il pin");
        SERIAL_SendMessage(pin);
        SERIAL_SendMessage(" non esiste.");
#endif
    }
}

#endif // LIGHTS_INIT


