/*
* Autore:
* Versione:
* Descrizione:
* Progetto:
*
*/

#ifndef STORAGE_INIT_CPP
#define STORAGE_INIT_CPP

// Header di Arduino
#include <Arduino.h>
// Libreria per l'utilizzo delle schede sd
#include <SD.h>
// Sorgente con le modalità di esecuzione
#include "../mode.cpp"
// Libreria per la comunicazione spi
#include <SPI.h>
// Libreria per il seriale
#include "../Serial/update.cpp"
// Header per gli errori
#include <ArduWin.h>
// Header per i pin
#include "../Main/PinDefs.cpp"
#include "../Utils/StringUtils.cpp"

/// Effettua l'inizializzazione della scheda sd
static bool STORAGE_InitSd(unsigned int cs_pin){
        // Il pin esiste
        #ifdef DEBUG_MODE
        SERIAL_SendMessage("Avvio inizializzazione scheda sd per storage avviato: " endl);
        SERIAL_SendMessage("Pin utilizzato per l'inizializzazione: ");
        SERIAL_SendMessage(cs_pin);
        SERIAL_ReturnToCarriage();
        #endif
        // Controllo l'avvio
        if(!SD.begin(cs_pin)){
        #ifdef DEBUG_MODE
            // La scheda sd non si e' avviata
            SERIAL_SendMessage(F("Impossibile inizializzare la scheda sd per l'utilizzo. Controllare il cablaggio e che sia effettivamente inserita una scheda. " endl));
            SERIAL_SendMessage(F("Tutte le funzionalit� legate alla scheda sd verranno disabilitate. Attenzione: il dispositivo non funzionera' correttamente." endl));
        #endif
            return false;
        }
        else{
            SERIAL_SendMessage(F("Inizializzazione scheda sd avvenuta con successo. " endl));
            return true;
        }
        return false;
}

/// Effettua la lettura dei pin dalla scheda sd e li salva
static GError STORAGE_ReadPinConfig(project_pins *pins, File pinnouts_file){
    #ifdef DEBUG_MODE
    SERIAL_SendMessage(endl "Avvio ricerca pin su memoria sd." endl);
    #endif
    // Apro il file
        pinnouts_file = SD.open("PINS.TXT");
        // Controllo che sia aperto
        if(pinnouts_file){
            // Buffer per la linea corrente
            char line_buffer[20];

            // Carattere corrente
            char curchar;

            // Contatore della posizione nella linea corrente
            int cont = 0;
            // Contatore delle righe
            int lines = 1;
#ifdef DEBUG_MODE
            SERIAL_ReturnToCarriage();
            // Invio le informazioni aggiuntive sul file
            SERIAL_SendMessage("Dimensioni file PINS.TXT: ");
            SERIAL_SendMessage(pinnouts_file.size());
            SERIAL_SendMessage(" byte" endl);
            // Creo una tabella
            SERIAL_SendMessage("Nome" tab tab "Valore" tab tab tab "Riga" tab tab "Dimensione" tab tab "Divisione parametro" endl);
#endif
            // Leggo il file
            while(pinnouts_file.available() > 0){
                // Leggo un nuovo carattere e lo aggiungo alla linea
                curchar = (char) pinnouts_file.read();
#ifdef DEBUG_MODE
                SERIAL_SendMessage("Carattere corrente letto dal file: ");
                SERIAL_SendMessage(curchar);
                SERIAL_SendMessage(endl);
#endif
                // Controllo se e' un terminatore di linea
                if(curchar == '\n'){
                    // E' terminata la linea
                    // Incremento il numero di righe
                    lines ++;
                    // Resetto il contatore
                    cont = 0;
                    // Scrivo la riga
                    // Controllo che la linea corrente non sia un commento
                    if(!(line_buffer[0] == '#' && line_buffer[1] == '#')){
                        // Salvo il backup della istruzione
                        // Nome del parametro corrente
                        char *param_name;
                        // Valore del parametro corrente
                        char *param_val;
                        // Puntatore all' array del buffer
                        char *buf = line_buffer;

                        // Estraggo il nome del parametro
                        param_name = strtok_r(buf, ":", &buf);

                        // Estraggo il valore del parametro
                        param_val = strtok_r(buf, ":", &buf);
                        // Tolgo gli spazi
                        strrems(param_val);

                        strrems(param_name);

#ifdef DEBUG_MODE
                        // Completo la tabella
                        SERIAL_SendMessage(param_name);
                        SERIAL_Tabulate();
                        SERIAL_Tabulate();
                        SERIAL_SendMessage(param_val);
                        SERIAL_Tabulate();

                        SERIAL_SendMessage(lines);
                        SERIAL_Tabulate();
                        SERIAL_Tabulate();
                        SERIAL_Tabulate();
                        SERIAL_SendMessage(strlen(param_val));
                        SERIAL_Tabulate();
                        SERIAL_Tabulate();
                        strsplit(param_val);
                        SERIAL_ReturnToCarriage();
#endif
                        // Salvo i valori nelle variabili
                        if((strcmp(param_name, "ir-pin")) == 0){
                            // Salvo il pin
                            pins->ir_pin = atoi(param_val);
                        }
                        else if((strcmp(param_name, "right-btn-pin")) == 0){
                            // Notifico sul seriale

                            // Ottengo il valore
                            pins->right_btn_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "left-btn-pin")) == 0){
                                // Notifico sul seriale

                            // Ottengo il valore
                            pins->left_btn_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "up-btn-pin")) == 0){
                            // Notifico sul seriale

                            // Ottengo il valore
                            pins->up_btn_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "down-btn-pin")) == 0){
                            // Notifico sul serial

                            // Ottengo il valore
                            pins->down_btn_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "select-btn-pin")) == 0){
                            // Notifico sul seriale

                            // Ottengo il valore
                            pins->select_btn_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "potentiometer")) == 0){
                            // Notifico sul seriale

                            // Ottengo il valore
                            pins->potent_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "alarm-input")) == 0){
                            // Ottengo il valore
                            pins->alarm_input_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "light-btn")) == 0){
                            // Notifico sul seriale

                            // Ottengo il valore
                            pins->lights_pin = convertAnalogPinToInt(param_val);
                        }
                        else if((strcmp(param_name, "white-led-pin")) == 0){
                            pins->big_light_pin = atoi(param_val);
                        }
                        else if((strcmp(param_name, "yellow-led-pin")) == 0){
                            pins->reading_light_pin = atoi(param_val);
                        }
                        else if((strcmp(param_name, "relay-pin")) == 0){
                            pins->relay_pin = atoi(param_val);
                        }

                        // Svuoto le variabili
                        for(int x = 0; x < strlen(param_name); x++){
                            param_name[x] = ' ';
                        }
                        for(int x = 0; x < strlen(param_val); x++){
                            param_val[x] = ' ';
                        }
                    }
                    else{
                        //SERIAL_SendMessage("Rilevato commento. Non visualizzo");
                    }
                    // Resetto il buffer della riga
                    for(int x = 0; x < strlen(line_buffer); x++){
                        line_buffer[x] = ' ';
                    }
                }
                else{
                    // Aggiungo il carattere alla riga
                    line_buffer[cont] = curchar;
                    // Incremento il conatore
                    cont++;
                }
            }
            // Do l'informazione
            // Non c'� il file con le impostazioni dei pin
            GError info;
            info.setName("System file found.");
            info.setSender("STORAGE_ReadPinConfig");
            info.setLevel(ErrorLevel::Information);
            info.setHeader("File PINS.TXT  trovato. Sar� possibile utilizzare la sveglia.");
            info.increaseTimes();

            return info;
        }
        else{
#ifdef DEBUG_MODE
            SERIAL_SendMessage("Impossibile accedere al file di configurazione PINS.TXT" endl);
#endif
            // Non c'� il file con le impostazioni dei pin
            GError error;
            error.setName("System file not found.");
            error.setSender("STORAGE_ReadPinConfig");
            error.setLevel(ErrorLevel::Fatal);
            error.setHeader("File PINS.TXT non trovato. Sar� impossibile utilizzare la sveglia. Riavviare il dispositivo");
            error.increaseTimes();
            return error;
        }
}

#endif // STORAGE_INIT_CPP
