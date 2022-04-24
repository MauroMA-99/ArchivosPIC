

#include <xc.h> // include processor files - each processor file is guarded.  

// MACROS
#define _XTAL_FREQ 4000000UL

#define RS2 LATDbits.LATD0
#define EN2 LATDbits.LATD1
#define B4 LATAbits.LA2
#define B5 LATAbits.LA3
#define B6 LATAbits.LA4
#define B7 LATAbits.LA5

// PROTOTIPOS
void LCD_PUERTO2(unsigned char a);
void LCD_CMD2(unsigned char a);
void LCD_LIMPIAR2( void );
void LCD_POSICION2(unsigned char a, unsigned char b);
void LCD_INICIO2( void );
void LCD_LETRA2(unsigned char a);
void LCD_MENSAJE2(unsigned char *a);
void LCD_DESPLAZAMIENTO_DERECHA2( void );
void LCD_DESPLAZAMIENTO_IZQUIERDA2( void );
void CARACTER2(char data);

