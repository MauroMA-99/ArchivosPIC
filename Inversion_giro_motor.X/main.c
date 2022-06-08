/*Cabecera del programa*/
//#include <xc.h>
#include "config.h" /*Cabecera con la configuracion de fuses*/
#define _XTAL_FREQ 8000000
#include <stdint.h>
#define IN1 0 //Entrada 1 del driver
#define IN2 1 //Entrada 2 del driver

/*Declaración de funciones*/
void INT0_Begin(void);
void INT0_ISR(void);

/*Funcion principal*/
int main(void) {
    
    ADCON1=0x0F; /*Todos los pines digitales*/
    OSCCON=0x72; /*Configura oscilador interno 8MHz*/
    TRISD &=~((1<<IN1)|(1<<IN2)); //IN1 e IN2 salidas
    LATD &=~(1<<IN1); //Dirección inicial: antihoraria
    LATD |=(1<<IN2);
    INT0_Begin();
    
    while(1);
    
    return 0;
}

/*Definicion de funciones */
void __interrupt() ISR(void){
    
    if(INT0IF){
        INT0_ISR();
    }
}

void INT0_Begin(void){
    
    TRISB |= (1<<0); // RB0 entrada
    GIE=1;    //Activa las interrupciones globales
    INT0IE=1; //Habilita la interrupción INT0
    INT0IF=0; //Limpiamos la bandera
    INTCON2=0x00;    // Pull-up activado, INT0 con flanco de bajada
}

void INT0_ISR(void){
    LATD ^=(1<<IN1);
    LATD ^=(1<<IN2);
    __delay_ms(300);
    INT0IF=0;
}


