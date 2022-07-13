/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/

/*Funcion principal*/
void main(void) {
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    TRISC2=0; // Pin CCP1 salida
    LATC2=1; 
    T3CON=0xC0; //TImer3 para CCP1 y modo 16 bits
    CCP1CON=0x02; //Modo comparación, Pin CCP1 toggle
    TMR3=0; //Limpiamos TMR3
    CCP1IF=0; //Limpiamos la bandera
    CCPR1=1000; //Valor de comparación
    TMR3ON=1; //Inicia el conteo del TIMER
    
    while (1){
        
        while(!CCP1IF); //Esperamos que la bandera se levante
        CCP1IF=0; //Limpiamos la bandera
        TMR3=0; //Limpiamos contador dee TMR3
    }
    return;
}
