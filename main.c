
// PIC18F46K22 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config FOSC = HSHP      // Oscillator Selection bits (HS oscillator (high power > 16 MHz))
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include "lcd.h"

#define _XTAL_FREQ 8000000 // frequency of the crystal oscillator

void main() {
    TRISD = 0x00; // configure PORTD as output
    TRISBbits.TRISB7 = 1; // configure RB7 as input
    LCD_Init(); // initialize the LCD
    while(1) {
        if(PORTBbits.RB7 == 1) { // check if RB7 is high
            LCD_Write_String("TITLE"); // write "TITLE" to the LCD
        } else {
            LCD_Command(0x01); // clear the display
        }
    }
}

#include "lcd.h"

void LCD_Init() {
    __delay_ms(20); // wait for 20 milliseconds
    LCD_Command(0x38); // set 8-bit mode, 2 lines, and 5x7 font
    LCD_Command(0x0C); // turn on display and cursor
    LCD_Command(0x06); // set cursor direction to right
    LCD_Command(0x01); // clear the display
}

void LCD_Command(unsigned char cmd) {
    RS = 0; // select command register
    D4 = (cmd & 1); // send least significant bit (LSB)
    D5 = (cmd & 2); // send next bit
    D6 = (cmd & 4); // send next bit
    D7 = (cmd & 8); // send most significant bit (MSB)
    EN = 1; // enable the LCD
    __delay_us(1); // wait for 1 microsecond
    EN = 0; // disable the LCD
    __delay_us(1); // wait for 1 microsecond
    D4 = (cmd & 16); // send next bit
    D5 = (cmd & 32); // send next bit
    D6 = (cmd & 64); // send next bit
    D7 = (cmd & 128); // send next bit
    EN = 1; // enable the LCD
    __delay_us(1); // wait for 1 microsecond
    EN = 0; // disable the LCD
    __delay_ms(2); // wait for 2 milliseconds
}

void LCD_Char(unsigned char data) {
    RS = 1; // select data register
    D4 = (data & 1); // send LSB
    D5 = (data & 2); // send next bit
    D6 = (data & 4); // send next bit
    D7 = (data & 8); // send MSB
    EN = 1; // enable the LCD
    __delay_us(1);


#ifndef LCD_H
#define	LCD_H

#define RS RD0
#define EN RD1
#define D4 RD2
#define D5 RD3
#define D6 RD4
#define D7 RD5

void LCD_Init();
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void LCD_Write_String(const char *str);

#endif	/* LCD_H *
    while(1) {
        
    }
}