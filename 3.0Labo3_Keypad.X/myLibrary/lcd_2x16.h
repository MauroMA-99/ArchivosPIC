/* 
 * File:   lcd_2x16.h
 * Author: PC1
 *
 * Created on July 26, 2022, 6:17 AM
 */

#ifndef LCD_2X16_H
#define	LCD_2X16_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//****************************************************************************
//    CONFIGURACIÓN DE LOS PINES DE INTERFACE
//****************************************************************************

/* Define el puerto a donde se conectará el BUS de datos del LCD
 * Se utilizará el nible alto del puerto escogido (ejem. PB4-DB4,...,PB7-DB7) */
#define  LCD_DATA_OUT   PORTD      // Registro PORTx del puerto
#define  LCD_DATA_DDR   DDRD       // Registro DDRx del puerto

/* Define el puerto a donde se conectarán las líneas de control del LCD
 * EN y RS (Puede ser el mismo puerto del BUS de datos) */
#define  LCD_CTRL_OUT   PORTD      // Registro PORT del puerto
#define  LCD_CTRL_DDR   DDRD       // Registro DDR del puerto

//Define los numeros de bits a donde se conectará el modulo LCD
#define RS	2 	// Pin Register Select
#define EN	3	// Pin Enable
#define D4	4	//define el pin del MCU conectado LCD D4
#define D5	5	//define el pin del MCU conectado LCD D5
#define D6	6	//define el pin del MCU conectado LCD D6
#define D7	7	//define el pin del MCU conectado LCD D7

//Prototipo de funciones 
void Lcd_Port(unsigned char a);
void Lcd_Cmd(unsigned char a);
void Lcd_Init( void );
void Lcd_Clear( void );
void Lcd_Set_Cursor(unsigned char a, unsigned char b);
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right( void );
void Lcd_Shift_Left( void );

#endif	/* LCD_2X16_H */

