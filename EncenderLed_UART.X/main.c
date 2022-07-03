/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#include <xc.h>
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria par alos enteros no estandar*/
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

/*Variables globales*/
char estado;

/*Declaracion de funciones*/

/*Funcion principal*/
int main(void) {
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    ADCON1=0x0F;
    TRISD1=0; //Led
    LATD1=0;  //Inicialmente el led estará apagado
    Serial_begin(9600); //Iniciamos el puerto serial a 9600 baudios
    
    while (1){
        
        estado=Serial_read();
        
        if(estado=='1'){
            LATD1=1;
            Serial_println("1 -> Led encendido");
        }
        else if(estado=='0'){
            LATD1=0;
            Serial_println("0 -> Led apagado");
        }
        else{
            Serial_println("Ingresaste un dato erroneo");
        }
    }
    return 0;
}

/*Definicion de funciones*/
