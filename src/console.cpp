
#include "stdafx.h"

#ifdef WINDOWS
    #define kbhit _kbhit
    #define getch _getch
    #define getche _getche
#endif

 #ifdef UNIX
 /*
 Funktion  : int kbhit(void)
 Aufgabe   : Prueft, ob eine Taste gedrueckt wurde. Gibt die Taste nicht aus.
 Eingaben  : keine
 Ausgaben  : 0 falls keine Taste gedrueckt wurde
             1 falls eine beliebige Taste gedrueckt wurde
 Autor     : Internetquelle
 Version   : 02
 Datum der letzten Änderung: 2016-01-22, SK
 */
int kbhit(void){
    struct termios newterm, oldterm;
    int ch = -1, fd = 0;
    fd = fileno(stdin);
    if(tcgetattr(fd, &oldterm)==-1)
    	return(-1);
	memcpy(&newterm, &oldterm, sizeof(struct termios));
    newterm.c_lflag &= ~(ICANON); /* disable canonical mode */
    newterm.c_cc[VMIN] = 0; /* get at least 0 chars */
    newterm.c_cc[VTIME] = 1; /* timeout = 100ms */
    if(tcsetattr(fd, TCSANOW, &newterm)==-1)
    	return(-1);
    ch = getchar();
    if(tcsetattr(fd, TCSANOW, &oldterm)==-1)
    	return(-1);
    if (ch != -1)
        ungetc(ch, stdin); /* flush stdin */
    return ((ch != -1) ? 1 : 0);
}

 /*
 Funktion  : int getch(void)
 Aufgabe   : Liest ein Zeichen von stdin. Gibt das Zeichen nicht aus.
 Eingaben  : keine
 Ausgaben  : ASCII-Code des eingelesenen Zeichens
             -1 falls kein Zeichen in stdin
 Autor     : Internetquelle
 Version   : 02
 Datum der letzten Änderung: 2016-01-22, SK
 */
 int getch(void){
     struct termios newterm, oldterm;
     int ch = -1, fd = 0;
     fd = fileno(stdin);
     if(tcgetattr(fd, &oldterm)==-1)
    	return(-1);
     memcpy(&newterm, &oldterm, sizeof(struct termios));
     newterm.c_lflag &= ~(ICANON|ECHO); /* disable canonical mode and echoing */
     newterm.c_cc[VMIN] = 1; /* get at least 1 chars */
     newterm.c_cc[VTIME] = 0; /* timeout = infinite */
     if(tcsetattr(fd, TCSANOW, &newterm)==-1)
    	return(-1);
     ch = getchar();
     if(tcsetattr(fd, TCSANOW, &oldterm)==-1)
    	return(-1);
     return ch;
}

/*
 Funktion  : int getche(void)
 Aufgabe   : Liest ein Zeichen von stdin. Gibt das Zeichen aus.
 Eingaben  : keine
 Ausgaben  : ASCII-Code des eingelesenen Zeichens
             -1 falls kein Zeichen in stdin
 Autor     : Internetquelle
 Version   : 02
 Datum der letzten Änderung: 2016-01-22, SK
 */
int getche(void){
    struct termios newterm, oldterm;
    int ch = -1, fd = 0;
    fd = fileno(stdin);
    if(tcgetattr(fd, &oldterm)==-1)
    	return(-1);
    memcpy(&newterm, &oldterm, sizeof(struct termios));
    newterm.c_lflag &= ~(ICANON); /* disable canonical mode */
    newterm.c_lflag |= ECHO; /* enable echo mode */
    newterm.c_cc[VMIN] = 1; /* get at least 1 chars */
    newterm.c_cc[VTIME] = 0; /* timeout = infinite */
    if(tcsetattr(fd, TCSANOW, &newterm)==-1)
    	return(-1);
    ch = getchar();
    if(tcsetattr(fd, TCSANOW, &oldterm)==-1)
    	return(-1);
    return ch;
}

#endif
