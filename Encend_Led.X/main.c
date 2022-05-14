/* 
 * File:   main.c
 * Author: MauroMA
 *
 * Created on 28 de abril de 2022, 19:27
 */

/*Cabecera del programa*/
#include "config.h" //Cabecera de la configuracion de las cond. inic.
#define _XTAL_FREQ 8000000 //Definicion del oscilador del CPU
#define encendido (PORTA & (1<<0)) //Mascara para detectar RA0 en 1

/*Funcion principal*/
int main(void) {
    
    ADCON1=0x0f; //Tods los pines como digitales
    OSCCON =0x72; //Configura el oscilador interno a 8MHz
    TRISA |= (1<<0); //Configura el RA0 como entrada (interuptor)
    TRISC &=~(1<<7); //RC7 como salida (led)
    LATC &=~ (1<<0); //Iniciamos el LED apagado
     
    while(1){
        
        if(encendido){
            LATC |= (1<<7); //Led on
        }
        else{
            LATC &=~(1<<7); //LED off
        }
    }

    return 0;
}




