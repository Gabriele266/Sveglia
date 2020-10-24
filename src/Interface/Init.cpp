/**
*   \file Init.cpp
*	\author Gabriele Cavallo
*	\version 1.1
*	\brief File che contiene tutti gli oggetti della interfaccia (finestre e controlli grafici)
*   e fornisce funzioni per inizializzarli
*/

#ifndef INTERF_START
#define INTERF_START

// Header pubblici
// Header della interfaccia
#include "Interface.cpp"
// Header di arduino
#include <Arduino.h>
// Header per le interfaccie grafiche
#include "../../lib/ArduWin/ArduWin.h"
// Header per lo schermo
#include "../../lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
// Header per il seriale
#include "../Serial/update.cpp"

/// Raccoglitore delle finestre per il progetto
static GWinList *windows = new GWinList("windows");

/// Finestra principale
static GWindow *mainWin = new GWindow("mainWin", "Principale");
/// Finestra delle luci
static GWindow *lightsWin = new GWindow("lightsWin", "Luci");
/// FInestra del tempo
static GWindow *timesWin = new GWindow("timesWin", "Orario");
/// Finestra per ipostare il tempo
static GWindow *alarmWin = new GWindow("alarmWin", "Sveglia");

/// Pulsante per visualizzare la finestra tempo
static GButton *timeBtn = new GButton("timeBtn", "Tm");
/// Pulsante per la finestra lights
static GButton *lightBtn = new GButton("lightBtn", "Lg");
/// Pulsante con le impostazioni
static GButton *setBtn = new GButton("setBtn", "St");

/// Etichetta stato luci grossa
static GLabel *bigLightState = new GLabel("bglightState", "Ambiente: ");
/// Etichetta stato luce lettura
static GLabel *readLightState = new GLabel("readLightState", "Lettura: ");
/// Etichetta stato della luce da vista
static GLabel *seeLightState = new GLabel("seeLightState", "Vista: ");


/// Pulsante per impostare lo stato della luce grossa
static GButton *setBigLight = new GButton("setbgState", "|off|");
/// Pulsante per impostare lo stato della luce da lettura
static GButton *setReadLight = new GButton("setReadLight", "|off|");
/// Pulsante per impostare lo stato della luce da vista
static GButton *setSeeLight = new GButton("setSeeLight", "|off|");

/// Etichetta che visualizza l'ora
static GLabel *timeLabel = new GLabel("timeLabel", "00:00");
/// Etichetta che visualizza la data
static GLabel *dateLabel = new GLabel("dateLabel", "00/00/00");
/// Etichetta che mostra il nome del giorno
static GLabel *dayLabel = new GLabel("dayLabel", "Non");

/// Box per indicare se accendere la luce alla sveglia o no
static GCheckBox *lightBox = new GCheckBox("lightBox", "Luce", createLocation(1,2));
/// Box per indicare se avviare la radio alla sveglia o usare un file di musica
static GCheckBox *radioBox = new GCheckBox("radioBox", "Radio", createLocation(1, 3));
/// Box per indicare se la sveglia sar� settimanale o scolastica
static GCheckBox *settimanalBox = new GCheckBox("settimanalBox", "Sett", createLocation(1, 1));

/// Etichetta che mostra lo stato dell' allarme
static GLabel *alarmInd = new GLabel("alarmInd", "Sveglia: ");
/// Pulsante per impostare lo stato dell' allarme
static GButton *alarmState = new GButton("alarmState", "|off|");

/// Pulsante per impostare le ore
static GButton *hourAlSet = new GButton("hourAlSet", "00");
/// Pulsante per impostare i minuti
static GButton *minuteAlSet = new GButton("minuteAlSet", "00");
/// Etichetta per fare il separatore
static GLabel *separator = new GLabel("separator", ":");
/// Pulsante per impostare l'allarme
static GButton *okAlBtn = new GButton("okAlBtn", "|Vai|");
/// Pulsante per visualizzare le informazioni dell' allarme
static GButton *showAlarm = new GButton("showAlarm", "|Visual|");
/// Posizione del cursore
static location cursor = createLocation();
/// notifica dopo l'impostazione della sveglia
static GNotification *notify = new GNotification();

/// Icona a forma di orologio
static GIcon *icn = new GIcon();
/// Icona a forma di luce
static GIcon *light = new GIcon();
/// Icona delle impostazioni
static GIcon *settings = new GIcon();

/// Icona a forma di ingranaggio
static byte settings_icon[8]{
     B00100,
     B01010,
     B10001,
     B10101,
     B10101,
     B10001,
     B01110,
     B00100
};

/// Icona a forma di luce
static byte light_icon[8]{
     B00000,
     B00000,
     B01010,
     B11111,
     B01110,
     B01110,
     B00100,
     B00100
};


// Handlers per l'interfaccia
#pragma regioname Handlers
/**
* \brief    Funzione core_manage_show_time_win, gestisce la visualizzazione della finestra tempo.
* \details  Viene chiamata dal controllore generale di mainWin oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_time_win(GEvent *event){
    SERIAL_SendMessage("Mostro finestra time");
    windows->draw("timesWin");
}

/**
* \brief    Funzione core_manage_show_main_win, gestisce la visualizzazione della finestra principale.
* \details  Viene chiamata dal controllore generale oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_main_win(GEvent *event){
    windows->drawMain();
}

/**
* \brief    Funzione core_manage_show_settings_win, gestisce la visualizzazione della finestra impostazioni.
* \details  Viene chiamata dal controllore generale di mainWin oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_settings_win(GEvent *event){
    //SERIAL_SendEventInfo(event);
}

/**
* \brief    Funzione core_manage_show_lights_win, gestisce la visualizzazione della finestra luci.
* \details  Viene chiamata dal controllore generale di mainWin oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_lights_win(GEvent *event){
    SERIAL_ReturnToCarriage();
    SERIAL_SendMessage("Premuto pulsante tempo");
    SERIAL_ReturnToCarriage();
    windows->draw("lightsWin");
}

#pragma endregion

/**
* \brief    Funzione INTERFACE_InitMainWin, inizializza la finestra principale
* \details  Crea tutti i controlli necessari, li formatta e li aggiunge alla finestra, inoltre
*   utilizza i gestori core_manage_show_time_win, core_manage_show_main_win, core_manage_show_settings_win, core_manage_show_lights_win per gestire gli eventi.
* Questa finestra funge da desktop per entrare nelle finestre tempo, allarme , luci etc... e gestire la sveglia.
* \param    [surface] surface contiene un puntatore allo schermo per poterlo assegnare ai vari controlli e permetterne il disegno.
* \return   Nessun valore restituito
*/
static void INTERFACE_InitMainWin(LiquidCrystal_I2C *surface){
    // Inizializzo la finestrra principale
    // Imposto il pulsante indietro
    mainWin->setBackBtnPos(BackBtnPos::TopLeft);
    mainWin->setBackBtnType(BackBtnType::Medium);
    // Imposto la superficie
    mainWin->setSurface(surface);
    // disAttivo la visualizzazione del pulsante indietro
    mainWin->setShowBackBtn(false);
    // Creo una icona e un pulsante

    icn->setCode(clock_icon);
    icn->setIndex(0);
    timeBtn->setSurface(surface);
    timeBtn->setIcon(icn);
    timeBtn->enable();

    timeBtn->setLocation(createLocation(2,2));
    timeBtn->setEventHandler(core_manage_show_time_win);
    timeBtn->begin();

    // Imposto la posizione
    lightBtn->setLocation(createLocation(7,2));
    lightBtn->setSurface(surface);
    // Creo una icona
    light->setCode(light_icon);
    light->setIndex(1);
    // Aggiungo l'icona
    lightBtn->setIcon(light);
    lightBtn->enable();
    lightBtn->setEventHandler(core_manage_show_lights_win);
    lightBtn->begin();

    // Creo l'icona
    settings->setCode(settings_icon);
    settings->setIndex(2);

    // Formatto il pulsante impostazioni
    setBtn->setSurface(surface);
    setBtn->setLocation(createLocation(13, 2));
    // Aggiungo l'icona
    setBtn->setIcon(settings);
    setBtn->enable();
    setBtn->begin();

    // Aggiungo i controlli
    mainWin->addControl(timeBtn);
    mainWin->addControl(lightBtn);
    mainWin->addControl(setBtn);

    // Aggiungo la finestra main a windows
    windows->setMain(windows->add(mainWin));
}

/**
* \brief    Funzione INTERFACE_InitLightWin, inizializza la finestra luci
* \details  Crea tutti i controlli necessari, li formatta e li aggiunge alla finestra, inoltre
*   utilizza i gestori passati come argomenti per gestire gli eventi.
* Questa finestra offre le funzionalit� per gestire le luci della sveglia, variandone lo stato
* \param    [surface] surface contiene un puntatore allo schermo per poterlo assegnare ai vari controlli e permetterne il disegno.
* \param    [bigLight] bigLight contiene un puntatore a una funzione in grado di gestire la variazione di stato della luce grossa.
* \param    [readLight] readLight contiene un puntatore a una funzione in grado di gestire la variazione di stato della luce da lettura
* \param    [seeLight] seeLight contiene un puntatore a una funzione in grado di gestire la variazione di stato della luce da vista
* \return   Nessun valore restituito
*/
static void INTERFACE_InitLightWin(LiquidCrystal_I2C *surf, void (*bigLight)(GEvent*), void (*readLight)(GEvent*), void (*seeLight)(GEvent*)){
    // Imposto la superficie
    lightsWin->setSurface(surf);
    // Imposto il pulsante indietro
    lightsWin->setBackBtnPos(BackBtnPos::TopLeft);
    lightsWin->setBackBtnType(BackBtnType::Medium);
    lightsWin->setShowBackBtn(true);
    // Creo l'etichetta per lo stato della luce grossa
    bigLightState->setLocation(createLocation(3,1));
    // Imposto la superficie
    bigLightState->setSurface(surf);
    bigLightState->setIcon(nullptr);

    // Aggiungo l'etichetta alla finestra
    lightsWin->addControl(bigLightState);

    // Imposto il pulsante per impostarne, visualizzarne lo stato
    setBigLight->setLocation(createLocation(14,1));
    // Imposto il gestore
    setBigLight->setSurface(surf);
    setBigLight->setEventHandler(bigLight);

    // Aggiungo il pulsante
    lightsWin->addControl(setBigLight);
    lightsWin->setBackBtnHandle(core_manage_show_main_win);

    // Inizializzo l' indicatore della luce da lettura:
    // Imposto la superficie
    readLightState->setSurface(surf);
    // Imposto la posizione
    readLightState->setLocation(createLocation(3, 2));
    // Do icona nulla
    readLightState->setIcon(nullptr);

    // Aggiungo alla finestra
    lightsWin->addControl(readLightState);

    // Inizializzo il pulsante per lo stato
    setReadLight->setSurface(surf);
    setReadLight->setLocation(createLocation(14, 2));
    // Imposto il gestore degli eventi
    setReadLight->setEventHandler(readLight);

    lightsWin->addControl(setReadLight);

    // Imposto l'etichetta della luce da vista
    seeLightState->setSurface(surf);
    seeLightState->setLocation(createLocation(3,3));
    seeLightState->setIcon(nullptr);

    // Aggiungo il controllo
    lightsWin->addControl(seeLightState);

    // Imposto il pulsante per invertire lo stato della luce da vista
    setSeeLight->setSurface(surf);
    setSeeLight->setLocation(createLocation(14,3));
    // Imposto il gestore
    setSeeLight->setEventHandler(seeLight);

    // Aggiungo l'elemento
    lightsWin->addControl(setSeeLight);
    // Aggingo la finestra alla raccolta
    windows->add(lightsWin);
}

/// Inizializza la finestra tempo
static void INTERFACE_InitTimesWin(LiquidCrystal_I2C *surf, void (*alarmSet)(GEvent *event)){
    // Imposto la superficie
    timesWin->setSurface(surf);
    // Imposto il pulsante indietro
    timesWin->setBackBtnPos(BackBtnPos::TopLeft);
    timesWin->setBackBtnType(BackBtnType::Medium);
    timesWin->setShowBackBtn(true);
    // Imposto il gestore
    timesWin->setBackBtnHandle(core_manage_show_main_win);

    // Imposto l'etichetta che mostra l'ora
    timeLabel->setSurface(surf);
    timeLabel->setLocation(createLocation(1,1));
    timeLabel->setIcon(nullptr);

    // Aggiungo l'icona alla finestra
    timesWin->addControl(timeLabel);

    // Inizializzo l'etichetta per la data
    dateLabel->setSurface(surf);
    dateLabel->setLocation(createLocation(10,1));
    dateLabel->setIcon(nullptr);

    // Aggiungo l'etichetta alla finestra
    timesWin->addControl(dateLabel);

    // Inizializzo l'etcihetta per il giorno
    dayLabel->setSurface(surf);
    dayLabel->setLocation(createLocation(16,0));
    dayLabel->setIcon(nullptr);

    timesWin->addControl(dayLabel);

    // Formatto l'indicatore dello stato dell' allarme
    alarmInd->setSurface(surf);
    alarmInd->setLocation(createLocation(1,2));
    alarmInd->setIcon(nullptr);
    // Inizializzo l'etichetta
    alarmInd->begin();
    // Aggiungo il controllo
    timesWin->addControl(alarmInd);

    // Formatto il pulsante per lo stato
    alarmState->setSurface(surf);
    alarmState->setLocation(createLocation(10,2));
    alarmState->setIcon(nullptr);
    alarmState->setEventHandler(alarmSet);
    alarmState->enable();
    // Aggiungo
    timesWin->addControl(alarmState);

    // Aggiungo la finestra al raccoglitore
    windows->add(timesWin);
}

/// Inizializza la finestra per l'impostazione dell' allarme

static void INTERFACE_InitAlarmWin(LiquidCrystal_I2C *surf, void (*hour)(GEvent *event), void (*minute)(GEvent *event), void (*saveFun)(GEvent *event)){
    alarmWin->setSurface(surf);
    // Imposto il gestore degli eventi per il pulsante indietro
    alarmWin->setBackBtnPos(BackBtnPos::TopLeft);
    alarmWin->setBackBtnType(BackBtnType::Medium);
    alarmWin->setBackBtnHandle(core_manage_show_main_win);
    alarmWin->setShowBackBtn(true);
    // Aggiungo il primo controllo per l'impostazione delle ore
    hourAlSet->setSurface(surf);
    hourAlSet->setLocation(createLocation(12,1));
    hourAlSet->setIcon(nullptr);
    hourAlSet->setEventHandler(hour);

    // Aggiungo il controllo alla finestra
    alarmWin->addControl(hourAlSet);

    // Formatto la label con i :
    separator->setSurface(surf);
    separator->setLocation(createLocation(14, 1));
    separator->setIcon(nullptr);

    // Aggiungo il separatore
    alarmWin->addControl(separator);

    // Formatto il parametro minuti
    minuteAlSet->setSurface(surf);
    minuteAlSet->setLocation(createLocation(15,1));
    minuteAlSet->setIcon(nullptr);
    minuteAlSet->setEventHandler(minute);

    // Aggiungo alla finestra
    alarmWin->addControl(minuteAlSet);

    // Formatto il pulsante ok
    okAlBtn->setSurface(surf);
    // imposto il gestore
    okAlBtn->setEventHandler(saveFun);
    okAlBtn->setLocation(createLocation(13,3));
    okAlBtn->setIcon(nullptr);

    // Aggiungo alla finestra
    alarmWin->addControl(okAlBtn);

    // Inzializzo il box luce
    lightBox->setSurface(surf);
    lightBox->begin();
    lightBox->check();
    // Aggiungo il controllo alla finestra
    alarmWin->addControl(lightBox);

    // Imposto il box per la radio
    radioBox->setSurface(surf);
    radioBox->begin();
    radioBox->check();
    // formatto il pulsante per visuallizzare l allarme
    alarmWin->addControl(radioBox);

    settimanalBox->setSurface(surf);
    settimanalBox->begin();

    alarmWin->addControl(settimanalBox);

    windows->add(alarmWin);

}

#endif // INTERF_START
