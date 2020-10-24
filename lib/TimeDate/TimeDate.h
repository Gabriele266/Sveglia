#ifndef TIMEDATE_H
#define TIMEDATE_H

#include <RTClib.h>


/// Rappresenta il giorno della settimana
enum Days{
    Lunedi,
    Martedi,
    Mercoledi,
    Giovedi,
    Venerdi,
    Sabato,
    Domenica
};

/// Rappresenta un orario e una data
class TimeDate
{
    public:
        /** Default constructor */
        TimeDate();
        TimeDate (int hh, int mm, int ss, int dd, int mt, int yy);
        /// Imposta le ore
        void setHour(int val){hour = val;}
        /// Imposta i minuti
        void setMinute(int val){minute = val;}
        /// Imposta i secondi
        void setSecond(int val){second = val;}
        /// Imposta il giorno
        void setDay(int val){day = val;}
        /// Imposta il mese
        void setMonth(int val){month = val;}
        /// Imposta l'anno
        void setYear(int val){year = val;}

        void setDayOfTheWeek(int val) { day_of_the_week = val; }

        /// Restituisce le ore
        unsigned int getHour(){return hour;}
        /// Restituisce i minuti
        unsigned int getMinute(){return minute;}
        /// Restituisce i secondi
        unsigned int getSecond(){return second;}
        /// Restituisce i giorni
        unsigned int getDay(){return day;}
        /// Restituisce i mesi
        unsigned int getMonth(){return month;}
        /// Restituisce l' anno
        unsigned int getYear(){return year;}


        /// Restituisce true se i due orari sono uguali
        bool isEqual(TimeDate *time);
        /// Legge e salva l'ora corrente a partire da quella espressa da un rtc
        void getByRtc(DateTime dt);

        /// Restituisce l'orario formattato
        void getFormTime(char res[], bool show_sec = false);
        /// Restituisce la data formattata
        void getFormDate(char res[], bool show_sec = false);

        /// Restituisce il nome del giorno della settimana
        char* getDayOfTheWeek(bool strict = true);

    protected:

    private:
        // Ore
        unsigned int hour;
        // Minuti
        unsigned int minute;
        // Secondi
        unsigned int second;
        unsigned int day;
        unsigned int month;
        unsigned int year;
        // Giorno della settimana
        unsigned int day_of_the_week = 0;
};

#endif // TIMEDATE_H
