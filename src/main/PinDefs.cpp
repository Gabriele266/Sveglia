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
    byte sd_cs_pin = 53;
    /// Pin della luce da lettura
    byte reading_light_pin = 3;
    /// Pin della luce da vista
    byte see_light_pin = 0;
    /// Pin del relay
    byte relay_pin = 5 ;
    /// Pin del modulo infrarossi
    byte ir_pin = 44;
    /// Pin del pulsante destro
    byte right_btn_pin = A12;
    /// Pin del pulsante sinistro
    byte left_btn_pin = A9;
    /// Pin del pulsante su
    byte up_btn_pin = A13;
    /// Pin del pulsante giu
    byte down_btn_pin = A10;
    /// Pin del pulsante select
    byte select_btn_pin = A6;
    /// Pin del potenziometro
    byte potent_pin = A11;
    /// Pin del pulsante allarme
    byte alarm_input_pin = A12;
    /// Pin del pulsante luci
    byte lights_pin = A8;
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
