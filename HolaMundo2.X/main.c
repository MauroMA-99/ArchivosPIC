/* 
 * File:   main.c
 * Author: MauroMA
 *
 * Created on 28 de abril de 2022, 19:27
 */

/*Cabecera del programa*/
#include "config.h" //Cabecera de la configuracion de las cond. inic.
#define _XTAL_FREQ 8000000 //Definicion del oscilador del CPU
#include <stdint.h> //Libreria para los enteros no estandar
#include <stdio.h> //Libreria que contiene la definic. de las constantes y declar. de func.
#include <stdlib.h> //Libreria para la gestion de la memoria dinamica y control de procesos

/*Funcion principal*/
int main() {
    
    OSCCON =0x72; //Configura el oscilador interno a 8MHz
    TRISB &=~(1<<0); //Configura el RB0 como salida
    
    while(1){
        
        LATB |=(1<<0); //Encendemos el led en RB0
        __delay_ms(2000); //Esperamos 500 ms
        LATB &=~(1<<0); //Apagamos el led RB0
        __delay_ms(2000); //Esperamos 500 ms
    }

    return 0;
}




