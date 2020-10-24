/*
	Autore: Cavallo Gabriele
	Versione: 1.1

	Insieme di funzioni utili per il controllo dello schermo
	Il seguente codice è aperto a modifiche
*/
#include "../../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

void UTILS_RemoveBackLight(LiquidCrystal_I2C *surf) {
	surf->noBacklight();
}

void UTILS_ResetCursor(LiquidCrystal_I2C* surf) {
	surf->setCursor(0, 0);
}



