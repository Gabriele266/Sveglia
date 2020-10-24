#ifndef OUTPUT_REGISTER_H_INCLUDED
#define OUTPUT_REGISTER_H_INCLUDED

/*
    Autore: Cavallo Gabriele
    Registro con tutte le frasi date in output in base alle varie situazioni
*/
// Output quando si avvia la ricerca della scheda sd
static const  char sd_search_start[] = "Avvio inizializzazione scheda sd per storage avviato";
static const char bool_val_true[] = "true";
static const char bool_val_false[] = "false";
// Eventi
static const  char event_happened[] = "Evento verificato";
static const  char event_display_name[] = "Nome evento: ";
static const  char event_display_sender[] = "Sender evento: ";
static const  char event_display_location[] = "Posizione evento: ";

// Errori
static const  char error_display_sender[] = "Sender errore: ";
static const  char error_display_level[] = "Livello errore: ";
static const  char error_display_level_high[] = "HIGH";
static const  char error_display_level_fatal[] = "FATAL";
static const  char error_display_level_medium[] = "MEDIUM";
static const  char error_display_level_low[] = "LOW";
static const  char error_display_level_information[] = "INFORMATION";
static const  char error_display_successes[] = "Numero successi: ";
// Keypad
static const  char keypad_button_up[] = "Keypad UP";
static const  char keypad_button_down[] = "Keypad DOWN";
static const  char keypad_button_right[] = "Keypad RIGHT";
static const  char keypad_button_left[] = "Keypad LEFT";
static const  char keypad_button_select[] = "Keypad SEL";
static const  char keypad_button_potenz[] = "Keypad POT";
static const  char keypad_button_alarm[] = "Keypad ALRM";
static const  char keypad_button_light[] = "Keypad LGHT";

static const  char serial_separator[] = "===========================";

#endif // OUTPUT_REGISTER_H_INCLUDED
