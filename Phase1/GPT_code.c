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

#endif	/* LCD_H */
