/* 
 * File:   main.c
 * Author: PC1
 *
 * Created on April 3, 2022, 11:55 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //Variables
    int mostrar[]={ 0b11000000,//0
                    0b11111001,//1
                    0b10100100,//2
                    0b10110000,//3
                    0b10011001,//4
                    0b10010010,//5
                    0b10000011,//6
                    0b11111000,//7
                    0b10000000,//8
                    0b00011000};//9
    /*int mostrar[]={   0b00011000,//9
                        0b10000000,//8
                        0b11111000,//7
                        0b10000011,//6
                        0b10010010,//5
                        0b10011001,//4
                        0b10110000,//3
                        0b10100100,//2
                        0b11111001,//1
                        0b11000000};//0*/
    int contador;
    
    //Configuracion entrada/salida
    TRISC = 0;//Configuracion del puerto C como salida
    do{
        for(contador=0;contador<=9;++contador)
        {
            PORTC = mostrar[contador];
            __delay_ms(250);
        }
    }while(1);

    return (EXIT_SUCCESS);
}

