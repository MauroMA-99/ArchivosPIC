/* 
 * File:   uart.h
 * Author: MauroMA
 *
 * Created on November 1, 2021, 10:40 PM
 */

#ifndef UART_H
#define	UART_H

/*Declaracion de funciones*/
#define _XTAL_FREQ 4000000
#include <stdint.h>
#include <xc.h>
void Serial_begin(uint16_t baud);
uint8_t Serial_available(void);
void Serial_write(char caracter);
char Serial_read(void);
void Serial_print(char *s);
void Serial_println(char *s);

/*Definicion de funciones*/
void Serial_begin(uint16_t baud){
    float temp;
    TRISC6=0;   /*Pin Tx salida*/
    TRISC7=1;   /*Pin Rx entrada*/
    temp =(_XTAL_FREQ/(64.00*baud))-1;
    SPBRG = (uint8_t)temp;
    TXSTA =0x20;
    RCSTA =0x90;       
}
uint8_t Serial_available(void){
    if(PIE3bits.RCIE == 1)
        return 1;
    else
        return 0;
}
// PIE3bits.RCIE
//  PIE3bits.TXIE

void Serial_write(char caracter){
    while(TXIE == 0);
    TXREG = caracter;
}
char Serial_read(void){
    while(RCIE==0);     /*Esperar por la bandera de interupcion*/
    if(OERR){
        CREN = 0;
        NOP();
        CREN = 1;
    }
    return RCREG;
}
void Serial_print(char *s){
    while(*s!='\0'){
        Serial_write(*s);
        s++;
    }
}
void Serial_println(char *s){
    while(*s!='\0'){
        Serial_write(*s);
        s++;
    }
    Serial_write('\r');// '\r' o '\n' segun tipo de terminal
}


#endif	/* UART_H */

