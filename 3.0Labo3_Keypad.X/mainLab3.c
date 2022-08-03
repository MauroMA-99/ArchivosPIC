//Definimos la frecuencia, la placa trabaja por defecto a 16MHz
#define F_CPU 16000000UL

#include <avr/io.h>//Libreria para avr
#include <stdint.h>
#include <util/delay.h>
#include "myLibrary/lcd_2x16.h"


int main(void)
{
    Lcd_Init();//Inicializar pantalla LCD
    Lcd_Clear();//Limpiamos pantalla
    while(1)
    {
        for(uint8_t columna = 16; columna>0;columna--)
        {
            Lcd_Set_Cursor(1,columna);
            Lcd_Write_String("Kristel");//Lcd_Write_Char('A');
            _delay_ms(200);
            Lcd_Clear();
        }
        for(uint8_t columna=0;columna<17;columna++)
        {
            Lcd_Set_Cursor(2,columna);
            Lcd_Write_String("Te quiero");
            _delay_ms(200);
            Lcd_Clear();
        }
     
        /*
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Hola Mundo");
         */
    }
}