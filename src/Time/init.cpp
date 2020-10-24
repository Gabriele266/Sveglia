/*

    Autore: Cavallo Gabriele
    Versione: 1.1



*/

#ifndef TIME_INIT_CPP
#define TIME_INIT_CPP

#include "../../lib/RTClib/RTClib.h"
#include <Arduino.h>
#include "../Serial/update.cpp"

/// Effettua l'inizializzazione dell' rtc
static bool TIME_InitRtc(RTC_DS1307 *rtc, bool log){
    // Controllo che rtc non sia un puntatore nullo
    if(rtc != nullptr){
        // Esiste
        // Inizializzo l'rtc
            if(rtc->begin()){
                // RTC è stato trovato
                SERIAL_SendMessage("Inizializzazione RTC avvenuta con successo. ", log);
                // Controllo se la batteria è ancora carica
                if(rtc->isrunning()){
                    // La batteria è ancora carica
                    SERIAL_SendMessage("La batteria dell' rtc e' ancora carica.", log);
                }
                else{
                    // La batteria è scarica
                    SERIAL_SendMessage("\nAttenzione: La batteria dell' rtc e' scarica. \nQuesto porterà alla perdita della data e ora al riavvio. Cambiare la batteria.", log);
                }
            }
            else{
                // L'rtc non è stato trovato
                SERIAL_SendMessage("Errore nella inizializzazione dell' rtc. Modulo non trovato.", log);
            }
        }
}

#endif // TIME_INIT_CPP
