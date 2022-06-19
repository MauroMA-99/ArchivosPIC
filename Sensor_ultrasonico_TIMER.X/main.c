/*Cabecera del programa*/
#include <xc.h>
#include "config.h" /*Cabecera con la configuracion de fuses*/
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria par alos enteros no estandar*/
#include <stdio.h>
#include <stdlib.h>
#include "LCD_4bits.h"

/*Variables globales*/

/*Declaracion de funciones*/
void Ultrasonico_Begin(void);
float Ultrasonico_read(void);

/*Funcion principal*/
int main(void) {
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/

    float distancia;
    char distancia_str[10];
    
    Ultrasonico_Begin();
    LCD_Begin();
    LCD_setCursor(0,0);
    LCD_Print("Distancia es : ");
    
    while (1){
        
        distancia=Ultrasonico_read();
        sprintf(distancia_str,"%5.1f",distancia);
        LCD_setCursor(0,1);
        LCD_Print(distancia_str);
        LCD_setCursor(6,1);
        LCD_Print("cm");
        __delay_ms(500);        
    }
    
    return 0;
}

/*Definicion de funciones*/

void Ultrasonico_Begin(void){
    
    TRISCbits.RC0=0; //Pin trigger: salida
    TRISBbits.RB0=1; //Pin echo: entrada
    LATC0=0;         // trigger=0
    T0CON=0b00001000;
    TMR0IF=0;
    TMR0=0;
}

float Ultrasonico_read(void){
    
    float tiempo;
    LATC0=1;
    __delay_us(10);
    LATC0=0;
    while(!PORTBbits.RB0);
    
    TMR0=0;
    TMR0ON=1;
    while(PORTBbits.RB0 && !TMR0IF);
    TMR0ON=0;
    TMR0IF=0;
    tiempo=TMR0; // n=tiempo
    
    return ((float)tiempo/117.00);
}
