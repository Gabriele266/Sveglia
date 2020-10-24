/*
 * BUTTON.h
 *
 *  Created on: 22 ott 2018
 *      Author: Gabriele
		Versione: 1.2018
		Descrive un pulsante in un progetto Arduino
		
 */
#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include "String.h"

#define BUTTON_PRESS_MIN 900

class Button{
public:
	// Costruttore vuoto
	Button();
	// Costruttore con un pin
	Button(unsigned int pin);
	// Funzioni per impostare un pin
	void attachPin(unsigned int val);
	// Funzione per ottenere il pin a cui è collegato
	unsigned int getPin();
	// Ottiene lo stato del pulsante
    void updateState(String *state);
	// True se il pulsante è stato premuto
	bool isPressed();
	
	void init();
	
private:
	int time;
	int state;				//DETERMINA SE IL PULSANTE è STATO PREMUTO
	bool pressed;
	bool first_pressed;			//DETERMINA SE IL PULSANTE è STATO PREMMUTO PER LA PRIVA VOLTA
	bool autoreport = true;
	int pin;
};



#endif /* BUTTON_H_ */
