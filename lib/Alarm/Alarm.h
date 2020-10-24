#ifndef ALARM_H
#define ALARM_H

#define ALARM_ACTIVE true
#define ALARM_DISABLED false

#include "F:\SyncFiles\Informatica\Arduino\libraries\TimeDate\TimeDate.h"

// Rappresenta una sveglia
class Alarm
{
    public:
        /** Default constructor */
        Alarm();
        /// Costruttore che accetta il tempo di avvio e lo stato
        Alarm(bool active);

        /// Imposta l'ora di avvio a partire da un intero
        void setStartHour(int val);

        /// Imposta il minuto di avvio
        void setStartMinute(int val);

        TimeDate* getAlarm();

        /// Attiva la sveglia
        void enable();

        /// Disattiva la sveglia
        void disable();

        /// Prospone la sveglia di un determinato lasso di minuti
        void snooze(int minutes);

        /// Controlla lo stato della sveglia
        bool updateAlarm(TimeDate* deviceTime);

        /// Imposta il parametro selective
        void setSelective(bool val);

        /// attiva o disattiva l'uso della radio
        void setRadio(bool val);

        /// attiva o disattiva la luce
        void setLight(bool val);

        bool getRadio() { return radio; }
        bool getLight() { return light; }
        bool getSelective() { return selective; }

        /// Restituisce lo stato della sveglia
        bool getState();

        /// Restituisce true se c'è un orario all' interno
        bool hasTime();

        /// Imposta il gestore degli eventi
        void setHandler(void (*handler)());

        /// Definisce se un allarme è attivo o no
        void setActive(bool val);

    protected:

    private:
        // Rappresenta l'orario di partenza della sveglia
        TimeDate* startTime = new TimeDate();

        // Rappresenta se la sveglia è selettiva o continua tutti i giorni
        bool selective;

        // Indica se la sveglia è attiva
        bool active = ALARM_DISABLED;

        bool set = false;

        // indica se accendere la luce
        bool light = true;

        // indica se accendere la radio o produrre un suono
        bool radio = true;

        // Punta ad un gestore dell' evento generato all' avvio della sveglia
        void (*handle)();

        // indica se l'allarme è appena avvenuto
        bool just_happened = false;
};

#endif // ALARM_H
