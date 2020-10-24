/*
 * Autore: Cavallo Gabriele
 * Data creazione: 15/12/2019
 * Licenza: Shareware
 * Descrizione: File di init del keypad per il progetto Sveglia Arduino
 *
 * ================================================================
 inizializza il keypad
 * =================================================================
 */

 #ifndef KEYINIT
 #define KEYINIT

 #include "../../lib/Button/Button.h"
#include "../Main/PinDefs.cpp"

 // Inizializza il keypad
 static void KEYPAD_InitKeypad(Button *r, Button *l, Button *u, Button *d, Button *s, Button *alarm, Button *light, project_pins *pins){
	// Azzero la posizione del cursore
//	cursor_pos.x = 0;
//	cursor_pos.y = 0;
	// Imposto i pin dei pulsanti
	r->attachPin(pins->right_btn_pin);
	l->attachPin(pins->left_btn_pin);
	u->attachPin(pins->up_btn_pin);
	d->attachPin(pins->down_btn_pin);
	s->attachPin(pins->select_btn_pin);
    alarm->attachPin(pins->alarm_input_pin);
    light->attachPin(pins->lights_pin);

	// Inizializzo i pulsanti
	r->init();
	l->init();
	u->init();
	d->init();
	s->init();
	alarm->init();
	light->init();
 }

 #endif
