/*
* Autore: Cavallo Gabriele
* Versione: 1.1
* Descrizione: Fornisce funzioni per la gestione delle memorie (sd, eeprom)
*/

#ifndef STORAGE_INIT_CPP
#define STORAGE_INIT_CPP

// Header di Arduino
#include <Arduino.h>
// Libreria per l'utilizzo delle schede sd
#include <SD.h>
// Libreria per la comunicazione spi
#include <SPI.h>
// Header per i pin
#include "../Main/PinDefs.cpp"
#include "../Utils/StringUtils.cpp"

/// Effettua l'inizializzazione della scheda sd
static bool initSd(unsigned int cs_pin){
    // Controllo l'avvio
    if(!SD.begin(cs_pin)){
        return false;
    }
    else{
        return true;
    }
}


#endif // STORAGE_INIT_CPP
