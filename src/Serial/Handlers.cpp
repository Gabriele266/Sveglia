/*
	Autore: Cavallo Gabriele
	Versione: 1.1
	Descrizione: File contenente tutti gli handlers seriali per il progetto


*/

#ifndef HANDLE
#define HANDLE

// Header per le schede
#include "../Utils/ShieldUtils.cpp"
// Header di arduino
#include <Arduino.h>
// Header per il seriale
#include "../Serial/update.cpp"
// Header per le interfaccie
#include <ArduWin.h>

// Gestisce la richiesta della versione da parte del seriale
static void handleCoreVersionReq() {
	// Invio la versione
	SERIAL_ReturnToCarriage();
	SERIAL_SendMessage("Versione corrente: 1.1");
	SERIAL_ReturnToCarriage();
}

static void handleArduWinVerReq(){
    SERIAL_ReturnToCarriage();
	SERIAL_SendMessage("Versione corrente: " + String(ARDUWIN_VERSION));
	SERIAL_ReturnToCarriage();
}

static void handleResetReq() {
	hardReset();
}

// Gestisce la richiesta di aiuto da parte dell' utente
static void handleHelpReq() {
	SERIAL_ReturnToCarriage();
	SERIAL_SendMessage("Comando							Parametri						Esempio						Descrizione\n");
	SERIAL_SendMessage("$CVERSION$						Nessuno							$VERSION$					Restituisce la versione corrente del core\n");
	SERIAL_SendMessage("$LVERSION$                      Nessuno                         $LVERSION$                  Restituisce la versione della libreria ArduWin\n");
	SERIAL_SendMessage("$RESET$							Nessuno							$RESET$						Resetta da assembly il dispositivo\n");
	SERIAL_SendMessage("$HELP$							Nessuno							$HELP$						Mostra questa lista\n");
	SERIAL_SendMessage("$SWITCH-TIMEWIN$				Nessuno							$SWITCH-TIMEWIN$			Passa alla finestra tempo	\n");
	SERIAL_SendMessage("$LIST-<WINNAME>$				Nome finestra					$LIST-main$					Avvia l'elenco delle informazioni legate a quella finestra e dei suoi componenti.\n");
	SERIAL_SendMessage("$SWITCH-TIMEWIN$                Nessuno                         $SWITCH-TIMEWIN$            Passa alla finestra tempo\n");
	SERIAL_SendMessage("$SWITCH-LIGHTWIN$               Nessuno                         $SWITCH-TIMEWIN$            Passa alla finestra tempo\n");
	SERIAL_SendMessage("$SWITCH-MAINWIN$                Nessuno                         $SWITCH-MAINWIN$            Passa alla finestra principale\n");
	SERIAL_SendMessage("$GET-TIME$                      Nessuno                         $GET-TIME$                  Mostra l'orario corrente\n");

	SERIAL_ReturnToCarriage();
}

// Gestisce la pulizia del seriale richiesta dall' utente
static void handleClear() {
	// Pulisco lo schermo
	for (int x = 0; x < 30; x++) {
		SERIAL_ReturnToCarriage();
	}
}

static void handleDisplayOn() {
	//lcd.backlight();
}

// Gestisce la richiesta di mettere lo schermo su uno stato
static void handleDisplayCommand(String comm) {
	if (comm == "0") {
		//lcd.noBacklight();
	}
	else {
		//lcd.backlight();
	}
}

// gESTISCE LòA RICHIESTA DELLA DATA E DELL' ORA
static void handleTimeReq() {
	SERIAL_ReturnToCarriage();
	//SERIAL_SendMessage(curTime.getFormTime());
	SERIAL_ReturnToCarriage();
}

static void handleSwitchTime(){

	SERIAL_SendMessage("Passo alla finestra time");
	//windows.currentWindow = 2;
	//windows.showCurrentWin();
}

static void handleListReq(String win){
	/* if(win == "main" || win == "MAIN"){
		SERIAL_ListInfos(&mainWindow);
	}
	else if(win == "time" || win == "TIME"){
		SERIAL_ListInfos(&timeWindow);
	} */
}

#endif // HANDLE_KEY

