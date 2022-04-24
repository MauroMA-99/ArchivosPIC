/*
 * File:   main.c
 * Author: MauroMA
 *
 * Created on 3 de abril de 2022, 11:18
 */

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
void main(void) {
    
    float distancia;
    char distancia_str[10];
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    //ADCON1=0x0F;
    
    LCD_Begin();
    Ultrasonico_Begin();
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
    
    return;
}

void Ultrasonico_Begin(void){
    
    TRISCbits.RC0=0;
    TRISBbits.RB0=1;
    //RBPU=0;
    LATC0=0;
    T1CON=0x80;
    TMR1IF=0;
    TMR1=0;
}

float Ultrasonico_read(void){
    
    float tiempo;
    LATC0=1;
    __delay_us(10);
    LATC0=0;
    
    while(!PORTBbits.RB0);
    
    TMR1=0;
    TMR1ON=1;
    while(PORTBbits.RB0 && !TMR1IF);
    TMR1ON=0;
    TMR1IF=0;
    tiempo=TMR1;
    
    return ((float)tiempo/117.00);
}
