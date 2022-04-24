

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 4000000UL

// MACROS
#define RS LATDbits.LATD2
#define EN LATDbits.LATD3
#define D4 LATDbits.LATD4
#define D5 LATDbits.LATD5
#define D6 LATDbits.LATD6
#define D7 LATDbits.LATD7

// PROTOTIPOS
void LCD_PUERTO(unsigned char a);
void LCD_CMD(unsigned char a);
void LCD_LIMPIAR( void );
void LCD_POSICION(unsigned char a, unsigned char b);
void LCD_INICIO( void );
void LCD_LETRA(unsigned char a);
void LCD_MENSAJE(unsigned char *a);
void LCD_DESPLAZAMIENTO_DERECHA( void );
void LCD_DESPLAZAMIENTO_IZQUIERDA( void );
void CARACTER(char data);

