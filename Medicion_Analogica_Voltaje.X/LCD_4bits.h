/* 
 * File:   LCD_4bits.h
 * Author: jhona
 *
 * Created on 9 de agosto de 2019, 10:35 PM
 */

#ifndef LCD_4BITS_H
#define	LCD_4BITS_H
/*Definiciones del LCD, modificar segun proyecto*/
#include <xc.h>
#define _XTAL_FREQ 8000000
#include <stdint.h>
#define RS          2          /*Modificar segun bit para RS de 0-3*/
#define EN          3          /*Modificar segun bit para EN de 0-3*/
#define data        LATD       /*Modificar segun puerto de coneccion*/
#define LCD_Port    TRISD

/*Modificar segun puerto de coneccion*/

/*Declaracion de funciones*/

/*LCD_Begin(void): Inicializa la pantalla LCD*/
void LCD_Begin(void);
/*LCD_Command: Envia un comando de datos*/
void LCD_Command(uint8_t dat);
/*LCD_Clear: Limpia la pantalla*/
void LCD_Clear(void);
/*LCD_Char: Imprime un caracter x en LCD*/
void LCD_Char(char x);
/*LCD_Print: Imprime una cadena str en LCD*/
void LCD_Print(const char* str);
/*LCD_setCursor: Ajusta el cursor en la columna x,fila y*/
void LCD_setCursor(uint8_t x,uint8_t y);

#endif	/* LCD_4BITS_H */

