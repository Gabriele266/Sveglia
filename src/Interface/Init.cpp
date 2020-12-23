/**
*   \file Init.cpp
*	\author Gabriele Cavallo
*	\version 1.1
*	\brief File che contiene tutti gli oggetti della interfaccia (finestre e controlli grafici)
*   e fornisce funzioni per inizializzarli
*/

#ifndef INTERF_START
#define INTERF_START

// Header di arduino
#include <Arduino.h>
// Header per le interfaccie grafiche
#include <ArduWin.h>
// Header per lo schermo
#include <LiquidCrystal_I2C.h>
// Header per le icone di stato
#include "../../files/state_icons.h"
#include <avr/pgmspace.h>

/// Raccoglitore delle finestre per il progetto
static GWinList windows;

/// Finestra principale
static GWindow mainWin("mainWin", "Principale");
/// Finestra delle luci
static GWindow lightsWin("lightsWin", "Luci");
/// FInestra del tempo
static GWindow timesWin("timesWin", "Orario");
/// Finestra per ipostare il tempo
static GWindow alarmWin("alarmWin", "Sveglia");

/// Pulsante per visualizzare la finestra tempo
static GButton timeBtn("Tm");
/// Pulsante per la finestra lights
static GButton lightBtn("Lg");
/// Pulsante con le impostazioni
static GButton setBtn("St");

/// Etichetta per lo stato della scheda sd
static GLabel sdState("");
/// Etichetta per lo stato dell' rtc
static GLabel rtcState("");
/// Etichetta per lo stato dell' allarme
static GLabel alrmState("");
/// Icona per la sd
static GIcon sdIcon("sdIcon", sd_ok_icon, 4);
/// Icona per l' rtc
static GIcon rtcIcon("rtcIcon", clock_ok_icon, 5);
/// Icona per la sveglia
static GIcon alarmIcon("alarmIcon", alarm_active_icon, 6);

/// Etichetta stato luce lettura
static GLabel readLightState("Lettura: ");
/// Etichetta stato della luce da vista
static GLabel seeLightState("Vista: ");

/// Pulsante per impostare lo stato della luce da lettura
static GButton setReadLight("|off|");
/// Pulsante per impostare lo stato della luce da vista
static GButton setSeeLight("|off|");

/// Etichetta che visualizza l'ora
static GLabel timeLabel("0");
/// Etichetta che visualizza la data
static GLabel dateLabel("0");
/// Etichetta che mostra il nome del giorno
static GLabel dayLabel("Non");

/// Box per indicare se accendere la luce alla sveglia o no
static GCheckBox lightBox("Luce", createLocation(1,2));
/// Box per indicare se avviare la radio alla sveglia o usare un file di musica
static GCheckBox radioBox("Radio", createLocation(1, 3));
/// Box per indicare se la sveglia sar� settimanale o scolastica
static GCheckBox settimanalBox("Sett", createLocation(1, 1));

/// Etichetta che mostra lo stato dell' allarme
static GLabel alarmInd("Sveglia: ");
/// Pulsante per impostare lo stato dell' allarme
static GButton alarmState("|off|");

/// Pulsante per impostare le ore
static GButton hourAlSet( "0");
/// Pulsante per impostare i minuti
static GButton minuteAlSet( "0");
/// Etichetta per fare il separatore
static GLabel separator(":");
/// Pulsante per impostare l'allarme
static GButton okAlBtn ("|Vai|");
/// Etichetta Attivo
static GLabel activeLabel("Alle:");
/// Pulsante per visualizzare le informazioni dell' allarme
static GButton alarmInfo( "|Info|");

/// Icona a forma di orologio
static GIcon icn;
/// Icona a forma di luce
static GIcon light;
/// Icona delle impostazioni
static GIcon settings;

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
 \brief    Funzione core_manage_show_time_win, gestisce la visualizzazione della finestra tempo.
* \details  Viene chiamata dal controllore generale di mainWin oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_time_win(GEvent *event){
    windows.draw("timesWin");
    delete event;
}

/**
* \brief    Funzione core_manage_show_main_win, gestisce la visualizzazione della finestra principale.
* \details  Viene chiamata dal controllore generale oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_main_win(GEvent *event){
    windows.drawMain();
    delete event;
}

/**
* \brief    Funzione core_manage_show_lights_win, gestisce la visualizzazione della finestra luci.
* \details  Viene chiamata dal controllore generale di mainWin oppure dai comandi seriali
* \param [event] event contiene le informazioni legate all' evento
*/
static void core_manage_show_lights_win(GEvent *event){
    windows.draw("lightsWin");
    delete event;
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
static void initMainWindow(LiquidCrystal_I2C *surface){
    // Inizializzo la finestrra principale
    // Imposto la superficie
    mainWin.setSurface(surface);
    // disAttivo la visualizzazione del pulsante indietro
    mainWin.setShowBackBtn(false);
    // Creo una icona e un pulsante
    icn.setCode(clock_icon);
    icn.setIndex(0);
    timeBtn.setSurface(surface);
    timeBtn.setIcon(&icn);
    timeBtn.enable();

    timeBtn.setLocation(createLocation(2,2));
    timeBtn.setEventHandler(core_manage_show_time_win);
    timeBtn.begin();

    // Imposto la posizione
    lightBtn.setLocation(createLocation(7,2));
    lightBtn.setSurface(surface);
    // Creo una icona
    light.setCode(light_icon);
    light.setIndex(1);
    // Aggiungo l'icona
    lightBtn.setIcon(&light);
    lightBtn.enable();
    lightBtn.setEventHandler(core_manage_show_lights_win);
    lightBtn.begin();

    // Creo l'icona
    settings.setCode(settings_icon);
    settings.setIndex(2);

    // Formatto il pulsante impostazioni
    setBtn.setSurface(surface);
    setBtn.setLocation(createLocation(13, 2));
    // Aggiungo l'icona
    setBtn.setIcon(&settings);
    setBtn.enable();
    setBtn.begin();

    // Formatto gli indicatori di stato della sveglia
    sdState.setSurface(surface);
    sdState.setLocation(createLocation(16, 3));
    // Creo l'icona della scheda sd
    sdState.setIcon(&sdIcon);
    sdState.begin();
    sdState.hide();

    rtcState.setSurface(surface);
    rtcState.setLocation(createLocation(17, 3));
    rtcState.setIcon(&rtcIcon);
    rtcState.begin();
    rtcState.hide();

    alrmState.setSurface(surface);
    alrmState.setLocation(createLocation(18, 3));
    alrmState.setIcon(&alarmIcon);
    alrmState.begin();
    alrmState.hide();

    // Aggiungo i controlli
    mainWin.add(&timeBtn);
    mainWin.add(&lightBtn);
    mainWin.add(&setBtn);
    mainWin.add(&sdState);
    mainWin.add(&rtcState);
    mainWin.add(&alrmState);

    // Aggiungo la finestra main a windows
    windows.addMain(&mainWin);
}

/**
 * \brief Inizializza la finestra per le luci, ne crea e aggiunge i controlli
 * @param surf superficie su cui disegnare
 * @param bigLight Gestore per il cambiamenteo di stato della luce grossa
 * @param readLight Gestore per il cambiamenteo di stato della luce da lettura
 * @param seeLight Gestore per il cambiamento di stato della luce da vista
 */
static void initLightWindow(LiquidCrystal_I2C *surf, void (*readLight)(GEvent*), void (*seeLight)(GEvent*)){
    // Imposto la superficie
    lightsWin.setSurface(surf);
    // Imposto il pulsante indietro
    lightsWin.setBackBtnPos(BackBtnPos::TopLeft);
    lightsWin.setBackBtnType(BackBtnType::Medium);
    lightsWin.setShowBackBtn(true);
    // Imposto il gestore per il pulsante indietro
    lightsWin.setBackBtnHandle(core_manage_show_main_win);

    // Inizializzo l' indicatore della luce da lettura:
    // Imposto la superficie
    readLightState.setSurface(surf);
    // Imposto la posizione
    readLightState.setLocation(createLocation(3, 2));

    // Aggiungo alla finestra
    lightsWin.add(&readLightState);

    // Inizializzo il pulsante per la luce da lettura
    // Imposto la surface
    setReadLight.setSurface(surf);
    // Imposto la posizione
    setReadLight.setLocation(createLocation(14, 2));
    // Imposto il gestore degli eventi
    setReadLight.setEventHandler(readLight);

    lightsWin.add(&setReadLight);

    // Imposto l'etichetta della luce da vista
    seeLightState.setSurface(surf);
    seeLightState.setLocation(createLocation(3,3));

    // Aggiungo il controllo
    lightsWin.add(&seeLightState);

    // Imposto il pulsante per invertire lo stato della luce da vista
    // Imposto la superficie
    setSeeLight.setSurface(surf);
    // Imposto la posizione
    setSeeLight.setLocation(createLocation(14,3));
    // Imposto il gestore
    setSeeLight.setEventHandler(seeLight);

    // Aggiungo l'elemento
    lightsWin.add(&setSeeLight);
    //Aggingo la finestra alla raccolta
    windows.add(&lightsWin);
}

/// Inizializza la finestra tempo
static void initTimesWindow(LiquidCrystal_I2C *surf, void (*alarmSet)(GEvent *event), void (*onWinDraw)(GEvent*), void (*alarmInfoRequest)(GEvent *)){
    // Imposto la superficie
    timesWin.setSurface(surf);
    // Imposto il pulsante indietro
    timesWin.setBackBtnPos(BackBtnPos::TopLeft);
    timesWin.setBackBtnType(BackBtnType::Medium);
    timesWin.setShowBackBtn(true);
    // Imposto il gestore
    timesWin.setBackBtnHandle(core_manage_show_main_win);
    timesWin.setOnDrawFunction(onWinDraw);
    // Imposto l'etichetta che mostra l'ora
    timeLabel.setSurface(surf);
    timeLabel.setIcon(nullptr);
    timeLabel.setLocation(createLocation(1, 1));

    // Aggiungo l'icona alla finestra
    timesWin.add(&timeLabel);

    // Inizializzo l'etichetta per la data
    dateLabel.setSurface(surf);
    dateLabel.setIcon(nullptr);
    dateLabel.setLocation(createLocation(8, 1));

//     Aggiungo l'etichetta alla finestra
    timesWin.add(&dateLabel);

    // Inizializzo l'etcihetta per il giorno
    dayLabel.setSurface(surf);
    dayLabel.setLocation(createLocation(16,0));
    dayLabel.setIcon(nullptr);

    timesWin.add(&dayLabel);

    // Formatto l'indicatore dello stato dell' allarme
    alarmInd.setSurface(surf);
    alarmInd.setLocation(createLocation(1,2));
    alarmInd.setIcon(nullptr);
    // Inizializzo l'etichetta
    alarmInd.begin();
    // Aggiungo il controllo
    timesWin.add(&alarmInd);

    // Formatto il pulsante per lo stato
    alarmState.setSurface(surf);
    alarmState.setLocation(createLocation(10,2));
    alarmState.setIcon(nullptr);
    alarmState.setEventHandler(alarmSet);
    alarmState.enable();

    alarmInfo.setSurface(surf);
    alarmInfo.setLocation(createLocation(14, 3));
    alarmInfo.setIcon(nullptr);
    alarmInfo.setEventHandler(alarmInfoRequest);
    alarmInfo.disable();

    // Aggiungo
    timesWin.add(&alarmState);
    timesWin.add(&alarmInfo);

    // Aggiungo la finestra al raccoglitore
    windows.add(&timesWin);
}

/// Inizializza la finestra per l'impostazione dell' allarme
static void initAlarmWindow(LiquidCrystal_I2C *surf, void (*hour_func)(GEvent *event), void (*minute_fun)(GEvent *event), void (*save_fun)(GEvent *event)){
    // Imposto la superficie della finestra
    alarmWin.setSurface(surf);
    // Formatto il pulsante indietro
    alarmWin.setBackBtnPos(BackBtnPos::TopLeft);
    alarmWin.setShowBackBtn(true);
    alarmWin.setBackBtnType(BackBtnType::Medium);
    alarmWin.setBackBtnHandle(core_manage_show_time_win);

    activeLabel.setSurface(surf);
    activeLabel.setLocation(createLocation(8, 1));
    activeLabel.setIcon(nullptr);

    // Formatto i pulsanti per impostare l'orario della sveglia
    hourAlSet.setSurface(surf);
    hourAlSet.setLocation(createLocation(10, 2));
    hourAlSet.setEventHandler(hour_func);
    hourAlSet.setIcon(nullptr);

    minuteAlSet.setSurface(surf);
    minuteAlSet.setLocation(createLocation(13, 2));
    minuteAlSet.setEventHandler(minute_fun);
    minuteAlSet.setIcon(nullptr);

    okAlBtn.setSurface(surf);
    okAlBtn.setLocation(createLocation(14, 3));
    okAlBtn.setEventHandler(save_fun);

    // Formatto il separatore
    separator.setSurface(surf);
    separator.setLocation(createLocation(12, 2));

    // Aggiungo un hh:mm per visualizzare l'orario corrente
    alarmWin.add(&timeLabel);

    alarmWin.add(&activeLabel);
    alarmWin.add(&hourAlSet);
    alarmWin.add(&minuteAlSet);
    alarmWin.add(&separator);
    alarmWin.add(&okAlBtn);

    // Aggiungo al gestore delle finestre
    windows.add(&alarmWin);
}

#endif // INTERF_START
