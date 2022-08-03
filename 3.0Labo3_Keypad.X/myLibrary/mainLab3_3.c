//Definimos la frecuencia, la placa trabaja por defecto a 16MHz
/*
 * Funcion sprintf(stringConvertido,"%u",contador);
 * 
 *  
 */
#define F_CPU 16000000UL

#include <avr/io.h>//Libreria para avr
#include <stdint.h>
#include <stdio.h>//sprintf();
#include <util/delay.h>
#include "lcd_2x16.h"
#include "keypad_4x4.h"

uint8_t tecla, columna=0;

int main(void)
{
    Lcd_Init();//Inicializar pantalla LCD
    Lcd_Clear();//Limpiamos pantalla
    //Configuramos el teclado 4x4
    Key_Init();
    
    while(1)
    {
        tecla = Key_Read();
        if(tecla != '\0')
        {
            //Imprime en la lcd la tecla presionada
            Lcd_Set_Cursor(1,columna);
            Lcd_Write_Char(tecla);
            columna++;
            
            if(columna>=17)
            {
                Lcd_Clear();
                columna = 0;
            }
                
        }
        /*
        for(contador = 0;contador<=100;contador++)
        {
            //Conversion de datos
            sprintf(strContador, "Cont: %03u", contador);
            //Imprmir datos en la pantalla LCD
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(strContador);
            _delay_ms(200);
        }*/
        
        
        
        
        
        /*for(uint8_t columna = 16; columna>0;columna--)
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
        }*/
     
        /*
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Hola Mundo");
         */
    }
}
