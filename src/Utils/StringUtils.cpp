/*
* Autore: Cavallo Gabriele
* Versione: 1.1
* Descrizione: Insieme di funzionalit� utili per le stringhe
* Progetto: Sveglia Arduino
*
*/

#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

// Header di Arduino
#include <Arduino.h>
// Libreria per l'utilizzo delle schede sd
// Libreria per la comunicazione spi
#include <SPI.h>
// Libreria per il seriale
#include "../Serial/update.cpp"
// Header per gli errori
#include <ArduWin.h>
// Header per i pin
#include "../Main/PinDefs.cpp"

/// Data una stringa source e un divisore div restituisce la divisione della stessa
static char** strsplit(char div, char source[]){
//    // Lunghezza della sogente
//    int len = strlen(source);
//    // Contatore del numero di stringhe in risultato
//    int strings = 0;
//    // Contatore della posizione del nuovo carattere in ogni stringa
//    int char_pos = 0;
//    char array_res[30][4];
//    for(int cur = 0; cur < len; cur++){
//        // Il carattere corrente e' il divisore
//        if(source[cur] == div){
//            strings++;
//            char_pos = 0;
//        }
//        else{
//            array_res[char_pos][strings] = source[cur];
//            char_pos++;
//        }
//    }
//    return array_res;
}

/// Restituisce la sottostringa di una stringa dalla posizione start fino alla fine
static char* strsub(char str[], int start){
    int resDim = strlen(str)- start;
    char res[resDim];
    for(int x = 0; x < resDim; x++){
        res[x] = str[x+start];
    }
    return res;
}

/// Toglie tutti gli spazi da una stringa
static void strrems(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

static void strsplit(char str[]){
    for(int c = 0; c < strlen(str); c++){
        SERIAL_SendMessage("Pos ");
        SERIAL_SendMessage(c);
        SERIAL_SendMessage(":-");
        SERIAL_Write(str[c]);
        SERIAL_SendMessage("-");
        SERIAL_ReturnToCarriage();
    }
}

static int convertAnalogPinToInt(char pinName[]){
    strrems(pinName);
    if(strncmp(pinName, "A0", 2) == 0){
        return A0;
    }
    else if(strncmp(pinName, "A1", 2) == 0){
      // Controllo se � un numero > di 10
      if(strncmp(pinName, "A10", 3) == 0){
          return A10;
      }
      else if(strncmp(pinName, "A11", 3) == 0){
          return A11;
      }
      else if(strncmp(pinName, "A12", 3) == 0){
          return A12;
      }
      else if(strncmp(pinName, "A13", 3) == 0){
          return A13;
      }
      else{
        return A1;
      }
    }
    else if(strncmp(pinName, "A2", 2) == 0){
        return A2;
    }
    else if(strncmp(pinName, "A3", 2) == 0){
        return A3;
    }
    else if(strncmp(pinName, "A4", 2) == 0){
        return A4;
    }
    else if(strncmp(pinName, "A5", 2) == 0){
        return A5;
    }
    else if(strncmp(pinName, "A6", 2) == 0){
        return A6;
    }
    else if(strncmp(pinName, "A7", 2) == 0){
        return A7;
    }
    else if(strncmp(pinName, "A8", 2) == 0){
        return A8;
    }
    else if(strncmp(pinName, "A9", 2) == 0){
        return A9;
    }
}

static char* convertAnalogToString(int pin){
    switch (pin){
    case A0:
        return "A0";
        break;
    case A1:
        return "A1";
        break;
    case A2:
        return "A2";
        break;
    case A3:
        return "A3";
        break;
    case A4:
        return "A4";
        break;
    case A5:
        return "A5";
        break;
    case A6:
        return "A6";
        break;
    case A7:
        return "A7";
        break;
    case A8:
        return "A8";
        break;
    case A9:
        return "A9";
        break;
    case A10:
        return "A10";
        break;
    case A11:
        return "A11";
        break;
    case A12:
        return "A12";
        break;
    case A13:
        return "A13";
        break;
    }
}

/// Pulisce una stringa date le dimensioni
static void strcls(char str[], int dim){
    for(int x = 0; x < 20; x++){
      str[x] = NULL;
    }
}

static char* intToArr(int val){
    char *res;
    // Converto il valore
    itoa(val, res, 10);
    // Restituisco la stringa
    return res;
}

static void intToArray(int val, char *v, bool keepTwo = true){
    itoa(val, v, 10);
    if(strlen(v) == 1){
        // aggiungo un carattere al secondo elemento
        v[1] = ' ';
    }
}

/// Data una stringa line in entrata la divide in base ad un separatore in nome:valore
static void splitParameter(char line[], char *par_name, char *par_val, char div){

}

#endif // STRING_UTILS_CPP
