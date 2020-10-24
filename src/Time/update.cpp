
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
#include "../../lib/RTClib/RTClib.h"
#include "../../lib/ArduWin/ArduWin.h"
#include "../../lib/TimeDate/TimeDate.h"

static void TIME_ReadTime(TimeDate *res, RTC_DS1307 *rtc) {
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



