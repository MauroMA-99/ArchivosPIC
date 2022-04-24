
#include "PantallaLCD.h"


void LCD_PUERTO(unsigned char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}

void LCD_CMD(unsigned char a)
{
	RS = 0;             //  RS = 0
	LCD_PUERTO(a);
	EN  = 1;             //  E = 1
        __delay_ms(4);
        EN  = 0;             //  E = 0
}

void LCD_LIMPIAR( void )
{
	LCD_CMD(0);
	LCD_CMD(1);
}

void LCD_POSICION(unsigned char a, unsigned char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_CMD(z);
		LCD_CMD(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_CMD(z);
		LCD_CMD(y);
	}
}

void LCD_INICIO( void )
{
  LCD_PUERTO(0x00);
   __delay_ms(20);
  LCD_CMD(0x03);
	__delay_ms(5);
  LCD_CMD(0x03);
	__delay_ms(11);
  LCD_CMD(0x03);

  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}

void LCD_LETRA(unsigned char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;                  //  RS = 1
   LCD_PUERTO(y>>4);          //transferencia de datos
   EN = 1;
   __delay_us(40);
   EN = 0;
   LCD_PUERTO(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void LCD_MENSAJE(unsigned char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_LETRA(a[i]);
}

void LCD_DESPLAZAMIENTO_DERECHA( void )
{
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
}

void LCD_DESPLAZAMIENTO_IZQUIERDA( void )
{
	LCD_CMD(0x01);
	LCD_CMD(0x08);
}

void CARACTER(char data){
EN = 0; RS = 1;
D7 = (data & 0b10000000)>>7; RD6 = (data & 0b01000000)>>6;
D5 = (data & 0b00100000)>>5; RD4 = (data & 0b00010000)>>4;
_delay(10);
EN = 1; __delay_us(5); EN = 0;
D7 = (data & 0b00001000)>>3; RD6 = (data & 0b00000100)>>2;
D5 = (data & 0b00000010)>>1; RD4 = (data & 0b00000001);
_delay(10);
EN = 1; __delay_us(5); EN = 0;
__delay_us(5); __delay_us(5500);
}

