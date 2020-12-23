
/*
Autore: Cavallo Gabriele
Versione: 1.1
Descrizione: Con funzioni per leggere e salvare una ora
*/
#ifndef TIME_CPP
#define TIME_CPP
// Header
#include <Arduino.h>

#include "../Utils/StringUtils.cpp"
#include <RTClib.h>
#include <TimeDate.h>

/// Legge l'ora corrente dall' rtc e la converte in una instanza di timedate
static void readTime(TimeDate *res, RTC_DS1307 *rtc) {
	// Prendo l'rtc e salvo l'ora attuale
	DateTime now = rtc->now();
	// Uso la funzione integrata
	res->setHour(now.hour());
	res->setMinute(now.minute());
	res->setSecond(now.second());

	res->setDay(now.day());
	res->setMonth(now.month());
	res->setYear(now.year());
    res->setDayOfTheWeek(now.dayOfTheWeek());
}

#endif // TIME_CPP