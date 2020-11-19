/*

    Autore: Cavallo Gabriele
    Versione: 1.1



*/

#ifndef TIME_INIT_CPP
#define TIME_INIT_CPP

#include <RTClib.h>
#include <Arduino.h>
#include "../Serial/update.cpp"
// Header modalit� esecuzione
#include "../mode.cpp"

/// Effettua l'inizializzazione dell' rtc
static bool initRtc(RTC_DS1307 *rtc){
    // Controllo che rtc non sia un puntatore nullo
    if(rtc != nullptr){
        // Esiste
        // Inizializzo l'rtc
            if(rtc->begin()){
                // RTC � stato trovato
            #ifdef DEBUG_MODE
                SERIAL_SendMessage("Inizializzazione RTC avvenuta con successo. ");
            #endif
                // Controllo se la batteria � ancora carica
                if(rtc->isrunning()){
                    // La batteria � ancora carica
#ifdef DEBUG_MODE
                    SERIAL_SendMessage("La batteria dell' rtc e' ancora carica.", log);
#endif
                }
                else{

#ifdef DEBUG_MODE
                    // La batteria � scarica
                    SERIAL_SendMessage("\nAttenzione: La batteria dell' rtc e' scarica. \nQuesto porter� alla perdita della data e ora al riavvio. Cambiare la batteria.");
#endif
                }
            }
            else{

#ifdef DEBUG_MODE
                // L'rtc non � stato trovato
                SERIAL_SendMessage("Errore nella inizializzazione dell' rtc. Modulo non trovato.", log);
#endif
            }
        }
}

#endif // TIME_INIT_CPP
