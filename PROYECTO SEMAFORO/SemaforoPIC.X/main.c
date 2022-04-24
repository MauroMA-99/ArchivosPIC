/* 
 * File:   main.c
 * Author: ALEXIS
 *
 * Created on 16 de septiembre de 2021, 04:56 PM
 */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <pic18f4550.h>
#include "PantallaLCD.h"
#include "PantallaLCD2.h"
#include "Config_Fuses.h"
#include "ADC.h"
#include "USART.h"
#define _XTAL_FREQ 4000000UL

// MACROS
uint16_t TVERDE=10;
uint16_t TAMBAR=3;
uint16_t TROJO=0;
#define AUTOSVERDE LATCbits.LATC0
#define AUTOSAMBAR LATCbits.LATC1
#define AUTOSROJO LATCbits.LATC2
#define PEATONESVERDE LATEbits.LATE0
#define PEATONESAMBAR LATEbits.LATE1
#define PEATONESROJO LATEbits.LATE2

/*
 * 
 */
// DEFINIMOS LA ESTRUCTURA DE LA MAQUINA DE ESTADOS
typedef enum{
    PasePeatones=0,
    AmbarPeatones,
    PaseCarros,
    AmbarCarros,       
}Cambios;
Cambios Semaforo;

// DEFINIMOS LOS PROTOTIPOS
void GoPeatones(void);              // PEATONES:VERDE AUTOS:ROJO
void WaitPeatones(void);            // PEATONES:AMBAR AUTOS:ROJO
void GoCarros(void);                // PEATONES:ROJO AUTOS:VERDE 
void WaitCarros(void);              // PEATONES:AMBAR AUTOS:VERDE 
void Config_Interrup_Globales(void);// CONFIGURO INTERRPCIONES GLOBALES
void Config_Interrup_TMR0(void);    // CONFIGURO INTERRPCIONES POR TIMER
void Config_TMR0(void);             // CONFIGURO EL PERIFERICO DEL TIMER
void Config_Interrupt_Rx(void);     // INTERRUPCIÓN POR RECEPCIÓN
void Info_Temperatura(void);        // MUESTRO EL MENSAJE DE LA TEMPERATURA
void Reloj_Digital(void);           // MUESTRO EL MENSAJE DEL TIEMPO
void Mensaje_EUART(void);           // ENVIA MENSAJES POR EL PUERTO SERIAL
void MostrarTiempos(void);          // MUESTRA EL TIEMPO DE VERDE Y AMBAR EN LCD 

// DEFINIMOS LOS PROTOTIPOS TECLADO
void Interrupcion_Teclado(void);
void Cambio_Teclado(void);
void ProgramarTiempo(void);

uint16_t CadenaAEntero(char cadena[3],uint8_t posicion);

// VARIABLES 
float tempAutos,tempPeatones;
uint16_t TiempoAutos,TiempoPeatones;
char str_tempAutos[8],str_tempPeatones[8],str_TiempoAutos[8],str_TiempoPeatones[8];
volatile uint16_t contador=0;
volatile uint8_t segundos=0,minutos=0,horas=0;
char str_segundos[4],str_minutos[4],str_horas[4];
char str_key[10],str_tiempos[20];
char str_verde[4],str_rojo[4],str_ambar[4];
uint8_t estado=0;
char str_estado[4];

// VARIABLES DE LA INTERRUPCIÓN POR RECEPCIÓN 
volatile bool bandera=false,MostrarMensaje=false;
volatile char caracter;
volatile uint8_t position=0;
volatile char DataRecibida[7]="       ";
volatile uint8_t Numero_Color=0;      // 0=VERDE 1=AMBAR

uint8_t keypad[4][4]={7,8,9,10,
                      4,5,6,11,
                      1,2,3,12,
                      14,20,15,13};// 0 ==>20

//VARIABLES PANTALLA 
uint8_t key=0;   // BOTON PRESIONADO EN EL TECLADO
uint8_t indice=0; // RECORRE LA POSICION DEL ARRAY
uint8_t valor[5];  // CADENA QUE ALMACENA EL TIEMPO DIGITALIZADO POR EL TECLADO
/*
 * 
 */
int main(int argc, char** argv) {
    OSCCONbits.IRCF=0b110;    // DEFINIMOS FRECUENCIA 4MHz
    Config_ADC();             // CONFIGURACIÓN ADC
    
    // DEFINIMOS PUERTOS
    
    //TRISB=0;                  // PUERTO B COMO SALIDA
    // **** PARA LA PANTALLA LCD **********
    TRISD=0;                  // PUERTO D COMO SALIDA
    TRISAbits.RA2=0;          // PUERTO RA2 COMO SALIDA
    TRISAbits.RA3=0;          // PUERTO RA3 COMO SALIDA
    TRISAbits.RA4=0;          // PUERTO RA4 COMO SALIDA
    TRISAbits.RA5=0;          // PUERTO RA5 COMO SALIDA
    // **** PARA SEMAFOROS **********
    TRISCbits.RC0=0;          // PUERTO RC0 COMO SALIDA
    TRISCbits.RC1=0;          // PUERTO RC1 COMO SALIDA
    TRISCbits.RC2=0;          // PUERTO RC2 COMO SALIDA
    TRISEbits.RE0=0;          // PUERTO RE0 COMO SALIDA
    TRISEbits.RE1=0;          // PUERTO RE1 COMO SALIDA
    TRISEbits.RE2=0;          // PUERTO RE2 COMO SALIDA
    // **** PARA TECLADO  **********
    TRISB=0xF0;                // CONFIGURAMOS PUERTO B TECLADO
    // INICALIZAMOS SALIDAS
    LATB=0xF0;                // INICIALIZAMOS PUERTO B TECLADO
    LATD=0;                   // INICIALIZAMOS PUERTO D
    AUTOSVERDE=0;             // INICIALIZAMOS PUERTO C0
    AUTOSAMBAR=0;             // INICIALIZAMOS PUERTO C1
    AUTOSROJO=0;              // INICIALIZAMOS PUERTO C2
    PEATONESVERDE=0;          // INICIALIZAMOS PUERTO E0
    PEATONESAMBAR=0;          // INICIALIZAMOS PUERTO E1
    PEATONESROJO=0;           // INICIALIZAMOS PUERTO E2
    
    Config_Interrup_Globales(); // CONFIGURAMOS INTERRUPCIONES GLOBALES
    Config_Interrup_TMR0();   // CONFIGURAMOS INTERRUPCIÓN TMR0
    Config_TMR0();            // CONFIGURAMOS TMR0
    Config_Interrupt_Rx();    // CONFIGURACIÓN DE LA INTERRUPCION POR RECEPCIÓN
    Config_EUART(9600);       // CONFIGURACION EUSART
    Interrupcion_Teclado();   // CONFIGURAMOS INTERRUPCIÓN TECLADO
    
     // LIMPIAMOS EL ARRAY DONDE SE ALMACENARA EL VALOR DEL TIEMPO TECLEADO
    memset(valor,0,5);
   // INICIALIZAMOS LA PANTALLA 1
    LCD_INICIO();             // INICIALIZAMOS LA PANTALLA LCD
    LCD_LIMPIAR();            // LIMPIAMOS LA PANTALLA LCD 
    // INICIALIZAMOS LA PANTALLA 2
    LCD_INICIO2();            // INICIALIZAMOS LA PANTALLA LCD2
    LCD_LIMPIAR2();           // LIMPIAMOS LA PANTALLA LCD2
    MostrarTiempos();        // MOSTRAR TIEMPO VERDE Y AMBAR  

    Semaforo=PasePeatones; // INICIALIZAMOS LA MAQUINA DE ESTADOS
    while(1){
        TROJO=TVERDE+TAMBAR;
        // OBTENEMOS LOS VALORES DE LA TEMPERATURA
        tempAutos=(float)((float)Canal_ADC(0)*(500.0/1023.0));
        tempPeatones=(float)((float)Canal_ADC(1)*(500.0/1023.0));
        // CONVERTIMOS LAS VARIABLES
        sprintf(str_tempAutos,"%.2f",tempAutos);
        sprintf(str_tempPeatones,"%.2f",tempPeatones);
        sprintf(str_TiempoAutos,"%02u",TiempoAutos);
        sprintf(str_TiempoPeatones,"%02u",TiempoPeatones);
        sprintf(str_segundos,"%02u",segundos);
        sprintf(str_minutos,"%02u",minutos);
        sprintf(str_horas,"%02u",horas);
        sprintf(str_verde,"%02u",TVERDE);
        sprintf(str_ambar,"%02u",TAMBAR);
        sprintf(str_rojo,"%02u",TROJO);
        sprintf(str_estado,"%u",estado);
        
        switch(Semaforo){    
            case PasePeatones:GoPeatones();break;
            case AmbarPeatones:WaitPeatones();break;
            case PaseCarros:GoCarros();break;
            case AmbarCarros:WaitCarros();break;
        }
        ProgramarTiempo();
        if(MostrarMensaje==true){
            switch(Numero_Color){
                case 0:TVERDE=(uint16_t) atoi(DataRecibida);contador=0;break;
                case 1:TAMBAR=(uint16_t) atoi(DataRecibida);contador=0;break;
                default: break;
            }
            memset(DataRecibida,0, 7);
            MostrarTiempos();         // ACTUALIZAMOS VALOR DE LOS TIEMPOS
            MostrarMensaje=false;
        }
        
    }

    return (EXIT_SUCCESS);
}

void __interrupt() Alexis(){
    if(INTCONbits.TMR0IF==1){
        // CARGO EL REGISTRO DEL TIMER A 1s
        TMR0H=0X85;
        TMR0L=0XEE;
        INTCONbits.TMR0IF=0;        // DESABILITO LA BANDERA DEL TIMER 0
        contador++; 
        Mensaje_EUART();           // ENVIAR MENSAJE POR EUART
        segundos++;
        // AUMENTO EL TIEMPO CADA 1s
        if(segundos==60){
            segundos=0;
            minutos++;
        }
        if(minutos==60){
            minutos=0;
            horas++;
        }
        if(horas==24){
            horas=0;
        }
       
    }
    if(RBIF){
        Cambio_Teclado();
        //ProgramarTiempo();
        INTCONbits.RBIF=0;
    }
    if(PIR1bits.RCIF==1){
        caracter=RCREG;
        if(bandera==false){
            switch(caracter){
                case '@': bandera=true;Numero_Color=0;break;
                case '*': bandera=true;Numero_Color=1;break;
                default: break; // @20%  *10/
            }   
        }
        while(bandera==true){
            while(PIR1bits.RCIF==0);
            if(RCSTAbits.OERR == 1){
                RCSTAbits.CREN = 0;
                NOP(); //Realizo un reatardo de 1 ciclo maquina
                RCSTAbits.CREN = 1;
            }
                caracter=RCREG;
            if(caracter=='%' || caracter=='/'){ 
                bandera=false;
                /*if(position<7){
                    for(int i=position;i<=6;i++){
                        DataRecibida[i]='0';
                    }
                }*/
                position=0;
                MostrarMensaje=true;             
            }else{
                DataRecibida[position]=caracter;
                position++;
            }
        }    
    }
}

uint16_t CadenaAEntero(char cadena[5],uint8_t posicion){
    uint16_t numero=0;
    uint8_t cuenta=0;
    for(int i=posicion;i>-1;i--){
        numero=(uint16_t)(numero+((cadena[i])*pow(10,cuenta)));
        cuenta++; // PERMITE VER EL GRADO DE POTENCIA DE 10
    }
    return numero;
}

void ProgramarTiempo(void){
    if(key!=0){
        if(key!= 12 && key!=13 &&key!=14 &&key!=15){ 
            if(key==10 || key==11 ){
                if(key==10){
                  TVERDE=CadenaAEntero(valor,indice-1); 
                }
                if(key==11){
                   TAMBAR=CadenaAEntero(valor,indice-1); 
                }
                LCD_POSICION(2,21);
                LCD_MENSAJE("TECLADO PROGRAMADO");
                contador=0;               // REINICIO EL TIEMPO
                Semaforo=PasePeatones;    // CAMBIO DE ESTADO
                indice=0;                 // INICIALIZAMOS EL INDICE DEL ARRAT
                memset(valor,0,5);        // RESETEAMOS VALOR DEL ARRAY
                MostrarTiempos();         // ACTUALIZAMOS VALOR DE LOS TIEMPOS
            }else{
                if(key==20){
                    key=0;
                }
                LCD_POSICION(2,21);
                LCD_MENSAJE("TECLADO: ");
                LCD_POSICION(2,30+indice);
                sprintf(str_key,"%u sec      ",key);
                //str_key=(char)key;
                LCD_MENSAJE(str_key);
                valor[indice]=(uint8_t)key;
                indice++;
            }
       }
       key=0;
     }


}

void MostrarTiempos(void){
    sprintf(str_tiempos,"Verde:%us Ambar:%us ",TVERDE,TAMBAR);
    LCD_POSICION2(2,21);
    LCD_MENSAJE2(str_tiempos);

}

// IMPRIMIR RELOJ EN ESUART
void Mensaje_EUART(void){
    EnviarMensaje_USART(str_tempAutos);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_tempPeatones);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_horas);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_minutos);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_segundos);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_rojo);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_ambar);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_verde);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_TiempoPeatones);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_TiempoAutos);
    EnviarMensaje_USART("#");
    EnviarMensaje_USART(str_estado);
}

// FUNCIONES DEL SEMAFORO
void GoPeatones(void){
    estado=0;
    //MENSAJE EN LA PANTALLA LCD SOBRE SEMAFORO
    if((TiempoPeatones!=0)&&(TiempoAutos!=0)){
        LCD_POSICION(1,1);
        LCD_MENSAJE("PASE ");
        LCD_MENSAJE("PEATONES: ");
        LCD_MENSAJE(str_TiempoPeatones);
        LCD_MENSAJE(" ");
        LCD_POSICION2(1,1);
        LCD_MENSAJE2("STOP ");
        LCD_MENSAJE2("AUTOS: ");
        LCD_MENSAJE2(str_TiempoAutos);
        LCD_MENSAJE2("  ");
    }
    TiempoPeatones=TVERDE-contador;
    TiempoAutos=(TVERDE+TAMBAR)-contador;
    // SEMAFORO
    AUTOSVERDE=0;         
    AUTOSAMBAR=0;        
    AUTOSROJO=1;         
    PEATONESVERDE=1;         
    PEATONESAMBAR=0;        
    PEATONESROJO=0; 
    //MENSAJE EN LA PANTALLA LCD SOBRE TEMPERATURA
    Info_Temperatura();
    //MENSAJE EN LA PANTALLA LCD SOBRE LA HORA
    Reloj_Digital();
    if(contador==TVERDE){
        Semaforo=AmbarPeatones;  // CAMBIO DE ESTADO
    }
}

void WaitPeatones(void){
    estado=1;
    //MENSAJE EN LA PANTALLA LCD SOBRE SEMAFORO
    if((TiempoPeatones!=0)&&(TiempoAutos!=0)){
        LCD_POSICION(1,1);
        LCD_MENSAJE("ESPERE ");
        LCD_MENSAJE("PEATONES: ");
        LCD_MENSAJE(str_TiempoPeatones);
        LCD_MENSAJE("  ");
        LCD_POSICION2(1,1);
        LCD_MENSAJE2("STOP ");
        LCD_MENSAJE2("AUTOS: ");
        LCD_MENSAJE2(str_TiempoAutos);
        LCD_MENSAJE2("  ");
    }
    TiempoPeatones=(TVERDE+TAMBAR)-contador;
    TiempoAutos=(TVERDE+TAMBAR)-contador;
    // SEMAFORO
    AUTOSVERDE=0;         
    AUTOSAMBAR=0;        
    AUTOSROJO=1;         
    PEATONESVERDE=0;         
    PEATONESAMBAR=1;        
    PEATONESROJO=0;
    //MENSAJE EN LA PANTALLA LCD SOBRE TEMPERATURA
    Info_Temperatura();
    //MENSAJE EN LA PANTALLA LCD SOBRE LA HORA
    Reloj_Digital();
    if(contador==(TVERDE+TAMBAR)){
        Semaforo=PaseCarros;   // CAMBIO DE ESTADO
    }
}

void GoCarros(void){
    estado=2;
    //MENSAJE EN LA PANTALLA LCD SOBRE SEMAFORO
    if((TiempoPeatones!=0)&&(TiempoAutos!=0)){
        LCD_POSICION(1,1);
        LCD_MENSAJE("STOP ");
        LCD_MENSAJE("PEATONES: ");
        LCD_MENSAJE(str_TiempoPeatones);
        LCD_MENSAJE("   ");
        LCD_POSICION2(1,1);
        LCD_MENSAJE2("PASE ");
        LCD_MENSAJE2("AUTOS: ");
        LCD_MENSAJE2(str_TiempoAutos);
        LCD_MENSAJE2("  ");
    }
    TiempoPeatones=(2*(TVERDE+TAMBAR))-contador;
    TiempoAutos=((2*TVERDE)+TAMBAR)-contador;
    // SEMAFORO
    AUTOSVERDE=1;         
    AUTOSAMBAR=0;        
    AUTOSROJO=0;         
    PEATONESVERDE=0;         
    PEATONESAMBAR=0;        
    PEATONESROJO=1; 
    //MENSAJE EN LA PANTALLA LCD SOBRE TEMPERATURA
    Info_Temperatura();
    //MENSAJE EN LA PANTALLA LCD SOBRE LA HORA
    Reloj_Digital();
    if(contador==((2*TVERDE)+TAMBAR)){
        Semaforo=AmbarCarros;    // CAMBIO DE ESTADO
    }
}

void WaitCarros(void){
    estado=3;
    //MENSAJE EN LA PANTALLA LCD SOBRE SEMAFORO
    if((TiempoPeatones!=0)&&(TiempoAutos!=0)){
        LCD_POSICION(1,1);
        LCD_MENSAJE("STOP ");
        LCD_MENSAJE("PEATONES: ");
        LCD_MENSAJE(str_TiempoPeatones);
        LCD_MENSAJE("   ");
        LCD_POSICION2(1,1);
        LCD_MENSAJE2("ESPERE ");
        LCD_MENSAJE2("AUTOS: ");
        LCD_MENSAJE2(str_TiempoAutos);
        LCD_MENSAJE2("  ");
    } 
    TiempoPeatones=(2*(TVERDE+TAMBAR))-contador;
    TiempoAutos=(2*(TVERDE+TAMBAR))-contador;
    // SEMAFORO
    AUTOSVERDE=0;         
    AUTOSAMBAR=1;        
    AUTOSROJO=0;         
    PEATONESVERDE=0;         
    PEATONESAMBAR=0;        
    PEATONESROJO=1; 
    //MENSAJE EN LA PANTALLA LCD SOBRE TEMPERATURA
    Info_Temperatura();
    //MENSAJE EN LA PANTALLA LCD SOBRE LA HORA
    Reloj_Digital();
    if(contador==(2*(TVERDE+TAMBAR))){
        Semaforo=PasePeatones;   // CAMBIO DE ESTADO
        contador=0;
    }
}

// IMPRIMIR RELOJ EN LCD
void Reloj_Digital(void){
    LCD_POSICION(1,21);
    LCD_MENSAJE("H:");
    LCD_MENSAJE(str_horas);
    LCD_MENSAJE(" ");
    LCD_MENSAJE("M:");
    LCD_MENSAJE(str_minutos);
    LCD_MENSAJE(" ");
    LCD_MENSAJE("S:");
    LCD_MENSAJE(str_segundos);
    LCD_MENSAJE(" ");
    LCD_POSICION2(1,21);
    LCD_MENSAJE2("H:");
    LCD_MENSAJE2(str_horas);
    LCD_MENSAJE2(" ");
    LCD_MENSAJE2("M:");
    LCD_MENSAJE2(str_minutos);
    LCD_MENSAJE2(" ");
    LCD_MENSAJE2("S:");
    LCD_MENSAJE2(str_segundos);
    LCD_MENSAJE2(" ");

}

void Config_Interrup_Globales(void){
    INTCONbits.GIE=1;          // HABILITO INTERRUPCIONES GLOBALES
    INTCONbits.PEIE=1;         // HABILITO INTERRUPCIONES PERIFERICOS
}

void Config_Interrup_TMR0(void){
    INTCONbits.TMR0IE=1;            // HABILITO LA INTERRUCPCIÓN DEL TIMER 0
    INTCONbits.TMR0IF=0;            // DESABILITO LA BANDERA DEL TIMER 0
}

void Config_TMR0(void){
    T0CONbits.TMR0ON=0;            // TODAVIA NO HABILITO EL TIMER 0
    T0CONbits.T08BIT=0;            // 16 BITS
    T0CONbits.T0CS=0;              // RELOJ INTERNO
    T0CONbits.PSA=0;               // PRE ESCALER ASIGNADO
    T0CONbits.T0PS=0b100;          // PRE ESCALER x32
    // CARGAMOS EL REGISTRO
    TMR0H=0X85;
    TMR0L=0XEE;
    T0CONbits.TMR0ON=1;            // HABILITO EL TIMER 0
}

void Config_Interrupt_Rx(void){
    PIE1bits.RCIE=1;       // HABILITAMOS INTERUPCION DE RECEPCION
    PIR1bits.RCIF=0;       // BANDERA APAGADA
}

void Info_Temperatura(void){
    LCD_POSICION(2,1);
    LCD_MENSAJE("TEMPERATURA: ");
    LCD_MENSAJE(str_tempPeatones);
    LCD_MENSAJE(" ");
    LCD_POSICION2(2,1);
    LCD_MENSAJE2("TEMPERATURA: ");
    LCD_MENSAJE2(str_tempAutos);
    LCD_MENSAJE(" ");
}
   // TMR0H=0XE7; TMR0L=0X96;  PARA 200ms
   // TMR0H=0XCF; TMR0L=0X2C;  PARA 400ms
   // TMR0H=0XB6; TMR0L=0XC2;  PARA 600ms
   // TMR0H=0X9E; TMR0L=0X58;  PARA 800ms 
 
void Interrupcion_Teclado(void){
    INTCON2bits.RBPU=0;      // Habilita pull--up Puerto B
    INTCONbits.RBIE=1;       // Habilita las interrupciones de cambio de estado
    INTCONbits.RBIF=0;       // Limpiamos la bandera
}

void Cambio_Teclado(void){
    uint8_t KBIx,i=1,j=0;
    uint8_t ROW=4,COL=0;
    KBIx=(PORTB^0xF0)>>4;
    while((KBIx>>i)){
        COL++;
        i++;
    }
    while(j<4){
        LATB=~(1<<j);
        if(PORTB!=LATB){
            ROW=j;
        }
        j++;
    }
    __delay_ms(50);
    key=keypad[ROW][COL];
    LATB=0xF0;
}