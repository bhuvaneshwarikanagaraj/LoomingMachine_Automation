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
    EN = 0; // disable the LCD
    __delay_us(1);
    D4 = (data & 16); // send next bit
    D5 = (data & 32); // send next bit
    D6 = (data & 64); // send next bit
    D7 = (data & 128); // send next bit
    EN = 1; // enable the LCD
    __delay_us(1);
    EN = 0; // disable the LCD