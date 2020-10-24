/*
 * BUTTON.cpp
 *
 *  Created on: 22 ott 2018
 *      Author: Gabriele
 */
#ifndef BUTTON_CPP
#define BUTTON_CPP

#include "Button.h"

void Button::updateState(String *state){
	int s;
	s = analogRead(pin);
	*state = String(s);
	
	if(s > 1000){
		//determina se il pulsante � stato premuto
		pressed = true;
		
		time ++;
		if (time == 1){
			first_pressed = true;
		}
		if (time == 2){
			first_pressed = false;
			time = 0;
		}

	}
	else{
		pressed = false;
	}
	if (autoreport){
		Serial.println(s);
	}

}

Button::Button(){
	
}

Button::Button(unsigned int val){
	pin = val;
}

void Button::init(){
	pinMode(pin, INPUT);
	analogWrite(pin, 0);
}

bool Button::isPressed() {
	// Controllo che il pin sia assegnato
	if (pin > 0) {
		// Leggo lo stato del pin
		int stat = analogRead(pin);
		// Controllo
		if (stat > BUTTON_PRESS_MIN) {
			// Il pulsante � stato premuto
			return true;
		}
		else {
			return false;
		}
	}
}

void Button::attachPin(unsigned int val){
	pin = val;
}

unsigned int Button::getPin(){
	return pin;
}

#endif