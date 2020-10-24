/*
=================================================
QUESTO FILE E' PARTE DEL PROGETTO SVEGLIA ARDUINO.
NON E' OPENSOURCE QUINDI E' ILLEGALE MODIFICARE IL CODICE
AUTORE: CAVALLO GABRIELE
IL FILE E TUTTO IL PROGETTO SONO PROTETTI DA COPYRIGHT.
E' INOLTRE ILLEGALE COPIARE LE IDEE E LE METODOLOGIE DI RISOLUZIONE DEI PROBLEMI
PER ULTERIORI INFORMAZIONI RIVOLGETEVI A GABRIELE CAVALLO:
3317375441
=================================================

Descrizione: contiene le funzioni per l'interfaccia seriale


*/

#ifndef SERFUN_CPP
#define SERFUN_CPP

#include <Arduino.h>
#include "../main/PinDefs.cpp"


// Avvia il seriale con il computer
static bool startCompSer(){
  // Avvio il seriale con il baudrate di default
  Serial.begin(115200);
  // Scrivo i messaggi di base
  if(Serial.availableForWrite() > 0){
    Serial.println(F("Sveglia Arduino di GAbriele CAvallo. Versione: 1.1"));
    Serial.println(F("Avvio in corso..."));
    return true;
  }
  else{
    return false;
  }
}

// Funzione per inviare un messaggio sul seriale per la debug mode
static bool sendDebugNotify(bool isDebug, String text){
  // Controllo se siamo nella debug mode
  if(isDebug){
    // Siamo in modalità di debug
    Serial.println(text);
  }
  else{
    // Non siamo nella modalità di debug
  }
}
#endif
