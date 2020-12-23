// Codice generato dal programma CharGenerator.
#ifndef STATE_ICONS
#define STATE_ICONS

#include <Arduino.h>

/// Rappresenta l'icona della scheda sd
static byte sd_ok_icon[8]{
     B00111,
     B01001,
     B01001,
     B10001,
     B10101,
     B10101,
     B10001,
     B11111
};

/// Rappresenta l'icona per l'rtc
static byte clock_ok_icon[8]{
        B00000,
        B01110,
        B10001,
        B10101,
        B10101,
        B10001,
        B01110,
        B00000
};

/// Rappresenta l'icona per la sveglia attiva
static byte alarm_active_icon[8]{
        B00000,
        B00000,
        B00100,
        B01010,
        B01010,
        B01110,
        B01010,
        B00000
};

#endif