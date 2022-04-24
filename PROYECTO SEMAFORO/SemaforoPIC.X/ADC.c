
#include <xc.h>
#include <stdint.h>
void Config_ADC(void){
    ADCON0bits.ADON=0;       // HABILITO MODULO ADC
    ADCON1bits.VCFG=0b00;    // VREF+=VCC  VERF-=VSS
    ADCON1bits.PCFG=0b1101;  // ALGUNOS CANALES ANALOGICOS
    ADCON2bits.ADFM=1;       // JUSTIFICACIÓN DERECHA
    ADCON2bits.ACQT=0b010;   // A/D Acquisition Time = 4TAD 
    ADCON2bits.ADCS=0b100;   // FOSC/4 ==> TAD=1us>0.8us
    ADCON0bits.ADON=1;       // HABILITO MODULO ADC
    ADCON0bits.GO_DONE=0;    // TODAVIA NO EMPIEZO LA CONVERSIÓN
}

uint16_t Canal_ADC(uint8_t canal){
    ADCON0bits.CHS=canal;    // SELLECIONO EL CANAL DEL ADC
    ADCON0bits.GO_DONE=1;    // INICIALIZO LA CONVERSIÓN
    while(ADCON0bits.GO_DONE==1);  // ESPERO QUE TERMINE LA CONVERSIÓN   
    return (ADRESH<<8)+ADRESL;
}
