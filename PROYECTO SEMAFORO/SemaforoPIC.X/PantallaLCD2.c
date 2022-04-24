

#include "PantallaLCD2.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void Define(void){
    ADCON0bits.ADON=0;
    ADCON1=0x0F;
}
void LCD_PUERTO2(unsigned char a)
{
	if(a & 1)
		B4 = 1;
	else
		B4 = 0;

	if(a & 2)
		B5 = 1;
	else
		B5 = 0;

	if(a & 4)
		B6 = 1;
	else
		B6 = 0;

	if(a & 8)
		B7 = 1;
	else
		B7 = 0;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_CMD2(unsigned char a)
{
	RS2 = 0;             // => RS = 0
	LCD_PUERTO2(a);
	EN2  = 1;             // => E = 1
        __delay_ms(4);
        EN2  = 0;             // => E = 0
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_LIMPIAR2( void )
{
	LCD_CMD2(0);
	LCD_CMD2(1);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_POSICION2(unsigned char a, unsigned char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_CMD2(z);
		LCD_CMD2(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		LCD_CMD2(z);
		LCD_CMD2(y);
	}
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_INICIO2( void )
{
  LCD_PUERTO2(0x00);
   __delay_ms(20);
  LCD_PUERTO2(0x03);
	__delay_ms(5);
  LCD_PUERTO2(0x03);
	__delay_ms(11);
  LCD_PUERTO2(0x03);
  /////////////////////////////////////////////////////
  LCD_CMD2(0x02);
  LCD_CMD2(0x02);
  LCD_CMD2(0x08);
  LCD_CMD2(0x00);
  LCD_CMD2(0x0C);
  LCD_CMD2(0x00);
  LCD_CMD2(0x06);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_LETRA2(unsigned char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS2 = 1;                  // => RS2 = 1
   LCD_PUERTO2(y>>4);          //Data transfer
   EN2 = 1;
   __delay_us(40);
   EN2 = 0;
   LCD_PUERTO2(temp);
   EN2 = 1;
   __delay_us(40);
   EN2 = 0;
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_MENSAJE2(unsigned char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_LETRA2(a[i]);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_DESPLAZAMIENTO_DERECHA2( void )
{
	LCD_CMD2(0x01);
	LCD_CMD2(0x0C);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void LCD_DESPLAZAMIENTO_IZQUIERDA2( void )
{
	LCD_CMD2(0x01);
	LCD_CMD2(0x08);
}
//XXXXXXX
void CARACTER2(char data){
EN2 = 0; RS2 = 1;
B7 = (data & 0b10000000)>>7; B6 = (data & 0b01000000)>>6;
B5 = (data & 0b00100000)>>5; B4 = (data & 0b00010000)>>4;
_delay(10);
EN2 = 1; __delay_us(5); EN2 = 0;
B7 = (data & 0b00001000)>>3; B6 = (data & 0b00000100)>>2;
B5 = (data & 0b00000010)>>1; B4 = (data & 0b00000001);
_delay(10);
EN2 = 1; __delay_us(5); EN2 = 0;
__delay_us(5); __delay_us(5500);
}

