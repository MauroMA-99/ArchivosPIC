/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#include <xc.h>
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria par alos enteros no estandar*/
#include <stdio.h>
#include <stdlib.h>

/*Variables globales*/

/*Declaracion de funciones*/
void Serial_begin(uint16_t baud);
void Serial_write(char caracter);
void Serial_print(char *s);
void Serial_println(char *s);

/*Funcion principal*/
int main(void) {
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    ADCON1=0x0F;
    Serial_begin(9600); //Iniciamos el puerto serial a 9600 baudios
    
    while (1){
        
        Serial_println("Hola Mundo");
        __delay_ms(1000);
    }
    
    return 0;
}

/*Definicion de funciones*/
void Serial_begin(uint16_t baud){
    float temp;
    TRISC6=0;   /*Pin Tx salida*/
    TRISC7=1;   /*Pin Rx entrada*/
    temp =(_XTAL_FREQ/(64.00*baud))-1;
    SPBRG = (uint8_t)temp;
    TXSTA =0x20; //0b00100000
    RCSTA =0x90; //0b10010000
}

void Serial_write(char caracter){
    while(TXIF == 0);
    TXREG = caracter;
}

void Serial_print(char *s){
    
    while(*s!='\0'){ // Mientras no lleguemos al final de la cadena:
        Serial_write(*s); //Mandamos los datos a Serial_write
        s++;
    }
}

void Serial_println(char *s){
    while(*s!='\0'){
        Serial_write(*s);
        s++;
    }
    Serial_write('\r');// '\r' o '\n' segun tipo de terminal
}