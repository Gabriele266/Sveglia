/* File: serial.cpp
 Contiene le informazioni sul componente serial
 Autore: Cavallo Gabriele
 Data creazione: 15/12/2019
 Licenza: shareware
*/

// Versione del seriale
#define __SERIAL__VERSION__ "1.1"
// Descrizione del seriale
#define __SERIAL__DESCR__ "Seriale di comunicazione della sveglia"
// Baudrate preferito di comunicazione del seriale
#define __SERIAL_PREFERR_BAUDRATE__ 115200
// Definisce se sarà necessario leggere l'input del computer
#define __SERIAL_GET_CINPUT__ true
// Definisce se inviare i messaggi di log sul seriale
#define __SERIAL_SEND_LOG__	true
// Definisce l'interfaccia sul quale comunicare
#define __SERIAL_PREFERRED_INTERFACE__ "serial"
// Definisce la lunghezza massima in caratteri di ogni messaggio
#define __SERIAL__MAX_DATA_BUFFER__ 200