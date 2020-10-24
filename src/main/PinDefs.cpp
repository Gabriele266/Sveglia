/*
* Autore:
* Versione:
* Descrizione:
* Progetto:
*
*/

#ifndef PINDEFS
#define PINDEFS

// Definizioni degli stati delle luci
#define LED_ON true
// Stato spento
#define LED_OFF false

#include <Arduino.h>

/// Contiene le definizioni di tutti i pin
struct project_pins{
    /// Pin per la scheda sd
    int sd_cs_pin = 53;
    /// Pin della luce grossa
    int big_light_pin = 0;
    /// Pin della luce da lettura
    int reading_light_pin = 3;
    /// Pin della luce da vista
    int see_light_pin = 0;
    /// Pin del relay
    int relay_pin = 5 ;
    /// Pin del modulo infrarossi
    int ir_pin = 44;
    /// Pin del pulsante destro
    int right_btn_pin = A7;
    /// Pin del pulsante sinistro
    int left_btn_pin = A11;
    /// Pin del pulsante su
    int up_btn_pin = A8;
    /// Pin del pulsante giu
    int down_btn_pin = A6;
    /// Pin del pulsante select
    int select_btn_pin = A13;
    /// Pin del potenziometro
    int potent_pin = A9;
    /// Pin del pulsante allarme
    int alarm_input_pin = A12;
    /// Pin del pulsante luci
    int lights_pin = A10;
};

/// Contiene le definizioni delle impostazioni
struct project_settings{
    /// Nome dell' utente
    char user_name[30] = "user";
    /// Definisce se salutare l'utente durante la sveglia
    bool greet_user = true;
    /// Definisce se abilitare il debug seriale del progetto
    bool enable_serial_debug = true;
    /// Stato della luce ambiente
    bool ambient_light_state = LED_OFF;
    /// Stato della luce da lettura
    bool read_light_state = LED_OFF;
    /// Stato della luce da vista
    bool see_light_state = LED_OFF;
    /// Stato della sd
    bool sd_success = false;
};
#endif // PINDEFS
