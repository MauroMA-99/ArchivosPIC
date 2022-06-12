/*Cabecera del programa*/
#include "config.h" //Cabecera de la configuracion de las cond. inic.
#include <stdint.h>
#define _XTAL_FREQ 8000000 //Definicion del oscilador del CPU
#define PIN 0

/*Variables globales*/
volatile uint8_t aux=0; // Variable auxiliar para contar 1s

/*Declaracion de funciones*/
void TIMER1_Begin(void);
void TIMER1_ISR(void);

/*Funcion principal*/
int main(void) {
    
    ADCON1=0x0f; //Tods los pines como digitales
    OSCCON =0x72; //Configura el oscilador interno a 8MHz
    TRISB &= ~(1<<PIN); //PIN salida
    LATB |=(1<<PIN); // Mandamos un HIGH a la salida
    TIMER1_Begin();
    TRISA |= (1<<0); //Colocamos el pulsador
    TRISD &= ~(1<<0); //Colocamos el led
    LATD &=~(1<<0);
    
    while(1){
        
        if(PORTAbits.RA0==0){
            
            LATD |=(1<<0);
        }
        else{
            LATD &=~(1<<0);
        }
    }

    return 0;
}

/*Definicion de funciones*/
void __interrupt() ISR(void){
    
    if(TMR1IF){
        TIMER1_ISR();
    }
}

void TIMER1_Begin(void){
    // Configuramos TMR1, sisn prescaler, oscilador interno, apagado
    T1CON=0b10110101;
    TMR1IF=0;  //Limpiamos la bandera de interrupcion
    GIE=1; //Habilita las interrupciones globales
    PEIE=1; //Habilita la interrupcion de periferico TMR1
    TMR1IE=1; //Habilita las interrupcion por desborde
    TMR1=0x3CB0; //Valor inicial del contador
}

void TIMER1_ISR(void){
    
    aux++;
    
    TMR1=0x3CB0; // Valor inicial del contador para 50000
    
    if(aux==5){
        LATB^=(1<<PIN);
        aux=0; //Reiniciamos el contador
    }
    
    TMR1IF=0; // Limpiamos la bandera de interrupción
}
