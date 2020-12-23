/**
 * \file CoreMain.cpp
 * \author   Cavallo Gabriele
 * \brief   File principale del progetto sveglia arduino. Viene chiamato dallo sketch dell' ide integrato
 */
#ifndef CORE_MAIN_CPP
#define CORE_MAIN_CPP

// Libreria per la gestione delle interfaccie
#include <ArduWin.h>
// Libreria per gli schermi
#include <LiquidCrystal_I2C.h>
// Libreria per la gestione della sd
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
// Sorgente con le funzioni per inizializzare lo storage
#include "Storage/init.cpp"
// sorgente con le funzioni per l'ora
#include "Time/update.cpp"
// Sorgente con le funzioni per inizializzare l'rtc
#include "Time/init.cpp"
// Sorgente con le utilità per le stringhe
#include "Utils/StringUtils.cpp"
// Sorgente con le definizioni dei pin
#include "main/PinDefs.cpp"
#include <MemoryFree.h>
// Liberria per gli allarmi
#include <Alarm.h>

#pragma region Variables_and_Obj
// Variabili pubbliche per il core
/// Raccoglie i pin del progetto e ne permette il passaggio a funzione
project_pins pins;
/// Raccoglie le impostazioni relative al progetto e ne permette il passaggio a funzione
project_settings info;
/// Tempo della scheda
TimeDate time;
/// Inizializzo lo schermo lcd
LiquidCrystal_I2C lcd(0x27, 20, 4);
/// Rappresenta l'rtc
RTC_DS1307 rtc;
/// Rappresenta l'allarme
Alarm *alarm = new Alarm();
// Buffer per la formattazione dell' orario
char date_buffer[11];
// Buffer
char time_buffer[11];
/// Rappresenta il keypad
GFisicalKeypad keypad;

// Timer per l'aggiornamento della finestra time
GTimer timeWinUpdater(7000);
// Timer per l'aggiornamento del keypad
GTimer keypadUpdater(50);

#pragma endregion Variables_and_Obj

#pragma region Window_handlers
/*
    Dichiarazione di tutti i gestori degli eventi nella interfaccia.
    Utilizzati per la pressione dei pulsanti virtuali e per switchare le finestre
*/

/**
 * \brief aggiorna effettivamente la finestra time
 */
void update_time_window(){
    // IMposto il testo dell' orario
    time.getFormTime(time_buffer);
    timeLabel.setText(time_buffer);
    // Formatto il testo della data
    time.getFormDate(date_buffer);
    // Imposto i vari testo
    dateLabel.setText(date_buffer);
    // Ottengo il nome del giorno
    dayLabel.setText(time.getDayOfTheWeek());
}

/**
* \brief Funzione core_manage_read_light_invert_status, gestisce l' inversione dello stato della luce da lettura (led gialli)
* \details  Quando richiamata, accende o spegne la luce da lettura in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
void core_manage_read_light_invert_status(GEvent *event){
    // Luce da lettura
    // Controllo se è già accesa
    if(info.read_light_state == LED_ON){
    //  La luce è accesa
    //  La spengo
        digitalWrite(pins.reading_light_pin, LOW);
//         Aggiorno l'indicatore dello stato
        setReadLight.setText("|off|");
        // Imposto che la luce è accesa
        info.read_light_state = LED_OFF;
    }
    else{
        // La luce è spenta
        // La accendo
        digitalWrite(pins.reading_light_pin, HIGH);
//         Aggiorno l'indicatore dello stato
        setReadLight.setText("|on|");
        // Imposto che la luce è accesa
        info.read_light_state = LED_ON;
    }
    delete event;
}

/**
* \brief Funzione core_manage_see_light_invert_status, gestisce l' inversione dello stato della luce da vista (led bianco)
* \details  Quando richiamata, accende o spegne la luce da vista in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
void core_manage_see_light_invert_status(GEvent *event){
    // Luce da lettura
    // Controllo se è già accesa
    if(info.see_light_state == LED_ON){
//         La luce è accesa
//         La spengo
        digitalWrite(pins.see_light_pin, LOW);
//         Aggiorno l'indicatore dello stato
        setSeeLight.setText("|off|");
        // Imposto che la luce è accesa
        info.see_light_state = LED_OFF;
    }
    else{
        // La luce è spenta
        // La accendo
        digitalWrite(pins.see_light_pin, HIGH);
//         Aggiorno l'indicatore dello stato
        setSeeLight.setText("|on|");
        // Imposto che la luce è accesa
        info.see_light_state = LED_ON;
    }
    // Cancello l'evento dallo heap
    delete event;

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
    lcd.noBlink();
    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
    // contiene il valore del potenziometro
    unsigned int pot_val = 0;
    // diventa false quando si preme una seconda volta il pulsante select
    bool stay = true;
    // contiene il valore calcolato in intero
    unsigned int val;
    // Buffer per la conversione in stringa
    char str[4];
    do{
        // aggiorno il valore del potenziometro
        pot_val = analogRead(pins.potent_pin);
        // calcolo il valore delle ore e lo salvo sul controllo
        val = ((pot_val * 23) / 1023) + 1;

        itoa(val, str, 10);

        hourAlSet.setText(str);
        // aggiorno lo stato del pulsante select
        stay = !keypad.getSelectBtn()->isPressed();
        delay(200);
    }while(stay);
    lcd.blink();

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
    lcd.noBlink();
    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
    // contiene il valore del potenziometro
    unsigned int pot_val = 0;
    // diventa false quando si preme una seconda volta il pulsante select
    bool stay = true;
    // contiene il valore calcolato in intero
    unsigned int val;
    // contiene il valore calcolato in stringa
    char str[4];
    do{
        // aggiorno il valore del potenziometro
        pot_val = analogRead(pins.potent_pin);
        // calcolo il valore delle ore e lo salvo sul controllo
        val = ((pot_val * 59)/1019) + 1;

        itoa(val, str, 10);
        minuteAlSet.setText(str);

        // aggiorno lo stato del pulsante select
        stay = !keypad.getSelectBtn()->isPressed();
        delay(200);
    }while(stay);
    lcd.blink();

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
            // Inverto lo stato di visualizzazione della icona sveglia
            if(alarm->getState()){
                // Mostro
                alrmState.show();
            }
            else{
                // Nascondo
                alrmState.hide();
            }
            // Aggiorno la finestra time
            update_time_window();
        }
        else{
            // Disegno la finestra
            windows.draw("alarmWin");
        }
    }
    delete event;
}

/** \brief  Funzione core_manage_alarm_on, gestisce l'avvio della sveglia ed esegue le operazioni necessarie.
 *  \details    Viene chiamato dal controllore di alarm. Al suo avvio notifica la cosa sul seriale. A seconda delle preferenze dell' utente
 *  accende o no la luce e produce un suono.
 * \return  Non restituisce valori
 */
void core_manage_alarm_on(){
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
    // contiene l'orario impostato dai controlli nella finestra alarmWin
    char *hour = hourAlSet.getText();
    char *minu = minuteAlSet.getText();
    // salvo le ore
    alarm->setStartHour(atoi(hour));
    // salvo i minuti
    alarm->setStartMinute(atoi(minu));
    alarm->enable();
    // salvo informazioni aggiuntive
    alarm->setSelective(settimanalBox.isChecked());
    alarm->setRadio(radioBox.isChecked());
    alarm->setLight(lightBox.isChecked());
    alarm->setHandler(core_manage_alarm_on);
    // Mostro l'indicatore di sveglia attiva
    alrmState.show();

    // esco dalla finestra
    // mostro la home
    windows.drawMain();
}

/**
 * \brief Funzione core_manage_time_window_update, gestisce l'aggiornamento ricorsivo della finestra time
 * @param time
 * @param timer_name
 */
void core_manage_time_window_update(unsigned int t, char *timer_name){
    // Controllo in che finestra sono
    if(windows.isCurrent("timesWin")){
        update_time_window();
    }
}

/**
 * \brief Funzione core_manage_keypad_update, gestisce l'aggiornamento dei pulsanti del keypad
 * @param t
 * @param timer_name
 */
void core_manage_keypad_update(unsigned int t, char *timer_name){
    // Aggiorno il keypad
    keypad.updateDebounced(1);
    // Posiziono il cursore
    windows.locateCursor(&lcd);
}

void core_manage_alarm_info_request(GEvent *event){
    delete event;
}

/**
 * \brief Gestisce la inizializzazione della finestra time
 * @param event
 */
void core_manage_time_win_init(GEvent *event){
    update_time_window();
    delete event;
}

#pragma endregion Window_handlers

void setup(){
    Serial.begin(115200);
    Serial.println("Avvio");
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
    keypad.attachWinList(&windows);
    // Avvio il tutto
    keypad.beginAll();
#ifdef DEBUG_MODE
//    keypad.writeReference();
#endif

    // Inizializzo i timer
    timeWinUpdater.setName("timeWinUpdater");
    // Imposto il gestore
    timeWinUpdater.setActivationHandler(core_manage_time_window_update);
    // Inizializzo il timer per l'aggiornamento del keypad
    keypadUpdater.setName("keypadUpdater");
    keypadUpdater.setActivationHandler(core_manage_keypad_update);

    // Avvio i timer
    timeWinUpdater.start();
    keypadUpdater.start();

    // Inizializzo la finestra principale
    initMainWindow(&lcd);
//    // Inizializzo la finestra per il tempo
    initTimesWindow(&lcd, core_manage_alarm_invert_status, core_manage_time_win_init, core_manage_alarm_info_request);
    // Inizializzo la finestra per le luci
    initLightWindow(&lcd, core_manage_read_light_invert_status, core_manage_see_light_invert_status );
//     Inizializzo la finestra per l'allarme
    initAlarmWindow(&lcd, core_manage_modify_hour, core_manage_modify_minute, core_manage_alarm_save);
    // Inizializzo rtc
    if(initRtc(&rtc)){
        // Mostro l'indicatore
        rtcState.show();
        rtcState.draw();
    }
    // Inizializzo la scheda sd
    if(initSd(pins.sd_cs_pin)){
        sdState.show();
    }
    // Disegno la finestra principale
    windows.drawMain();
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
    // Leggo l'orario corrente
    readTime(&time, &rtc);
    // Aggiorno i timer
    timeWinUpdater.update();
    keypadUpdater.update();

    // Aggiorno la sveglia
    alarm->updateAlarm(&time);
    // Attendo 1 millisecondo
    delay(1);
}

#endif // CORE_MAIN_CPP


