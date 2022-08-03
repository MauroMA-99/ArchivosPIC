/*
 * Libreria en C: es un conjunto de funciones diseñadas para realizar tareas especificas
 * Una libreria en C esta compuesta por 2 archivos
 * 
 * Archivo.h -> Encontramos recursos de otras librerias, macros, tipos de datos, prototipos de funciones
 * 
 * Archivo.c -> Inclusion del Archivo.h,el desarrollo de todas las funciones, definicion de las variables
 * 
 * Archivo.h
 
 
 */
//Definimos la frecuencia 
#define F_CPU 16000000UL
//Librerias
//#include <xc.h> libreria para xc8
#include <avr/io.h>//Libreria para avr
#include <util/delay.h>
#include "lcd_2x16.h"


int main(void)
{
    Lcd_Init();//Inicializar el modulo LCD
    Lcd_Clear();//Inicio limpiando o borrando la pantalla
    
    while(1)
    {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Felices Fiestas");
        
        Lcd_Set_Cursor(2,3);
        Lcd_Write_String("Patrias PERU");
    }
}