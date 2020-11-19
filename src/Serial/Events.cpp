/*
	Autore: Cavallo Gabriele
	Versione: 1.1
	Descrizione: File contenente una funzione per giudicare dei comandi seriali e avviare relativi handler


*/

#ifndef EVENTS

#define EVENTS

#include "Handlers.cpp"
#include "init.cpp"
#include "update.cpp"
#include <Arduino.h>
#include <ArduWin.h>
#include "../Time/update.cpp"
#include <TimeDate.h>

// Dato un messaggio in input lo controlla e esegue gli handler
static void SERIAL_ControlMessage(char message[], GWinList *wins, TimeDate *time) {
	// Controllo che ci sia qualcosa
	if(strlen(message) > 0){
        Serial.print("Controllo messaggio: |");
        Serial.print(message);
        Serial.println("|");
        if(strcmp(message, "$HELP$") == 0){
            handleHelpReq();
        }
        else if(strcmp(message, "$CVERSION$") == 0){
            handleCoreVersionReq();
        }
        else if(strcmp(message, "$LVERSION$") ==0 ){
            handleCoreVersionReq();
        }
        else if(strcmp(message, "$RESET$") == 0){
            handleResetReq();
        }
        else if(strcmp(message, "$CLEAR$") == 0){
            handleClear();
        }
        else if(strcmp(message, "$SWITCH-TIMEWIN$") == 0){
            SERIAL_SendMessage("Mostro finestra tempo");
            wins->draw("timesWin");
        }
        else if(strcmp(message, "$SWITCH-LIGHTWIN$") == 0){
            SERIAL_SendMessage("Mostro finestra luci");
            wins->draw("lightsWin");
        }
        else if(strcmp(message, "$SWITCH-MAINWIN$") == 0){
            SERIAL_SendMessage("Mostro finestra principale");
            wins->draw("mainWin");
        }
        else if(strcmp(message, "$GET-TIME") == 0){
            char time_b[30];
            time->getFormTime(time_b);
            SERIAL_SendMessage(time_b);
        }
        else{
            SERIAL_SendMessage("Messaggio non riconosciuto: ");
            SERIAL_SendMessage(message);
        }
	}

}

#endif // EVENTS



