/*
* Autore:
* Versione:
* Descrizione:
* Progetto:
*
*/
#ifndef TIMEDATE_CPP
#define TIMEDATE_CPP

#include "TimeDate.h"
TimeDate::TimeDate()
{
    //ctor
	hour = 0;
	minute = 0;
	second = 0;
	day = 0;
	month = 0;
	year = 0;
}

TimeDate::TimeDate(int hh, int mm, int ss, int dd, int mt, int yy){
    hour = hh;
    minute = mm;
    second = ss;
    day = dd;
    month = mt;
    year = yy;
}

bool TimeDate::isEqual(TimeDate *time){
    if(hour == time->getHour()&& minute == time->getMinute()
       ){
        // Sono uguali
        return true;
    }
    else{
        return false;
    }
}

void TimeDate::getByRtc(DateTime dt){
    hour = (int) dt.hour();
    minute = (int) dt.minute();
    second = (int) dt.second();
    day = (int) dt.day();
    month = (int) dt.month();
    year = (int) dt.year();
    // Leggo il giorno della settimana
    day_of_the_week = dt.dayOfTheWeek();
}

void TimeDate::getFormTime(char res[], bool show_sec = false){
	// COntiene il risultato
	char buf[5];
	char buf_2[5];
	char buf_3[5];

	// Metto le ore
	itoa(getHour(), buf, 10);
	itoa(getMinute(), buf_2, 10);
	//itoa(getSecond(), buf_3, 10);

	strcpy(res, buf);
	strcat(res, ":");
	strcat(res, buf_2);
	if (show_sec) {
        // Aggiungo i secondi
		strcat(res, ":");
		//strcat(res, buf_3);
	}
	
}

void TimeDate::getFormDate(char res[11], bool show_sec = false) {
	// COntiene il risultato
	char buf[5];
	char buf_2[5];
	char buf_3[5];

	// Metto le ore
	itoa(getDay(), buf, 10);
	itoa(getMonth(), buf_2, 10);
	itoa(getYear(), buf_3, 10);

	strcpy(res, buf);
	strcat(res, "/");
	strcat(res, buf_2);

	// Aggiungo i secondi
	strcat(res, "/");
	strcat(res, buf_3);
	
}

char* TimeDate::getDayOfTheWeek(bool strict = true) {
	if (strict) {
		switch (day_of_the_week) {
		case 0:
			return "Dom";
		case 1:
			return "Lun";
		case 2:
			return "Mar";
		case 3:
			return "Mer";
		case 4:
			return "Gio";
		case 5:
			return "Ven";
		case 6:
			return "Sab";
		};
	}
	else {
		switch (day_of_the_week) {
		case 0:
			return "Domenica";
		case 1:
			return "Lunedì";
		case 2:
			return "Martedì";
		case 3:
			return "Mercoledì";
		case 4:
			return "Giovedì";
		case 5:
			return "Venerdì";
		case 6:
			return "Sabato";
		};
	}
}

#endif