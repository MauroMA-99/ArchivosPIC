/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#include "LCD_4bits.h"
#include <xc.h>
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#define F_TIMER1 2000000  //Timer sin prescaler
#include <stdint.h>  /*Libreria par alos enteros no estandar*/
#include <stdio.h>
#include <stdlib.h>

/*Variables globales*/

/*Declaracion de funciones*/
void Capture_Begin(void);
float Capture_read(void);

/*Funcion principal*/
void main(void) {
    
    float frecuencia;
    char buffer[16];
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    LCD_Begin();
    Capture_Begin();
    LCD_setCursor(0,0);
    LCD_Print("Frecuencia es :");
    
    while (1){
        
        frecuencia=Capture_read();
        sprintf(buffer,"%.1f",frecuencia);
        LCD_setCursor(0,1);
        LCD_Print(buffer);
        __delay_ms(500);
    }
    return;
}

/*Definicion de funciones*/
void Capture_Begin(void){
    
    TRISC2=1; //Entrada para el modulo CCP1
    CCP1CON=0x05; //Modo captura en flanco de subida
    //T3CON=0b10000000;
    T1CON=0x80; //16 bits, TIMER1 sin prescaler, apagado
    CCPR1=0;
    TMR1=0;
    CCP1IF=0;
    CCP1IE=1; //Activamos la interrupcion del modulo CCP1
    TMR1ON=1; // Activamos la cuenta del TIMER
}

float Capture_read(void){
    
    uint16_t signal_period,data1=0,data2=0;
    
    while(data1>=data2){
        while(!CCP1IF); //Esperamos la bandera de captura
        CCP1IF=0; //Limpiamos la bandera
        data1=CCPR1; //Copiamos el valor del 1er flanco del contador
        
        while(!CCP1IF); //Esperamos la bandera de captura
        CCP1IF=0; //Limpiamos la bandera
        data2=CCPR1; //Copiamos el valor del 2do flanco del contador
    }
    
    TMR1=0;
    //Calculo de la frecuencia
    signal_period=data2-data1;
    
    //Cda muestra nos genera 0.5us de tiempo
    return ((float)F_TIMER1/(float)signal_period);
}
