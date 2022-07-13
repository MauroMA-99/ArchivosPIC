#include "LCD_4bits.h"

/*Definicion de funciones*/
void LCD_Begin(){
    __delay_ms(15);     /*Tiempo de espera inicia pantalla*/
    /*SAlida para control RS, E y  salida data D4-D7*/
    LCD_Port &=~((1<<RS)|(1<<EN)|(0b11110000));
    LCD_Command(0x02);
    LCD_Command(0x28);  /*Modo 4bits,usa dos lineas y matriz de 5x8 de letra*/
    LCD_Command(0x01);  /*Limpia pantalla- clear*/
    LCD_Command(0x0C);  /*Desactiva visualizacion de cursor*/
    LCD_Command(0x06);  /*Incrementa cursor*/
}

void LCD_Clear(void){
    LCD_Command(0x01);  /*Limpia la pantalla*/
    __delay_ms(1);
}

void LCD_Command(uint8_t dat){
    data = (data & 0x0F)|(dat & 0xF0); /*Envia la parte alta datH*/
    data &=~(1<<RS);    /*RS =0 seleccion registro de comando*/
    data |=(1<<EN);     /*EN=1*/
    Nop();
    data &=~(1<<EN);    /*EN=0*/
    __delay_ms(1);
    data = (data & 0x0F)|(dat<<4); /*Envia la parte baja datL*/
    data |=(1<<EN);     /*EN=1*/
    Nop();
    data &=~(1<<EN);    /*EN=0*/
    __delay_ms(3);      
}
void LCD_Char(char x){
    data = (data & 0x0F)|(x & 0xF0);         /*Envia la parte alta de xH*/
    data |=(1<<RS);     /*RS =1 */
    data |=(1<<EN);     /*EN=1*/
    Nop();
    data &=~(1<<EN);
    data = (data & 0x0F)|(x<<4);            /*Envia la parte baja de xL*/
    data |=(1<<EN);
    Nop();
    data &=~(1<<EN);    /*EN=0*/
    __delay_ms(3);    
}
void LCD_Print(const char* str){
    while((*str)!=0){
        LCD_Char(*str);
        str++;
    }
}
void LCD_setCursor(uint8_t x,uint8_t y){
    uint8_t location=0;
    switch(y){
        case 0:
        /*coloca el cursor del mensaje en la primera fila*/
        location=(0x80)|((x)&0x0F);
        LCD_Command(location);
        break;
        case 1:
        /*coloca el cursos del mensaje en la segunda fila*/
        location=(0xC0)|((x)&0x0F);
        LCD_Command(location);
        break;
    }
}

