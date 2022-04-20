/* 
 * File:   main.c
 * Author: PC1
 *
 * Created on April 7, 2022, 11:27 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */
//Declaracion de variables
int DISPLAY[10]={0x3f//0
                ,0x06//1
                ,0x5b//2
                ,0x4f//3
                ,0x66//4
                ,0x6d//5
                ,0x7d//6
                ,0x07//7
                ,0x7f//8
                ,0x6f};//9

int main(int argc, char** argv) {
    int ud=0,dec=0;
    TRISC = 0x00;
    TRISA = 0x00;
    PORTC = 0x00 ;
    for(;;)
    {
        for(dec=0;dec<10;dec++)//Cuenta digito decenas
        {
            for(ud=0;ud<10;ud++)
            {
                PORTA = 0x02;//decenas=apagado;unidades=encendido
                PORTC = DISPLAY[ud];//Digito unidades
                __delay_ms(50);//Para evitar parpadeos
                if(dec==0)//Si decenas = 0
                {
                    PORTA=0x03;//Decenas=apagado
                    
                }
                else//Si decenas >0
                {
                    PORTA = 0x01;//Decenas = encendido
                }
                PORTC = DISPLAY[dec];//Digito decenas
                __delay_ms(50);//Para evitar parpadeos
            }
        }
    }

    return (EXIT_SUCCESS);
}

