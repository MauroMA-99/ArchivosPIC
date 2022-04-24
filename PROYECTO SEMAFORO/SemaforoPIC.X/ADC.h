
#ifndef ADC_10BITS_H
#define	ADC_10BITS_H

#define _XTAL_FREQ 4000000UL
#include <xc.h>

// FUNCIONES
void Config_ADC(void);
uint16_t Canal_ADC(uint8_t canal);

#endif	/* ADC_10BITS_H */