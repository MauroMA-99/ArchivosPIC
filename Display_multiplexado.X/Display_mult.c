#include "Display_mult.h"
void mostrarDisplay(uint8_t numero){
    
    uint8_t uni,dec,j;
    uni=numero%10; /*Obtengo las unidades*/
    dec=numero/10; /*Obtengo las decenas*/
    
    for(j=0;j<200;j++){
        /*Mostramos las unidades*/
        Display = display7a[uni];
        /*Habilitamos el display corrspondiente*/
        Ena &=~ (1<<ena2);
        __delay_ms(1);
        /*Desabilitamos el display*/
        Ena |= (1<<ena2);
        /*Mostramos las decenas*/
        Display=display7a[dec];
        /*Habilitamos el display*/
        Ena &=~(1<<ena1);
        __delay_ms(1);
        /*Deshabilitamos el display*/
        Ena |= (1<<ena1);
    }
}
