/*
    Autore: Cavallo Gabriele
    Versione: Gestisce l'inizializzazione del modulo del tempo
*/

#ifndef TIME_INIT_CPP
#define TIME_INIT_CPP

#include <RTClib.h>
#include <Arduino.h>

/// Effettua l'inizializzazione dell' rtc
static bool initRtc(RTC_DS1307 *rtc){
    // Controllo che rtc non sia un puntatore nullo
    if(rtc != nullptr){
        // Esiste
        // Inizializzo l'rtc
        if(rtc->begin()){
            // RTC è stato trovato
            // Controllo se la batteria è ancora carica
            if(rtc->isrunning()){
                // La batteria è ancora carica
                return true;
            }
        }
    }
    return false;
}

#endif // TIME_INIT_CPP
