/*
 * Autore: Cavallo Gabriele
 * Data creazione: 15/12/2019
 * Licenza: Shareware
 * Descrizione: File di init del seriale per il progetto Sveglia Arduino
 *
 * ================================================================
 aggiorna il seriale
 * =================================================================
 */

#ifndef __SERIAL_UPDATE_CPP
#define __SERIAL_UPDATE_CPP

#include "serial.cpp"
#include "../Main/PinDefs.cpp"
#include "../Main/output_register.h"
#include <arduino.h>
#include "../../lib/ArduWin/ArduWin.h"
#include "../../lib/TimeDate/TimeDate.h"
#include "../../lib/Alarm/Alarm.h"

#define endl "\n"
#define tab "\t"

/// Invia un messaggio sul seriale senza andare a capo
static bool SERIAL_SendMessage(String message) {
	// Controllo se il messaggio � plausibile
	if (message != "" ) {
		// Controllo la lunghezza del messaggio
		if (message.length() <= __SERIAL__MAX_DATA_BUFFER__) {
			// Il messaggio � plausibile e rientra nei criteri
			if (__SERIAL_PREFERRED_INTERFACE__ == "serial") {
				// invio il messaggio
				Serial.print(message);
			}
			else if (__SERIAL_PREFERRED_INTERFACE__ == "serial2") {
				// Invio il messaggio
				Serial2.print(message);
			}
			// Restituisco true
			return true;
		}
		else {
			// Splitto il messaggio
			String tempMsg = "";
			for (int index = 0; index < message.length(); index++) {
				if (index == __SERIAL__MAX_DATA_BUFFER__) {
					// Invio la parte del messaggio e resetto la variabile
					if (__SERIAL_PREFERRED_INTERFACE__ == "serial") {
						// invio il messaggio
						Serial.print(tempMsg);
					}
					else if (__SERIAL_PREFERRED_INTERFACE__ == "serial2") {
						// Invio il messaggio
						Serial2.print(tempMsg);
					}
					tempMsg = "";
				}
				else {
					// Aggiungo il carattere del messaggio alla stringa temporanea
					tempMsg += message[index];
				}
			}
		}
	}
	else {
		return false;
	}
}

static void SERIAL_SendMessage(char *msg){
	int len = strlen(msg);
	for(int x = 0; x < len; x++){
		Serial.print(msg[x]);
	}
}

/// Invia un numero sul seriale senza andare a capo
static bool SERIAL_SendMessage(double val) {
	// Controllo se il messaggio � plausibile
	// Il messaggio � plausibile e rientra nei criteri
	if (__SERIAL_PREFERRED_INTERFACE__ == "serial") {
		// invio il messaggio
		Serial.print(val);
	}
	else if (__SERIAL_PREFERRED_INTERFACE__ == "serial2") {
		// Invio il messaggio
		Serial2.print(val);
	}
	// Restituisco true
	return true;

}



/// Invia un messaggio sul seriale specificando un sender
static bool SERIAL_SendMessageWithSender(String sender, String message) {
	// Controllo che non siano vuoti
	if (message != "" && sender != "") {
		// Unisco i due e inivio

		SERIAL_SendMessage(sender + ": " + message);
	}
	else {
		return false;
	}
}

/// Invia la sequenza di tabulazione sul seriale
static void SERIAL_Tabulate(){
    SERIAL_SendMessage("\t");
}

/// Invia un segnale di a capo sul seriale
static bool SERIAL_ReturnToCarriage() {
	if (__SERIAL_PREFERRED_INTERFACE__ == "serial") {
		// invio il messaggio
		Serial.print("\n");
	}
	else if (__SERIAL_PREFERRED_INTERFACE__ == "serial2") {
		// Invio il messaggio
		Serial2.print("\n");
	}
	return true;
}

/// Invia un messaggio di log se � possibile
static void SERIAL_SendLog(String log) {
	// Invio il messaggio
	if (__SERIAL_SEND_LOG__ && log != "") {
		// sE VOGLIO CHE VENGANO INVIATI LOG
		// Invio il messaggio
		SERIAL_SendMessage("LOG-> " + log);
	}
}

/// Invia sul seriale un array di valori
static void SERIAL_SendArray(double val[], int elems, char separator = ',') {
	// Controllo che il numero di oggetti non sia 0 o negativo
	if (elems > 0) {
		// Prendo ogni valore e lo mando sul mainstream
		for (int index = 0; index < elems; index++) {
			// Invio il valore
			SERIAL_SendMessage(val[index]);
			// Invio la stringa di separazione
			SERIAL_SendMessage(String(separator));
		}
	}
}

/// invia sul seriale un orario con data
static void SERIAL_SendMessage(TimeDate *time){
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage(time->getFormTime());
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage(time->getFormDate());
//    SERIAL_ReturnToCarriage();
}



static void SERIAL_Write(char val){
    if(__SERIAL_PREFERRED_INTERFACE__ == "serial"){
        Serial.print(val);
    }
}
/// Legge i messaggi sul seriale
static void SERIAL_UpdateInput(char *str){
  int bytes = 0;
  char curchar;
  int curbyte;
  // Ottengo il numero di caratteri disponibili
    bytes = Serial.available();
    // Controllo se � disponibile almeno un carattere
    for(int x = 0; x < bytes; x++){
      curchar = (char) Serial.read();
      if(curchar != '\n'){
        str[x] = curchar;
      }
    }
    //Serial.println(str);
}

/// Invia il messaggio solo se la condizione � vera
static void SERIAL_SendMessage(char message[], bool condition){
    if(condition){
        SERIAL_SendMessage(message);
    }
}

/// Invia il numero solo se la condizione � vera
static void SERIAL_SendMessage(int val, bool condition){
    if(condition){
        SERIAL_SendMessage(val);
    }
}

/// Invia sul seriale un valore booleano
static void SERIAL_SendBool(bool val){
    // Controllo se � vero o falso
    if(val){
        Serial.println(bool_val_true);
    }
    else{
        Serial.println(bool_val_false);
    }
    return;
}

/// Invia le informazioni legate ad un evento
static void SERIAL_SendEventInfo(GEvent *__event){
    // Invio le informazioni
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(event_happened);
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(event_display_name);
    SERIAL_SendMessage(__event->getName());
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(event_display_sender);
    SERIAL_SendMessage(__event->getSender());
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(event_display_location);
    SERIAL_SendMessage(toString(__event->getPosition()));

}

/// Invia una stringa se la condizione � vera
static void SERIAL_SendMessage(String msg, bool cond){
    if(cond){
        SERIAL_SendMessage(msg);
    }
}

/// Invia un errore
static void SERIAL_SendMessage(GError *e){
    // COntrollo che non sia nullo
    if(e != nullptr){
        // Tutto bene
        // Invio il nome
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage(e->getName());
        SERIAL_ReturnToCarriage();
        // Invio l'header
        SERIAL_SendMessage(e->getHeader());
        // Invio il sender
        SERIAL_SendMessage(error_display_sender);
        SERIAL_SendMessage(e->getSender());

        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage(error_display_level);
        // Invio la gravita'
        SERIAL_ReturnToCarriage();
        switch(e->getLevel()){
        case ErrorLevel::Fatal:
            SERIAL_SendMessage(error_display_level_fatal);
            break;
        case ErrorLevel::High:
            SERIAL_SendMessage(error_display_level_high);
            break;
        case ErrorLevel::MediumL:
            SERIAL_SendMessage(error_display_level_medium);
            break;
        case ErrorLevel::Low:
            SERIAL_SendMessage(error_display_level_low);
            break;
        case ErrorLevel::Information:
            SERIAL_SendMessage(error_display_level_information);
            break;
        }
        // Numero di volte che e' successo
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage(error_display_successes);
        SERIAL_SendMessage(e->getTimes());
    }
}

/// Invia un errore solo se la condizione e' true
static void SERIAL_SendMessage(GError *error, bool cond){
    if(cond){
        SERIAL_SendMessage(error);
    }
}

/// Funzione che invia sul seriale un parametro composto da un nome, \t un valore
static void SERIAL_SendParam(char name[], int val){
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(name);
    SERIAL_Tabulate();
    SERIAL_SendMessage(val);
}


/// Scrive una tabella con i valori di tutti i pin
static void SERIAL_WritePinnout(project_pins *pin){
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("\t Visualizzazione configurazione pin per la sveglia");
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Nome assegnato al pin");
    SERIAL_Tabulate();
    SERIAL_SendMessage("Pin assegnato");
    // Inizio
    SERIAL_SendParam(keypad_button_up, pin->up_btn_pin);
    SERIAL_SendParam(keypad_button_down, pin->down_btn_pin);
    SERIAL_SendParam(keypad_button_right, pin->right_btn_pin);
    SERIAL_SendParam(keypad_button_left, pin->left_btn_pin);
    SERIAL_SendParam(keypad_button_select, pin->select_btn_pin);
    SERIAL_SendParam(keypad_button_potenz, pin->potent_pin);
    SERIAL_SendParam(keypad_button_alarm, pin->alarm_input_pin);
    SERIAL_SendParam(keypad_button_light, pin->lights_pin);

    SERIAL_SendParam("Pin luce grossa", pin->big_light_pin);
    SERIAL_SendParam("Pin luce lettura", pin->reading_light_pin);
    SERIAL_SendParam("Pin luce vista", pin->see_light_pin);
    SERIAL_SendParam("Pin relay: ", pin->relay_pin);
    SERIAL_SendParam("Pin infrarossi", pin->ir_pin);

}

// Elenca le caratteristiche di una finestra e dei suoi componenti
static void SERIAL_ListInfos(GWindow* win) {
//	// Invio il nome della finestra
//	SERIAL_SendMessage("\nNome della finestra: ");
//	SERIAL_SendMessage(	win->getName());
//	// Vado a capo
//	SERIAL_ReturnToCarriage();
//	// Invio i tag della stessa
//	SERIAL_SendMessage("Tag della finestra: ");
//	SERIAL_SendMessage( win->getTags());
//	// A capo
//	SERIAL_ReturnToCarriage();
//	// invio il titolo
//	SERIAL_SendMessage("Titolo della finestra: " );
//	SERIAL_SendMessage( win->getTitle());
//	// Vado a capo
//	SERIAL_ReturnToCarriage();
//	// Scrivo testo e tag di ogni pulsante
//	for (int cur = 0; cur < win->getControlsNum(); cur++) {
//		// Vado a capo
//		SERIAL_ReturnToCarriage();
//		// Invio il numero del controllo
//		SERIAL_SendMessage("=====================================================================");
//		SERIAL_ReturnToCarriage();
//		SERIAL_SendMessage("Controllo " + String(cur));
//		SERIAL_ReturnToCarriage();
//		// Invio il nome del controllo
//		SERIAL_SendMessage("Nome: " + (String) (win->getControl(cur))->getName());
//		SERIAL_ReturnToCarriage();
//		// Invio il testo del componente
//		SERIAL_SendMessage("Testo: " + (String) (win->getControl(cur))->getText());
//		SERIAL_ReturnToCarriage();
//		// Invio i suoi tag
//		SERIAL_SendMessage("Tags: "  + (String) (win->getControl(cur))->getTags());
//		SERIAL_ReturnToCarriage();
//		// Invio la sua posizione
//		//SERIAL_SendMessage("Posizione: " + (String) toString((win->getControl(cur))->getLocation()));
//		SERIAL_ReturnToCarriage();
//		// Termino
//		SERIAL_SendMessage("=====================================================================");
//	}
}

/// invia le informazione di una sveglia
static void SERIAL_SendMessage(Alarm *a){
    // invio la data e l' ora in formato lineare
    // contiene l'orario formattato
    char time[15];
    // salvo la data e l'ora
    a->getAlarm()->getFormTime(time);

    // scrivo
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(serial_separator);
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Informazioni allarme: ");
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Orario avvio: ");
    SERIAL_SendMessage(time);
    SERIAL_ReturnToCarriage();

    SERIAL_SendMessage("Stato: ");
    SERIAL_SendBool(a->getState());
    SERIAL_ReturnToCarriage();

    SERIAL_SendMessage("Radio: ");
    SERIAL_SendBool(a->getRadio());
    SERIAL_ReturnToCarriage();

    SERIAL_SendMessage("Luci: ");
    SERIAL_SendBool(a->getLight());
    SERIAL_ReturnToCarriage();

    SERIAL_SendMessage("Settimanale: ");
    SERIAL_SendBool(a->getSelective());
    SERIAL_ReturnToCarriage();

    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage(serial_separator);
    SERIAL_ReturnToCarriage();
}
#endif
