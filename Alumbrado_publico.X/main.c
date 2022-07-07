
#include "mcc_generated_files/mcc.h"
//#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uart.h"

// Declaracion de funciones
//void Serial_print(char *s);

//void Ultrasonico_Begin(void);
//float Ultrasonico_read(void);
char str_adc_dato[8];
long valor_adc=123;

void main(void)
{
    
    SYSTEM_Initialize();
    char distancia_str[8];
    float distancia;
    //Serial_begin(9600);
    //Serial_print("Xx");

    while (1){
        
        //char Rx=EUSART_Read();
        
        //EUSART_Write(Rx);
        
        uint8_t adc_dato= ADCC_GetSingleConversion(7);
        
        //LCD_goto(1,1);
        //LCD_Integer(adc_dato);
        //LCD_print(" ");
        
        sprintf(str_adc_dato, "%.2f", adc_dato);
        
        PWM6_LoadDutyValue((adc_dato*300/341)+10);
        
        //EUSART_Write(adc_dato);
        
        //Serial_print("Loq");
        
        //printf("%.2f\r\n",adc_dato);
        
        __delay_ms(1000);
    }
}
/*
void Serial_print(char *s){
    while(*s!='\0'){
        EUSART_Write(*s);
        s++;
    }
}*/