#ifndef HANDLE_KEY
#define HANDLE_KEY

#include "../../lib/ArduWin/ArduWin.h"
#include "../Serial/update.cpp"
#include "../mode.cpp"

static void handleUp(location *loc){
	// Incremento la y
	loc->y -= 1;
}

static void handleDown(location *loc){
	loc->y += 1;
}

static void handleLeft(location *loc){
	loc->x -= 1;
}

static void handleRight(location *loc){
	loc->x += 1;
}

static void handleSelect(location *loc, GWindow *win){
    // controllo
    if(win != nullptr){
#ifdef DEBUG_MODE
        SERIAL_SendMessage(endl "Aggiorno controlli" endl);
        SERIAL_SendMessage(endl "Finestra: ");
        SERIAL_SendMessage(win->getName());
        SERIAL_ReturnToCarriage();
#endif
        win->updateControls(getLocationByPointer(loc));
    }
    else{
        SERIAL_SendMessage("Passata finestra per il controllo pressione select non valida. ");
    }
}

#endif
