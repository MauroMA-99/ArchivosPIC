

#include "USART.h"

void Config_EUART(uint16_t Baudios){
    uint16_t n=0;
    TRISCbits.RC6=0;            // SALIDA TX
    TRISCbits.RC7=1;            // ENTRADA RX
    TXSTA=0b00100100;           // CONFIGURACIÓN TRANSMISIÓN
    RCSTA=0b10010000;           // CONFIGURACIÓN RECEPCIÓN
    BAUDCON=0b00001000;         // CONFIGURACIÓN BAUDIOS
    // FOSC=4MHz   B=9600 Baudios
    // n=((FOSC/BAUDIOS)/4)-1   n=((4MHz/9600)/4)-1=103 
    n=(uint16_t)((_XTAL_FREQ/Baudios)/4)-1;
    SPBRG=n;
    SPBRGH=(n>>8);
}

void EnviarCaracter_USART(char caracter){
    TXREG = caracter;
    while(TXSTAbits.TRMT == 0); //Esperar hasta que se complete la transmision
}

void EnviarMensaje_USART(char *data){
    while(*data!=NULL){
        TXREG=*data;
        while(TXSTAbits.TRMT==0);
        data++;
    }
}
void EnviarVariable_USART(char *String, char *Variable){
    while(*String != '\0'){
        EnviarCaracter_USART(*String);
        String++;
    }
    
    while(*Variable != '\0'){
        EnviarCaracter_USART(*Variable);
        Variable++;
    }
}
char RecibirCaracter_USART(void){
    while(PIR1bits.RCIF == 0); //Esperar hasta que se reciba 1 datos por UART
    //Evaluar el desbordamiento
    if(RCSTAbits.OERR == 1){
        RCSTAbits.CREN = 0;
        NOP(); //Realizo un reatardo de 1 ciclo maquina
        RCSTAbits.CREN = 1;
    }
    return (RCREG);
}
void RecibirString_USART(char *Buffer, unsigned int len){
    uint8_t i;
    unsigned char data;
    uint32_t timeout=12000000;
    
    for(i=0;i<len;i++){
        while(PIR1bits.RCIF==0){
            timeout--;
            if(timeout==0){
                return;
            }
        }
        data=RecibirCaracter_USART();
        *Buffer=data;
         Buffer++;
    } 
    
}