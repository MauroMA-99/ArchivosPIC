/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria par alos enteros no estandar*/
#include <stdio.h>
#include <stdlib.h>
#include "LCD_4bits.h"
#define VREF 5.00 /*Voltaje de REf=5V*/

/*Variables globales*/
void ADC_Begin(uint8_t N_canales);
uint16_t ADC_Read(uint8_t canal);

/*Declaracion de funciones*/

/*Funcion principal*/
int main(void) {
    
    char buffer[8];
    float voltaje1;
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    ADC_Begin(1);
    LCD_Begin();
    LCD_setCursor(0,0);
    LCD_Print("Voltaje es : ");
    
    while (1){
        
        /*Convertir el valor digital a analogico*/
        voltaje1=ADC_Read(0)*(VREF/1023);
        /*Convertimos el float en cadena de texto ASCCI*/
        sprintf(buffer,"V=%.2f",voltaje1);
        LCD_setCursor(0,1);
        LCD_Print(buffer);
        __delay_ms(500);
    }
    
    return 0;
}

/*Definicion de funciones*/
void ADC_Begin(uint8_t N_canales){
    
    ADCON1=~N_canales & 0x0F; // Referencias Vss y Vdd y habilita ANx
    ADCON2=0x91; //0b10010001 : Justificado a la derecha 4Tad FOSC/8
    ADRES=0; // Limpiamos los registros
}

uint16_t ADC_Read(uint8_t canal){
    
    uint16_t valor;
    //Asigno el canal de lectura
    ADCON0=(canal<<2);
    ADON=1; //Habilitamos el modulo ADC
    GO_DONE=1; //Iniciamos la conversion
    while(GO_DONE);
    valor=ADRES;
    
    return valor;
}
