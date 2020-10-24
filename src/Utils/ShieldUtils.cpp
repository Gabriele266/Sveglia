/*
	Autore: Cavallo Gabriele
	Versione: 1.1

	Insieme di funzioni utili per il controllo della scheda
	Il seguente codice è aperto a modifiche
*/
#ifndef SHUTIL
#define SHUTIL

static void hardReset() {
	// Resetto la scheda tramite comando assembly
	asm volatile ("jmp 0");
}

#endif
