//..begin "Ifdef"
#ifndef _Console_H_
#define _Console_H_
//..end "Ifdef"

//..begin "pragma"
#pragma once
//..end "pragma"

//#define UNIX
//#define WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef UNIX
    #include <termios.h>
    #include <unistd.h>
    #define UNIXCONSOLEIO ; // do nothing, already enabled
    // forward declarations of console input functions
    int kbhit(void);
    int getch(void);
    int getche(void);
#endif

#ifdef WINDOWS
    #include <conio.h>
    #include <windows.h>
    // Erlaube der Windows Console auf ESC Steuersequenzen zu reagieren
    #define UNIXCONSOLEIO { HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); DWORD dwMode = 0; GetConsoleMode(hOut, &dwMode); SetConsoleMode(hOut, dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);}
#endif

 /* Unix kompatible Defines zur Positionierung des Cursors auf der Konsole */
 /* ANSI Escape Sequences start by ESC \x1b[ followed by an escape code */
 /* See also "https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797" */
 /* CLS = Clear Screen. Use: CLS; */
 #define CLS printf("\x1b[2J");fflush(stdout)
 /* CURPOS(L,C) = Positioniere den Cursor in Zeile L und Spalte C.
  * Use: to print a text in line L starting at column C
  * CURPOS(L,C); printf("place your text here"); */
 #define CURPOS(L,C) printf("\x1b[%d;%df",L,C);fflush(stdout)
 /* CURPOSTEXT(L,C,T) = Positioniere den Cursor in Zeile L und Spalte C.
  * Use: to print text T in line L starting at column C
  * CURPOSTEXT(L,C,T); T="place your text here" */
 #define CURPOSTEXT(L,C,T) printf("\x1b[%d;%df",L,C);printf("\x1b[0m%s",T);fflush(stdout)
 /* CURPOSGREENTEXT(L,C,T) = Positioniere den Cursor in Zeile L und Spalte C.
  * Use: to print a green colored text T in line L starting at column C
  * CURPOSGREENTEXT(L,C,T); T="place your text here" */
 #define CURPOSGREENTEXT(L,C,T) printf("\x1b[%d;%df",L,C);printf("\x1b[32m%s\x1b[0m",T);fflush(stdout)
 #define CURPOSGREENFTEXT(L,C,F,T) printf("\x1b[%d;%df\x1b[32m",L,C);printf(F,T);printf("\x1b[0m");fflush(stdout)
 /* CURPOSGREENSTR(L,C,F,S) = Positioniere den Cursor in Zeile L und Spalte C.
  * Use: to print a green colored String (F) followed by String S in line L starting at column C
  * CURPOSGREENSTR(L,C,F,S); F=StringF, S=StringS */
 #define CURPOSGREENSTR(L,C,F,S) printf("\x1b[%d;%df",L,C);printf("\x1b[32m%s %s\x1b[0m",F,S);fflush(stdout)
 /* CURUP(L) = Bewege den Cursor um L Zeilen nach oben. */
 #define CURUP(L) printf("\x1b[%dA",L);fflush(stdout)
 /* CURDOWN(L) = Bewege den Cursor um L Zeilen nach unten. */
 #define CURDOWN(L) printf("\x1b[%dB",L);fflush(stdout)
 /* CURRIGHT(C) = Bewege den Cursor um C Spalten nach rechts. */
 #define CURRIGHT(C) printf("\x1b[%dC",C);fflush(stdout)
 /* CURLEFT(C) = Bewege den Cursor um C Spalten nach links. */
 #define CURLEFT(C) printf("\x1b[%dD",C);fflush(stdout)
 /* CUR2EOL = Lösche alle Zeichen rechts ab aktuelle CURPOS */
 #define CURCLR2EOL printf("\x1b[K");fflush(stdout)

//..begin "Endif"
#endif //_Console_H_
//..end "Endif"