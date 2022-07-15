/*Cabecera del programa*/
#include "config.h" /*Cabecera con la configuracion de fuses*/

/*Funcion principal*/
int main(void) {
    
    OSCCON=0x72; /*Configura Oscilador interno a 8 MHz*/
    TRISC2=0; // Pin CCP1 salida
    PR2=199; // Carga frecuencia PWM
    CCPR1L=40; // Carga del duty cycle
    CCP1CON=0x0C; //Modo de operación PWM
    T2CON=0; // Prescaler 1, TIMER2 off
    TMR2=0; // Limpiamos TMR2
    TMR2ON=1; // Inicia el TIMER2
    
    while (1){
    }
    
    return 0;
}
