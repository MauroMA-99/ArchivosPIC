/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/
#include "Display_mult.h"

/*Funcion principal*/
int main(void) {
    
    ADCON1=0x0F; /*Configura los pines ANx a digital*/
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    
    Display_Init();
    
    TRISB5=1; //entrada
    uint8_t cuenta=0;
    uint8_t bandera1=0;
    uint8_t bandera2=1;
    
    while (1){
        
        if(PORTBbits.RB5==1){
            bandera1=1;
        }
        else{
            bandera1=0;
            bandera2=1;
        }
        
        if(bandera1==1 && bandera2==1){
            cuenta++;
            bandera2=0;
        }
        
        if(cuenta==12){
            cuenta=0;
        }
        mostrarDisplay(cuenta);
        
    }

    return 0;
}

/*Definicion de funciones */

