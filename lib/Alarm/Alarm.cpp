#include "Alarm.h"

Alarm::Alarm()
{
    //ctor
}

void Alarm::setStartHour(int val) {
    startTime->setHour(val);
    set = true;
}

void Alarm::setStartMinute(int val) {
    startTime->setMinute(val);
    set = true;
}


void Alarm::enable() {
    active = true;
}

void Alarm::disable() {
    active = false;
}

void Alarm::snooze(int minutes) {
    // Controllo che il tempo non sia nullo
    if (startTime != nullptr) {
        // Incremento i minuti
        startTime->setMinute(startTime->getMinute() + minutes);
        // Riattivo l'allarme
        active = true;
    }
}

void Alarm::setSelective(bool val) {
    selective = val;
}

TimeDate* Alarm::getAlarm() {
    return startTime;
}

bool Alarm::updateAlarm(TimeDate* deviceTime) {
    // Controllo che il tempo del device e quello dell' allarme non siano vuoti
    if (deviceTime != nullptr && startTime != nullptr) {
        // Controllo che l'allarme sia attivo
        if (active) {
            // Controllo se i due orari sono uguali
            if (deviceTime->isEqual(startTime)) {
                // Chiamo il gestore
                if (!just_happened) {
                    handle();
                    just_happened = true;
                }
                
            }
            else {
                just_happened = false;
            }
        }
    }
}

bool Alarm::hasTime() {
    // Controllo che il tempo di inizio non sia nullptr
    if (set) {
        // Ho un orario
        // Restituisco true
        return true;
    }
    else {
        // Non ho un orario
        return false;
    }
}

void Alarm::setActive(bool val) {
    active = val;
}
    
bool Alarm::getState() {
    return active;
}

void Alarm::setHandler(void (*h)()) {
    handle = h;
}

void Alarm::setLight(bool val) {
    light = val;
}

void Alarm::setRadio(bool val) {
    radio = val;
}


