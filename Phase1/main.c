#include <xc.h>
#include "config.h"
#include "lcd.h"

#define _XTAL_FREQ 20000000
int main(void)
{
    LcdInit();
   __delay_ms(1000);
   LcdClearDisplay();
   while(1){ 
   LcdDisplayString(1, 0, " LOOM SETTING ");
   LcdDisplayString(2, 0, " MENU SETTINGS ");
   __delay_ms(1000);
   }
}