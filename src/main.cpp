/**
 * \file CoreMain.cpp
 * \author   Cavallo Gabriele
 * \brief   File principale del progetto sveglia arduino. Viene chiamato dallo sketch dell' ide integrato
 */
#ifndef CORE_MAIN_CPP
#define CORE_MAIN_CPP

// Inclusione header
// Sorgente con le modalità di esecuzione
#include "mode.cpp"
// sorgente con la definizione degli oggetti per il progetto
#include "Serial/Update.cpp"
// Libreria per la gestione dei pulsanti hardware
#include <ArduWin.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
// Libreria per la comunicazione spi
#include <SPI.h>
// Header di Arduino
#include <Arduino.h>
// Header per il tempo
#include <TimeDate.h>
// Libreria RTC_DS1307
#include <RTClib.h>
// sorgente con funzioni per inizializzare l'interfaccia e generare i suoi componenti
#include "Interface/Init.cpp"
// Sorgente conle funzioni per le luci
#include "Lights/update.cpp"
// Sorgente con le funzioni per inizializzare le luci
#include "Lights/init.cpp"
// sorgente che contiene la funzione per controllare i messaggi seriali
#include "Serial/Events.cpp"
// Sorgente con le funzioni per inizializzare lo storage
#include "Storage/init.cpp"
// Sorgente con le funzioni per gestire lo storage
#include "Storage/update.cpp"
// sorgente con le funzioni per l'ora
#include "Time/update.cpp"
// Sorgente con le funzioni per inizializzare l'rtc
#include "Time/init.cpp"
// Sorgente con le utilità per le stringhe
#include "Utils/StringUtils.cpp"
// Sorgente con le definizioni dei pin
#include "main/PinDefs.cpp"
// Liberria per gli allarmi
#include <Alarm.h>

/**
* Contiene la versine del file coremain.cpp corrente
*/
#define CORE_VERSION "1.1"

#pragma region Variables_and_Obj
// Variabili pubbliche per il core

/// Definisce se accelogndere la luce all' avvio della sveglia
bool turn_light_on = true;
/// Funge da buffer per la formattazione dell' orario
char time_buffer[11] = "";
/// Funge da buffer per la formattazione della data
  char date_buffer[11] = "";
/// Raccoglie i pin del progetto e ne permette il passaggio a funzione
  project_pins pins;
/// Raccoglie le impostazioni relative al progetto e ne permette il passaggio a funzione
  project_settings info;
/// Timer per l'aggiornamento deferenziato dei diversi oggetti nella interfaccia
  int timer = 0;
/// Buffer per il messaggio corrente inviato sul seriale
  char cur_msg[20];
/// Tempo della scheda
  TimeDate time;

/// File di impostazioni per la sveglia
  File pinnouts_file;
/// Definisce la posizione del cursore
  location cursor_pos;

/// Inizializzo lo schermo lcd
  LiquidCrystal_I2C lcd(0x27, 20, 4);
/// Rappresenta l'rtc
  RTC_DS1307 rtc;
/// Rappresenta l'allarme
  Alarm *alarm = new Alarm();
/// funge da buffer per tutte le impostazioni di orario
  TimeDate *time_buf = new TimeDate();
/// Rappresenta il keypad
  GFisicalKeypad keypad;

#pragma endregion Variables_and_Obj

/*
        Dichiarazione di tutti i gestori degli eventi nella interfaccia.
        Utilizzati per la pressione dei pulsanti virtuali e per switchare le finestre
*/

/**
* \brief Funzione core_manage_big_light_invert_status, gestisce l' inversione dello stato della luce grossa
* \details  Quando richiamata, accende o spegne la luce grossa in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
  void core_manage_big_light_invert_status(GEvent *event){
    // Luce ambientale
//    // Controllo se è già accesa
//    if(info.ambient_light_state == LED_ON){
//        // La luce è accesa
//        // La spengo
//        digitalWrite(pins.relay_pin, HIGH);
//        // Aggiorno l'indicatore dello stato
//        setBigLight->setText("|off|");
//        // Imposto che la luce è accesa
//        info.ambient_light_state = LED_OFF;
//        // Ridisegno la finestra
//        windows->drawCurrent();
//        // Esco forzatamente
//        return;
//
//    }
//    else{
//        // La luce è spenta
//        //  La accendo
//        digitalWrite(pins.relay_pin, LOW);
////         Aggiorno l'indicatore dello stato
//        setBigLight->setText("|on|");
//        // Imposto che la luce è accesa
//        info.ambient_light_state = LED_ON;
//        // Ridisegno la finestra
//        windows->drawCurrent();
//        // Esco forzatamente
//        return;
//    }
}

/**
* \brief Funzione core_manage_read_light_invert_status, gestisce l' inversione dello stato della luce da lettura (led gialli)
* \details  Quando richiamata, accende o spegne la luce da lettura in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
  void core_manage_read_light_invert_status(GEvent *event){
//    // Luce da lettura
//    // Controllo se è già accesa
//    if(info.read_light_state == LED_ON){
////         La luce è accesa
////         La spengo
//        digitalWrite(pins.reading_light_pin, LOW);
////         Aggiorno l'indicatore dello stato
//        setReadLight->setText("|off|");
//        // Imposto che la luce è accesa
//        info.read_light_state = LED_OFF;
//        // Ridisegno la finestra
//        windows->drawCurrent();
//        // Esco forzatamente
//        return;
//    }
//    else{
////         La luce è spenta
////         La accendo
//        digitalWrite(pins.reading_light_pin, HIGH);
////         Aggiorno l'indicatore dello stato
//        setReadLight->setText("|on|");
//        // Imposto che la luce è accesa
//        info.read_light_state = LED_ON;
//        // Ridisegno la finestra
//        windows->drawCurrent();
//        // Esco forzatamente
//        return;
//    }
}

/**
* \brief Funzione core_manage_see_light_invert_status, gestisce l' inversione dello stato della luce da vista (led bianco)
* \details  Quando richiamata, accende o spegne la luce da vista in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
  void core_manage_see_light_invert_status(GEvent *event){

}

/**
* \brief    Funzione core_manage_alarm_set_hours. Gestisce l'impostazione del parametro ore nella finestra alarmWin
* \details  Quando richiamata entra nella modalità focus: tutti gli eventi non vengono più controllati, eccetto quello di select sul pulsante relativo alle ore
*   Durante questo ciclo legge il valore del potenziometro presente sul keypad e ne converte il valore in un range da 0 a 23 e lo imposta come ore di sveglia
*  Per uscire è necessario premere il pulsante select.
* \param[event]     event     Contiene informazioni sull evento generato dal controllore
* \return   Non viene restituito alcun valore
*/

void core_manage_modify_hour(GEvent *event){
//    SERIAL_SendMessage("Modifico parametro ore in finestra allarme. ");
//    lcd.noBlink();
//    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
//    // contiene il valore del potenziometro
//    int pot_val = 0;
//    // diventa false quando si preme una seconda volta il pulsante select
//    bool stay = true;
//    // contiene il valore calcolato in intero
//    int val;
//    // contiene il valore calcolato in stringa
//    char res[2];
//    // disegno la finestra
//    delay(1000);
//    //alarmWin->draw();
//    do{
//        SERIAL_ReturnToCarriage();
//        SERIAL_SendMessage("Giro di focus");
//        // aggiorno il valore del potenziometro
//        pot_val = analogRead(pins.potent_pin);
//        // calcolo il valore delle ore e lo salvo sul controllo
//        val = (pot_val * 23) / 1023;
//        itoa(val, res, 10);
//        SERIAL_SendMessage(res);
//        // imposto il testo del controllo e lo ridisegno
//        SERIAL_SendMessage("Aggiorno controllo con valore: ");
//        SERIAL_SendMessage(res);
//        SERIAL_ReturnToCarriage();
//        hourAlSet->setText(res);
//        alarmWin->redrawControl("hourAlSet", 1);
//        // aggiorno lo stato del pulsante select
//        stay = !select.isPressed();
//        delay(200);
//    }while(stay);
//    SERIAL_SendMessage("Esco dal focus");
//    lcd.blink();
}

/**
* \brief    Funzione core_manage_modify_minute. Gestisce l'impostazione del parametro minuti nella finestra alarmWin
* \details  Quando richiamata entra nella modalità focus: tutti gli eventi non vengono più controllati, eccetto quello di select sul pulsante relativo ai minuti
*   Durante questo ciclo legge il valore del potenziometro presente sul keypad e ne converte il valore in un range da 0 a 59 e lo imposta come minuti di sveglia
*  Per uscire è necessario premere il pulsante select.
* \param[event]     event     Contiene informazioni sull evento generato dal controllore
* \return   Non viene restituito alcun valore
*/
void core_manage_modify_minute(GEvent *event){
//    SERIAL_SendMessage("Modifico parametro ore in finestra allarme. ");
//    lcd.noBlink();
//    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
//    // contiene il valore del potenziometro
//    unsigned int pot_val = 0;
//    // diventa false quando si preme una seconda volta il pulsante select
//    bool stay = true;
//    // contiene il valore calcolato in intero
//    int val;
//    // contiene il valore calcolato in stringa
//    char res[2];
//    // disegno la finestra
//    delay(1000);
//    //alarmWin->draw();
//    do{
//        SERIAL_ReturnToCarriage();
//        SERIAL_SendMessage("Giro di focus");
//        // aggiorno il valore del potenziometro
//        pot_val = analogRead(pins.potent_pin);
//        // calcolo il valore delle ore e lo salvo sul controllo
//        val = (pot_val * 59)/1019;
//        intToArray(val, res);
//
//        SERIAL_SendMessage(res);
//        // imposto il testo del controllo e lo ridisegno
//        SERIAL_SendMessage("Aggiorno controllo con valore: ");
//        SERIAL_SendMessage(val);
//        SERIAL_SendMessage("Valore potenziometro: ");
//        SERIAL_SendMessage(analogRead(pins.potent_pin));
//        SERIAL_ReturnToCarriage();
//        minuteAlSet->setText(res);
//        minuteAlSet->draw();
//        // aggiorno lo stato del pulsante select
//        stay = !select.isPressed();
//        delay(200);
//    }while(stay);
//    SERIAL_SendMessage("Esco dal focus");
//    lcd.blink();
//    //alarmWin->draw();
}

/**
*   \brief Funzione core_manage_alarm_invert_status. Gestisce l'inversione dello stato della sveglia.
*   \details    Quando richiamata controlla che la sveglia abbia un orario impostato. Se non ce ne è uno viene visualizzata la finestra per impostarlo.
*   Se invece è presente un valore allora inverte lo stato di abilitazione: se prima la sveglia era abilitata ora non lo è più
*   \param[event]   event   Contiene informazioni sull evento generato dal gestore
*   \return     Nessun valore restituito
*/
  void core_manage_alarm_invert_status(GEvent *event){
    // Controllo se l'allarme ha un orario
    if(alarm != nullptr){
        // Se l'utente ha impostato un allarme
        if(alarm->hasTime()){
            // Inverto lo stato dell' allarme
            alarm->setActive(!alarm->getState());
            // Scrivo sul seriale
#ifdef DEBUG_MODE
            SERIAL_ReturnToCarriage();
            SERIAL_SendMessage("Inverto stato allarme su: ");
            SERIAL_SendMessage(alarm->getState());
            SERIAL_ReturnToCarriage();
#endif
            if(alarm->getState()){
                alarmState->setText("|on|");
            }
            else{
                alarmState->setText("|off|");
            }
            timesWin->redrawControl("alarmState", 5);
        }
        else{
            // L'utente non ha impostato nessun allarme
#ifdef DEBUG_MODE
            // Mostro la finestra per l'impostazione di un allarme
            SERIAL_ReturnToCarriage();
            SERIAL_SendMessage("Attenzione: nessun allarme impostato, avvio finestra impostazione");

            SERIAL_ReturnToCarriage();
#endif
            // Disegno la finestra
            windows->draw("alarmWin");
        }
    }
}

/** \brief  Funzione core_manage_alarm_on, gestisce l'avvio della sveglia ed esegue le operazioni necessarie.
 *  \details    Viene chiamato dal controllore di alarm. Al suo avvio notifica la cosa sul seriale. A seconda delle preferenze dell' utente
 *  accende o no la luce e produce un suono.
 * \return  Non restituisce valori
 */
  void core_manage_alarm_on(){
#ifdef DEBUG_MODE
    // do informazioni di debug
    SERIAL_SendMessage("Raggiunto orario: ");
    SERIAL_SendMessage(&time);
    SERIAL_SendMessage(endl "  Sveglia suonata." endl);
#endif
    // controllo che la sveglia esista
    if(alarm != nullptr){
        if(alarm->getLight()){
            digitalWrite(pins.relay_pin, LOW);
        }
        // eseguo una melodia
        tone(A0, 500, 2000);
        tone(A0, 200, 4000);
    }
}

void core_manage_alarm_save(GEvent *e){
//    // contiene l'orario impostato dai controlli nella finestra alarmWin
//    char *hour = hourAlSet->getText();
//    char *minu = minuteAlSet->getText();
//    // controllo gli spazi e correggo le ore
//    if(hour[1] == ' '){
//        // il numero ha 1 sola cifra
//        // tolgo lo spazio
//        hour[1] = '\0';
//    }
//    else if(strcmp(hour, "00") == 0){
//        strcpy(hour, "0");
//    }
//
//    if(minu[1] == ' '){
//        // il numero ha 1 sola cifra
//        // tolgo lo spazio
//        minu[1] = '\0';
//    }
//    else if(strcmp(minu, "00") == 0){
//        strcpy(minu, "0");
//    }
//#ifdef DEBUG_MODE
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage("Salvataggio allarme. Informazioni: " endl);
//    SERIAL_SendMessage("Divisione caratteri ore: ");
//    strsplit(hour);
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage("Divisione caratteri minuti: ");
//    strsplit(minu);
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage("Allarme settimanale: ");
//    SERIAL_SendMessage(settimanalBox->isChecked());
//    SERIAL_ReturnToCarriage();
//    SERIAL_SendMessage("Richiede accensione radio: ");
//    SERIAL_SendMessage(radioBox->isChecked());
//    SERIAL_SendMessage("Accensione luce: ");
//    SERIAL_SendMessage(lightBox->isChecked());
//    SERIAL_ReturnToCarriage();
//#endif
//
//    // salvo le ore
//    alarm->setStartHour(atoi(hour));
//    // salvo i minuti
//    alarm->setStartMinute(atoi(minu));
//
//    alarm->enable();
//
//    // salvo informazioni aggiuntive
//    alarm->setSelective(settimanalBox->isChecked());
//    alarm->setRadio(radioBox->isChecked());
//    alarm->setLight(lightBox->isChecked());
//    alarm->setHandler(core_manage_alarm_on);
//    // esco dalla finestra
//    // mostro la home
//    windows->draw("mainWin");
//    // scrivo la sveglia sul seriale
//    //SERIAL_SendMessage(&alarm);
}


void setup(){
#ifdef DEBUG_MODE
    // Inizializzo il seriale
    Serial.begin(115200);
    // Mostro un hello word
    Serial.println(F("Avvio sveglia. "));
#endif
    // Inizializzo lo schermo
    lcd.init();
    // Accendo la retroilluminazione
    lcd.backlight();
    // Avvio il blink del cursore
    lcd.blink();
    // Inizializzo rtc
    initRtc(&rtc);
    // Inizializzo la luce grossa
    initBigLight(pins.relay_pin);
    // Inizializzo la luce da vista
    initSeeLight(pins.see_light_pin);
    // Inizializzo la luce da lettura
    initReadLight(pins.reading_light_pin);
    // Inizializzo il keypad
    keypad.setLeftBtnPin(pins.left_btn_pin);
    keypad.setRightBtnPin(pins.right_btn_pin);
    keypad.setUpBtnPin(pins.up_btn_pin);
    keypad.setDownBtnPin(pins.down_btn_pin);
    keypad.setSelectBtnPin(pins.select_btn_pin);
    // Imposto il gestore finestre
    keypad.attachWinList(windows);
    // Avvio il tutto
    keypad.beginAll();
#ifdef DEBUG_MODE
    keypad.writeReference();
#endif
    // Inizializzo la finestra principale
    initMainWindow(&lcd);
    // Inizializzo la finestra per il tempo
    initTimesWindow(&lcd, core_manage_alarm_invert_status);
    // Inizializzo la finestra per le luci
    initLightWindow(&lcd, core_manage_big_light_invert_status, core_manage_read_light_invert_status, core_manage_see_light_invert_status );
    // Inizializzo la finestra per l'allarme
//    initAlarmWindow(&lcd, core_manage_modify_hour, core_manage_modify_minute, core_manage_alarm_save);
//    // Disegno la finestra principale
    windows->drawMain();
}

/**
* \brief    Funzione loop, aggiorna la sveglia ciclicamente con diversi timing
*  \details Viene chiamata dallo sketch Core.ino nella funzione loop. Aggiorna l'interfaccia, lo stato dei pulsanti, i messaggi seriali con un diverso timing.
*   Utilizza la variabile timer. Ogni 2 secondi vengono aggiornati i valori di data e ora e vengono rappresentati nella finestra tempo, se ci si trova dentro
*   Viene controllato lo stato dell' allarme.
*   Ad ogni ciclo viene aggiornato l'input seriale e controllato lo stato della sveglia.
*   \note   La funzione è statica
*   \return  Nessun valore restituito
*/
void loop(){
#ifdef DEBUG_MODE
    Serial.println("Loop");
    // Scrivo lo stato del keypad
    keypad.writeState();
#endif
    delay(100);
    // Aggiorno il keypad
    keypad.update();
    // Posiziono il cursore
    windows->locateCursor(&lcd);
}

#endif // CORE_MAIN_CPP


