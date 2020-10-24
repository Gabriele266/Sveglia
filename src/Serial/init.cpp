/*
 * Autore: Cavallo Gabriele
 * Data creazione: 15/12/2019
 * Licenza: Shareware
 * Descrizione: File di init del seriale per il progetto Sveglia Arduino
 *
 * ================================================================
 inizializza il seriale
 * =================================================================
 */

#ifndef __SERIAL_INIT_CPP
#define __SERIAL_INIT_CPP

#include "serial.cpp"
#include <arduino.h>

// Inizializza il seriale
static bool SERIAL_InitSerial() {
	// Inizializzo il seriale corretto
	if (__SERIAL_PREFERRED_INTERFACE__ == "serial") {
		// Inizializzo il seriale con il giusto baudrate
		Serial.begin(__SERIAL_PREFERR_BAUDRATE__);
		return true;
	}
	else if (__SERIAL_PREFERRED_INTERFACE__ == "serial2") {
		// Inizializzo il seriale con il giusto baudrate
		Serial2.begin(__SERIAL_PREFERR_BAUDRATE__);
		return true;
	}
	else {
		return false;
	}
}

#endif
