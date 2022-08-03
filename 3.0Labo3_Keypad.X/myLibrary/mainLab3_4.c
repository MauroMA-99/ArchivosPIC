//Definimos la frecuencia, la placa trabaja por defecto a 16MHz
/*
 * Funcion sprintf(stringConvertido,"%u",contador);
 *  
 */
#define F_CPU 16000000UL

#include <avr/io.h>//Libreria para avr
#include <stdint.h>
#include <stdio.h>//sprintf();
#include <string.h>//Val = strcmp(str1,str2); retorna un valor 0:cadenas iguales, 1:cadenas diferentes
#include <util/delay.h>
#include "lcd_2x16.h"
#include "keypad_4x4.h"
//Definir estados de la aplicacion
#define ESTADO_INGRESO_CLAVE            0
#define ESTADO_VERIFICACION             1 
#define ESTADO_INGRESO_CORRECTO         2
#define ESTADO_INGRESO_INCORRECTO       3
uint8_t tecla, columna = 1, indice = 0;
uint8_t appstate = ESTADO_INGRESO_CLAVE;

//5 caracteres para la clave del ususario
char claveUsuario[5] = "*50#";
//5 caracteres para la clave ingresada
char claveIngresada[5];

int main(void) {
    Lcd_Init(); //Inicializar pantalla LCD
    Lcd_Clear(); //Limpiamos pantalla
    //Configuramos el teclado 4x4
    Key_Init();

    //Data LCD
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Ingrese Clave");

    while (1) {
        switch (appstate) {
            case ESTADO_INGRESO_CLAVE:
                //Leer la clave ingresada
                tecla = Key_Read();
                if (tecla != '\0') {
                    //Columna empieza en 0
                    Lcd_Set_Cursor(2, columna);
                    Lcd_Write_Char(tecla);
                    //Imprimo la tecla
                    claveIngresada[indice] = tecla;
                    //almaceno la tecla
                    indice++;
                    columna++;
                    if (columna >= 5) {
                        _delay_ms(1000);
                        columna = 0;
                        appstate = ESTADO_VERIFICACION;
                        Lcd_Clear();
                    }
                }

                break;
                /////////////////////////
            case ESTADO_VERIFICACION:
                //Verificar clave ingresada
                if (0 == strcmp(claveUsuario, claveIngresada)) {
                    appstate = ESTADO_INGRESO_CORRECTO;
                } else {
                    appstate = ESTADO_INGRESO_INCORRECTO;
                }
                break;
            case ESTADO_INGRESO_CORRECTO:
                //Codigo Ingreso Correcto
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("Ingreso ok");
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String("Motor ON");
                break;
                ///////////////////////
            case ESTADO_INGRESO_INCORRECTO:
                //Codigo Ingreso Incorrecto
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("No Ingreso");
                Lcd_Set_Cursor(2, 1);
                Lcd_Write_String("Motor OFF");
                break;
        }

    }
}

