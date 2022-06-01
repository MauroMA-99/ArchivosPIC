/*Cabecera del programa*/
#include <xc.h>
#include "config.h" /*Cabecera con la configuracion de fuses*/
#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria par alos enteros no estandar*/

/*Variables globales*/
uint8_t display7a[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

/*Declaración de funciones*/
void pinChange_ISR(void);

/*Funcion principal*/
int main(void) {
    
    ADCON1=0x0F; /*Todos los pines digitales*/
    OSCCON=0x72; /*Configura oscilador interno 8MHz*/
    uint8_t i=0; //Variable contador
    TRISD=0; //Salida para display 7 segmentos
    TRISB |=((1<<4)|(1<<5)|(1<<6)|(1<<7)); //Entradas
    RBPU=0; //Habilito los pull up internos
    
    /*Configuramos la interrupcion (acceso directo)*/
    GIE=1; /*Habilitamos las interrupciones generales*/
    RBIE=1; /*Habilita las interrupciones, cambio de estado*/
    RBIF=0; /*Limpiamos su bandera*/
    
    /*Configuramos la interrupcion (campo de bits)*/
//    INTCON2bits.RBPU=0; //Habilito los pull up internos
//    INTCONbits.RBIE=1; /*Habilita las interrupciones, cambio de estado*/
//    INTCONbits.RBIF=0; /*Limpiamos su bandera*/
//    INTCONbits.GIE=1; /*Habilitamos las interrupciones generales*/
    
    /*Configuramos la interrupcion (uso de máscaras)*/
//    INTCON2 &=~(1<<7); //Habilito los pull up internos
//    INTCON |=(1<<3); /*Habilita las interrupciones, cambio de estado*/
//    INTCON &=~(1<<0); /*Limpiamos su bandera*/
//    INTCON |=(1<<7); /*Habilitamos las interrupciones generales*/
    
    while(1){
        
        for(i=0;i<10;i++){
            
            LATD=display7a[i];
            __delay_ms(1000);
        }
    }
    return 0;
}

/*Definicion de funciones */
void __interrupt() ISR(void){ 
    if(RBIF){           /*Verificamos el flag de la interrupcion*/
        pinChange_ISR(); /*Se verifica inerrupcion, vamos a la ISR*/
    }
}

void pinChange_ISR(void){
    
    uint8_t KBIx; //Drfinimos variables para los pines
    KBIx=(PORTB^0xF0)>>4; //Aplicamos una máscara y corrimiento de bits
    
    switch(KBIx){
        
        case 1:
            LATD=display7a[0];
            break;
        case 2:
            LATD=display7a[1];
            break;
        case 4:
            LATD=display7a[2];
            break;
        case 8:
            LATD=display7a[3];
            break;
        
        default:
            break;
    }
    
    if(KBIx>0)
        __delay_ms(1000); //Para 7 segmentos, generamos el reatrdo solicitado
    RBIF=0;
}


//******************************

