/*
        Autore: Cavallo Gabriele
        Versione: 1.1
        Contiene le funzioni per aggiornare lo stato dei pulsanti

*/
#ifndef UPDATE_KEY
#define UPDATE_KEY
// Sorgente con le implemetazioni degli handlers
#include "handlers.cpp"
// Sorgente con le funzioni per le stringhe
#include "../Utils/StringUtils.cpp"
// Sorgente con le funzioni per il seriale
#include "../Serial/update.cpp"
// Sorgente con le funzioni per la gestione dei pulsanti
#include "../../lib/Button/Button.h"

/// Controlla lo stato dei vari pulsanti e agisce di conseguenza
static void KEYPAD_CheckButtonsPressed(location *loc, GWindow *win, Button *r, Button *l, Button *u, Button *d, Button *s, Button *alarm, Button *light, bool show_event){
	// Controllo il pulsante up
	if(u->isPressed()){
		// Notifico
		SERIAL_SendMessage("Premuto pulsante up.");
		SERIAL_ReturnToCarriage();
		// Avvio l'handler
		handleUp(loc);
	}
	else if(d->isPressed()){
        // Notifico
		SERIAL_SendMessage("Premuto pulsante down.");
		SERIAL_ReturnToCarriage();
		handleDown(loc);
	}
	else if(l->isPressed()){
	    // Notifico
		SERIAL_SendMessage("Premuto pulsante left.");
		SERIAL_ReturnToCarriage();
		handleLeft(loc);
	}
	else if(r->isPressed()){
	    // Notifico
		SERIAL_SendMessage("Premuto pulsante right.");
		SERIAL_ReturnToCarriage();
		handleRight(loc);
	}
	else if(s->isPressed()){
	    // Notifico
		SERIAL_SendMessage("Premuto pulsante select.");
		SERIAL_ReturnToCarriage();
		handleSelect(loc, win);
	}
	else if(alarm->isPressed()){
        // Notifico
		SERIAL_SendMessage("Premuto pulsante alarm_in.");
		SERIAL_ReturnToCarriage();
	}
}

static void KEYPAD_WriteButtonState(Button *r, Button *l, Button *u, Button *d, Button *s, Button *alarm, Button *light){
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Inizio lista stato pulsanti: ");
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Nome pulsante\tValore lettura pin\tPin");

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("right\t");
    SERIAL_SendMessage(convertAnalogToString(r->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(r->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("left\t");
    SERIAL_SendMessage(convertAnalogToString(l->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(l->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("up\t");
    SERIAL_SendMessage(convertAnalogToString(u->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(u->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("down\t");
    SERIAL_SendMessage(convertAnalogToString(d->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(d->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("select\t");
    SERIAL_SendMessage(convertAnalogToString(s->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(s->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("alarm\t");
    SERIAL_SendMessage(convertAnalogToString(alarm->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(alarm->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("light\t");
    SERIAL_SendMessage(convertAnalogToString(light->getPin()));
    SERIAL_Tabulate();
    SERIAL_SendMessage(analogRead(light->getPin()));
    SERIAL_ReturnToCarriage();

    SERIAL_SendMessage("Fine");
    SERIAL_ReturnToCarriage();
}


#endif

