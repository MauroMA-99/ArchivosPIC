/* 
 * File:   Display_mult.h
 * Author: MauroMA
 *
 * Created on 19 de mayo de 2022, 0:32
 */

#ifndef DISPLAY_MULT_H
#define	DISPLAY_MULT_H

#define _XTAL_FREQ 8000000 /*Definicion del oscilador del CPU*/
#include <stdint.h>  /*Libreria para los enteros no estandar*/
#include <xc.h>
#define Puerto_Display TRISD
#define Puerto_Ena     TRISE
#define Display        LATD
#define Ena            LATE
#define ena1           0
#define ena2           1

/*Variables globales*/
extern uint8_t display7a[10]={0xC0,0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

/*Declaracion de funciones*/
void Display_Init(void);
void mostrarDisplay(uint8_t numero);

#endif	/* DISPLAY_MULT_H */

