

#ifndef USART_H
#define	USART_H

#define _XTAL_FREQ 4000000UL
#include <xc.h>
#include <stdint.h>

void Config_EUART(uint16_t Baudios);     // CONFIGURO EL PUERTO EUSART
void EnviarMensaje_USART(char *data);    // ENVIA UN STRING
void EnviarCaracter_USART(char caracter);// ENVIA UN CARACTER
void EnviarVariable_USART(char *String, char *Variable); // ENVIAR UN STRING CON UNA VARIABLE
char RecibirCaracter_USART(void);        // RECIBE UN CARACTER
void RecibirString_USART(char *Buffer, unsigned int len); // RECIBE UN STRING

#endif	/* USART_H */