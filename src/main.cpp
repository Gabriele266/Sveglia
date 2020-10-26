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
// Libreria per lo schermo e le interfaccie
#include "../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
// Libreria per le sd
#include "../lib/SD/src/SD.h"
// Libreria per la comunicazione spi
#include <SPI.h>
// Header di Arduino
#include <Arduino.h>
// Header per il tempo
#include "../lib/TimeDate/TimeDate.h"
// Libreria RTC_DS1307
#include "../lib/RTClib/RTClib.h"
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
// Header per il controllo del keypad
#include "Keypad/update.cpp"
// Header per inizializzare il keypad
#include "Keypad/init.cpp"
// Liberria per gli allarmi
#include "../lib/Alarm/Alarm.h"

/**
* Contiene la versine del file coremain.cpp corrente
*/
#define CORE_VERSION "1.1"

#pragma region Variables_and_Obj
// Variabili pubbliche per il core

/// Definisce se accelogndere la luce all' avvio della sveglia
static bool turn_light_on = true;
/// Funge da buffer per la formattazione dell' orario
static char time_buffer[11] = "";
/// Funge da buffer per la formattazione della data
static char date_buffer[11] = "";
/// Raccoglie i pin del progetto e ne permette il passaggio a funzione
static project_pins pins;
/// Raccoglie le impostazioni relative al progetto e ne permette il passaggio a funzione
static project_settings info;
/// Timer per l'aggiornamento deferenziato dei diversi oggetti nella interfaccia
static int timer = 0;
/// Buffer per il messaggio corrente inviato sul seriale
static char cur_msg[20];
/// Tempo della scheda
static TimeDate time;

/// File di impostazioni per la sveglia
static File pinnouts_file;
/// Definisce la posizione del cursore
static location cursor_pos;

/// Inizializzo lo schermo lcd
static LiquidCrystal_I2C lcd(0x27, 20, 4);
/// Rappresenta l'rtc
static RTC_DS1307 rtc;
/// Rappresenta l'allarme
static Alarm *alarm = new Alarm();
/// funge da buffer per tutte le impostazioni di orario
static TimeDate *time_buf = new TimeDate();
/// Rappresenta il keypad
static GFisicalKeypad keypad;

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
static void core_manage_big_light_invert_status(GEvent *event){
    // Luce ambientale
    // Controllo se è già accesa
    if(info.ambient_light_state == LED_ON){
        // La luce è accesa
        // La spengo
        digitalWrite(pins.relay_pin, HIGH);
        // Aggiorno l'indicatore dello stato
        setBigLight->setText("|off|");
        // Imposto che la luce è accesa
        info.ambient_light_state = LED_OFF;
        // Ridisegno la finestra
        windows->drawCurrent();
        // Esco forzatamente
        return;

    }
    else{
        // La luce è spenta
        //  La accendo
        digitalWrite(pins.relay_pin, LOW);
//         Aggiorno l'indicatore dello stato
        setBigLight->setText("|on|");
        // Imposto che la luce è accesa
        info.ambient_light_state = LED_ON;
        // Ridisegno la finestra
        windows->drawCurrent();
        // Esco forzatamente
        return;
    }
}

/**
* \brief Funzione core_manage_read_light_invert_status, gestisce l' inversione dello stato della luce da lettura (led gialli)
* \details  Quando richiamata, accende o spegne la luce da lettura in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
static void core_manage_read_light_invert_status(GEvent *event){
    // Luce da lettura
    // Controllo se è già accesa
    if(info.read_light_state == LED_ON){
//         La luce è accesa
//         La spengo
        digitalWrite(pins.reading_light_pin, LOW);
//         Aggiorno l'indicatore dello stato
        setReadLight->setText("|off|");
        // Imposto che la luce è accesa
        info.read_light_state = LED_OFF;
        // Ridisegno la finestra
        windows->drawCurrent();
        // Esco forzatamente
        return;
    }
    else{
//         La luce è spenta
//         La accendo
        digitalWrite(pins.reading_light_pin, HIGH);
//         Aggiorno l'indicatore dello stato
        setReadLight->setText("|on|");
        // Imposto che la luce è accesa
        info.read_light_state = LED_ON;
        // Ridisegno la finestra
        windows->drawCurrent();
        // Esco forzatamente
        return;
    }
}

/**
* \brief Funzione core_manage_see_light_invert_status, gestisce l' inversione dello stato della luce da vista (led bianco)
* \details  Quando richiamata, accende o spegne la luce da vista in base al suo vecchio stato.
* Viene chiamata dalla finestra delle luci, il relazione alla pressione del pulsante select su un GButton che può gestire questa luce.
* \param[event]     event   Contiene un evento generato del gestore principale degli eventi della finestra.
* \return  void     Nessun tipo restituito
*/
static void core_manage_see_light_invert_status(GEvent *event){

}

/**
* \brief    Funzione core_manage_alarm_set_hours. Gestisce l'impostazione del parametro ore nella finestra alarmWin
* \details  Quando richiamata entra nella modalità focus: tutti gli eventi non vengono più controllati, eccetto quello di select sul pulsante relativo alle ore
*   Durante questo ciclo legge il valore del potenziometro presente sul keypad e ne converte il valore in un range da 0 a 23 e lo imposta come ore di sveglia
*  Per uscire è necessario premere il pulsante select.
* \param[event]     event     Contiene informazioni sull evento generato dal controllore
* \return   Non viene restituito alcun valore
*/

/*static void core_manage_modify_hour(GEvent *event){
    SERIAL_SendMessage("Modifico parametro ore in finestra allarme. ");
    lcd.noBlink();
    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
    // contiene il valore del potenziometro
    int pot_val = 0;
    // diventa false quando si preme una seconda volta il pulsante select
    bool stay = true;
    // contiene il valore calcolato in intero
    int val;
    // contiene il valore calcolato in stringa
    char res[2];
    // disegno la finestra
    delay(1000);
    //alarmWin->draw();
    do{
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Giro di focus");
        // aggiorno il valore del potenziometro
        pot_val = analogRead(pins.potent_pin);
        // calcolo il valore delle ore e lo salvo sul controllo
        val = (pot_val * 23) / 1023;
        itoa(val, res, 10);
        SERIAL_SendMessage(res);
        // imposto il testo del controllo e lo ridisegno
        SERIAL_SendMessage("Aggiorno controllo con valore: ");
        SERIAL_SendMessage(res);
        SERIAL_ReturnToCarriage();
        hourAlSet->setText(res);
        alarmWin->redrawControl("hourAlSet", 1);
        // aggiorno lo stato del pulsante select
        stay = !select.isPressed();
        delay(200);
    }while(stay);
    SERIAL_SendMessage("Esco dal focus");
    lcd.blink();
}*/

/**
* \brief    Funzione core_manage_modify_minute. Gestisce l'impostazione del parametro minuti nella finestra alarmWin
* \details  Quando richiamata entra nella modalità focus: tutti gli eventi non vengono più controllati, eccetto quello di select sul pulsante relativo ai minuti
*   Durante questo ciclo legge il valore del potenziometro presente sul keypad e ne converte il valore in un range da 0 a 59 e lo imposta come minuti di sveglia
*  Per uscire è necessario premere il pulsante select.
* \param[event]     event     Contiene informazioni sull evento generato dal controllore
* \return   Non viene restituito alcun valore
*/
/*static void core_manage_modify_minute(GEvent *event){
    SERIAL_SendMessage("Modifico parametro ore in finestra allarme. ");
    lcd.noBlink();
    // modalità focus: aggiorno solo il controllo, lo stato del potenziometro e lo stato del pulsante select.
    // contiene il valore del potenziometro
    unsigned int pot_val = 0;
    // diventa false quando si preme una seconda volta il pulsante select
    bool stay = true;
    // contiene il valore calcolato in intero
    int val;
    // contiene il valore calcolato in stringa
    char res[2];
    // disegno la finestra
    delay(1000);
    //alarmWin->draw();
    do{
        SERIAL_ReturnToCarriage();
        SERIAL_SendMessage("Giro di focus");
        // aggiorno il valore del potenziometro
        pot_val = analogRead(pins.potent_pin);
        // calcolo il valore delle ore e lo salvo sul controllo
        val = (pot_val * 59)/1019;
        intToArray(val, res);

        SERIAL_SendMessage(res);
        // imposto il testo del controllo e lo ridisegno
        SERIAL_SendMessage("Aggiorno controllo con valore: ");
        SERIAL_SendMessage(val);
        SERIAL_SendMessage("Valore potenziometro: ");
        SERIAL_SendMessage(analogRead(pins.potent_pin));
        SERIAL_ReturnToCarriage();
        minuteAlSet->setText(res);
        minuteAlSet->draw();
        // aggiorno lo stato del pulsante select
        stay = !select.isPressed();
        delay(200);
    }while(stay);
    SERIAL_SendMessage("Esco dal focus");
    lcd.blink();
    //alarmWin->draw();
}*/

/**
*   \brief Funzione core_manage_alarm_invert_status. Gestisce l'inversione dello stato della sveglia.
*   \details    Quando richiamata controlla che la sveglia abbia un orario impostato. Se non ce ne è uno viene visualizzata la finestra per impostarlo.
*   Se invece è presente un valore allora inverte lo stato di abilitazione: se prima la sveglia era abilitata ora non lo è più
*   \param[event]   event   Contiene informazioni sull evento generato dal gestore
*   \return     Nessun valore restituito
*/
static void core_manage_alarm_invert_status(GEvent *event){
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
            // Disegno la finestra
            windows->draw("alarmWin");
            SERIAL_ReturnToCarriage();
#endif
        }
    }
}

/** \brief  Funzione core_manage_alarm_on, gestisce l'avvio della sveglia ed esegue le operazioni necessarie.
 *  \details    Viene chiamato dal controllore di alarm. Al suo avvio notifica la cosa sul seriale. A seconda delle preferenze dell' utente
 *  accende o no la luce e produce un suono.
 * \return  Non restituisce valori
 */
static void core_manage_alarm_on(){
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

/**
*   \brief  Funzione core_manage_alarm_save, gestisce il salvataggio delle informazioni della sveglia.
*   \details    Viene chiamata dalla pressione del pulsante Vai nella finestra alarmWin.
*   Inizialmente converte i valori stringa dei pulsanti per le ore e i minuti in numeri salvabili nell' oggetto Alarm globale alarm.
*   \note   Gli 00 vengono convertiti in 0
*   Successivamente, dopo aver salvato nell' oggetto i valori convertiti, salva le impostazioni espresse dalle checkbox nella parte
*   sinistra della finestra.
*   Infine mostra una GNotification per informare l'utente e abilita la sveglia
*   \param [e] e Contiene le informazioni dell' evento
*   \return nessun valore restituito
*/
void core_manage_alarm_save(GEvent *e){
    // contiene l'orario impostato dai controlli nella finestra alarmWin
    char *hour = hourAlSet->getText();
    char *minu = minuteAlSet->getText();
    // controllo gli spazi e correggo le ore
    if(hour[1] == ' '){
        // il numero ha 1 sola cifra
        // tolgo lo spazio
        hour[1] = '\0';
    }
    else if(strcmp(hour, "00") == 0){
        strcpy(hour, "0");
    }

    if(minu[1] == ' '){
        // il numero ha 1 sola cifra
        // tolgo lo spazio
        minu[1] = '\0';
    }
    else if(strcmp(minu, "00") == 0){
        strcpy(minu, "0");
    }
#ifdef DEBUG_MODE
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Salvataggio allarme. Informazioni: " endl);
    SERIAL_SendMessage("Divisione caratteri ore: ");
    strsplit(hour);
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Divisione caratteri minuti: ");
    strsplit(minu);
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Allarme settimanale: ");
    SERIAL_SendMessage(settimanalBox->isChecked());
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Richiede accensione radio: ");
    SERIAL_SendMessage(radioBox->isChecked());
    SERIAL_SendMessage("Accensione luce: ");
    SERIAL_SendMessage(lightBox->isChecked());
    SERIAL_ReturnToCarriage();
#endif

    // salvo le ore
    alarm->setStartHour(atoi(hour));
    // salvo i minuti
    alarm->setStartMinute(atoi(minu));

    alarm->enable();

    // salvo informazioni aggiuntive
    alarm->setSelective(settimanalBox->isChecked());
    alarm->setRadio(radioBox->isChecked());
    alarm->setLight(lightBox->isChecked());
    alarm->setHandler(core_manage_alarm_on);
    // esco dalla finestra
    // mostro la home
    windows->draw("mainWin");
    // scrivo la sveglia sul seriale
    //SERIAL_SendMessage(&alarm);
}

/**
*   \brief  Funzione core_setup funge da funzione per l'inizializzazione di tutti i componenti della sveglia.
*   \details    Inizializza tutto. Viene chiamata dallo sketch arduino Core.ino all' interno del setup.
*   Inizializza la scheda sd per poter leggere le impostazioni e la configurazione del pinnout del progetto. (chiamata STORAGE_InitSd(pins.sd_cs_pin, info.enable_serial_debug))
*   Legge la configurazione dei pin dal file PINS.TXT e inizializza tutte le luci (grossa, vista e lettura).
*   Inizializza lo schermo per poterlo utilizzarlo come interfaccia.
*   Inizializza l' rtc e tutte le finestre, tramite la chiamata delle funzioni del modulo Interface/init.cpp
*   Mostra all' utente sul seriale la configurazione dei pin letta dal file
*   Infine disegna la finestra principale.
*   \note La funzione è statica
*   \return Nessun valore restituito
*/
void setup(){
    // Saluto il mondo
    Serial.begin(57600);
    SERIAL_SendMessage("Core avviato. Eseguo core_setup" endl, info.enable_serial_debug);
    // Inizializzo la sd
    info.sd_success = STORAGE_InitSd(pins.sd_cs_pin, info.enable_serial_debug);
#ifdef DEBUG_MODE
    SERIAL_SendMessage("Risultato inizializzazione sd: ");
    SERIAL_SendMessage(info.sd_success);
    SERIAL_ReturnToCarriage();
#endif
    // Controllo se l'inizializzazione della sd ha avuto successo
    if(info.sd_success){
        // Leggo la configurazione dei pin
        //STORAGE_ReadPinConfig(&pins, pinnouts_file, info.enable_serial_debug);
    }
    // Inizializzo la luce grossa
    LIGHTS_InitBigLight(pins.relay_pin, info.enable_serial_debug);
    // Inizializzo la luce da lettura
    LIGHTS_InitReadingLight(pins.reading_light_pin, info.enable_serial_debug);
    // Inizializzo la luce da vista
    LIGHTS_InitSeeLight(pins.see_light_pin, info.enable_serial_debug);

    // Faccio il bench della luce grossa
    //LIGHTS_BenchBigLight(pins.big_light_pin, enable_serial_debug);
    //listInfos(sd_cs_pin);
    // Inizializzo lo schermo lcd
    lcd.init();
    // Attivo la backlight
    lcd.backlight();
    // Invio il log
#ifdef DEBUG_MODE
    SERIAL_SendMessage("Inizializzazione schermo effettuata. " endl);
#endif
    // Inizializzo l'rtc
    TIME_InitRtc(&rtc, info.enable_serial_debug);
    // Inizializzo il keypad
//    KEYPAD_InitKeypad(&right, &left, &up, &down, &select, &alarm_in, &lights_in, &pins);
    // Inizializzo il pin per il potenziometro
    pinMode(pins.potent_pin, INPUT);
    // Inizializzo una nuova finestra principale
    INTERFACE_InitMainWin(&lcd);
    // Inizializzo la finestra per le luci
    INTERFACE_InitLightWin(&lcd, core_manage_big_light_invert_status, core_manage_read_light_invert_status, core_manage_see_light_invert_status);
    // Inizializzo la finestra per il tempo
    INTERFACE_InitTimesWin(&lcd, core_manage_alarm_invert_status);
    // Iizializzo la finestra allarme
//    INTERFACE_InitAlarmWin(&lcd, core_manage_modify_hour, core_manage_modify_minute, core_manage_alarm_save);
#ifdef DEBUG_MODE
    // Scrivo la configurazione dei pin
    SERIAL_WritePinnout(&pins);
    // Indico che ho finito l'inizializzazione della scheda
    SERIAL_SendMessage("Inizializzazione sveglia terminata. " endl);
#endif
    // Disegno la finestra principale
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
    if(timer == 7000){
#ifdef DEBUG_MODE
        SERIAL_SendMessage("Passati 2 secondi dall' ultimo aggiornamento finestre. " endl);
#endif
        // Ridisegno la finestra tempo, se ci sono
        if(windows->isCurrent("timesWin")){
            SERIAL_SendMessage("Siamo nella finestra tempo");
            // Leggo il tempo e lo invio
            TIME_ReadTime(&time, &rtc);
            // Salvo il tempo in una stringa
            time.getFormTime(time_buffer);
            time.getFormDate(date_buffer);
#ifdef DEBUG_MODE
            SERIAL_SendMessage( endl "Stringa data: ");
            SERIAL_SendMessage(time_buffer);
            SERIAL_ReturnToCarriage();
            SERIAL_SendMessage(date_buffer);
#endif
            // Aggiorno l'indicatore del tempo
            timeLabel->setText(time_buffer);
            dateLabel->setText(date_buffer);
            dayLabel->setText(time.getDayOfTheWeek());
#ifdef DEBUG_MODE
            SERIAL_SendMessage("Nome giorno corrente: ");
            SERIAL_SendMessage(time.getDayOfTheWeek());
#endif
            // Ridisegno i controlli
            timesWin->redrawControl("timeLabel", 5);
            timesWin->redrawControl("dateLabel", 8);
            timesWin->redrawControl("dayLabel", 3);

            // Aggiorno l'indicatore dello stato dell' allarme
            if(alarm->getState() == false){
                // Metto la stringa su off
                alarmState->setText("|off|");
            }
            else{
                alarmState->setText("|on|");
            }
           // Ridisegno il controllo
            timesWin->redrawControl("alarmState", 5);
        }
        timer = 0;
    }
    else if(timer == 2000){
        // mostro informazioni di debug
#ifdef DEBUG_MODE
        SERIAL_ReturnToCarriage();
        // mostro il nome della finestra main
        SERIAL_SendMessage("Nome finestra principale: ");
        SERIAL_SendMessage(windows->get("mainWin")->getName());
        SERIAL_ReturnToCarriage();
        // mostro il nome della finestra timesWin
        SERIAL_SendMessage("Nome finestra timesWin: ");
        SERIAL_SendMessage(windows->get("timesWin")->getName());
        SERIAL_ReturnToCarriage();
        
        SERIAL_SendMessage("Loop" endl);
        timer += 100;
#endif
    }
    else{
        // Incremento il timer
        timer += 100;
    }
    // Aggiorno l'input
    //SERIAL_UpdateInput(cur_msg);
//    if(strlen(cur_msg) > 0){
//        SERIAL_SendMessage(cur_msg);
//        SERIAL_ControlMessage(cur_msg, windows, &time);
//        SERIAL_ReturnToCarriage();
//    }
//    // controllo la sveglia
    //alarm.updateAlarm(&time);
    // Pulisco la stringa seriale
    //strcls(cur_msg, 20);
    // Normalizzo la posizione del cursore
    normalize(&cursor);
    lcd.blink();
    // Imposto la posizione allo schermo
    lcd.setCursor(cursor.x, cursor.y);
//    // Aggiorno i pulsanti
    KEYPAD_CheckButtonsPressed(&cursor, windows->get(windows->getCurrent()), &right, &left, &up, &down, &select, &alarm_in, &lights_in, info.enable_serial_debug);
#ifdef DEBUG_MOD
    SERIAL_SendMessage("Valore potenziometro: ");
    SERIAL_SendMessage(analogRead(pins.potent_pin));
    SERIAL_ReturnToCarriage();
#endif
    delay(100);

}

#endif // CORE_MAIN_CPP


