/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#include "Display_mult.h"

/*Funcion principal*/
int main(void) {
    
    uint8_t cuenta=0;
    ADCON1=0x0F; /*Configura los pines ANx a digital*/
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    Puerto_Display = 0; /*Configura el puerto D como salida*/
    /*Salida para los Ena*/
    Puerto_Ena &=~ ((1<<ena1)|(1<<ena2));
    /*Deshabilitamos los 2 displays*/
    Ena |= ((1<<ena1)|(1<<ena2));
    
    while (1){
        
        mostrarDisplay(cuenta);
        cuenta++;
        
        if(cuenta==15){
            cuenta=0;
        }
        
    }

    return 0;
}

/*Definicion de funciones */

