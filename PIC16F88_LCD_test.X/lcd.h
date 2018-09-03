#ifndef LCD_H
#define LCD_H


#include "config.h"         // For the pinout, and the clock frequency for __delay_ms()


void LCD_set_port (unsigned char value_4_bit){
// 4-bit operations are used
    if (value_4_bit & 0x1) D4 = 1;
    else                   D4 = 0;

    if (value_4_bit & 0x2) D5 = 1;
    else                   D5 = 0;

    if (value_4_bit & 0x4) D6 = 1;
    else                   D6 = 0;

    if (value_4_bit & 0x8) D7 = 1;
    else                   D7 = 0;
}


void LCD_command (unsigned char command) {
    RS = 0;                     // Clear the RS bit to enter the COMMAND mode (otherwise DATA mode is used)
    LCD_set_port (command);     // Send the command to the port
    EN = 1;                     // Tell the device that the command set is a valid command (enable)
    __delay_ms (5);             // Wait a few milliseconds
    EN = 0;                     // Disable
}


void LCD_clear () {
    // Send the CLEAR command (0x01 devided onto 2 4-bit instructions)
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0x1);
}


void LCD_set_cursor (char row, char column) {
    // The current LCD device is 20x4
    if (row < 0 || row > 4 || column < 0 || column > 20) return;

    unsigned char ddram_address = 0x80;    // This is the bit pattern holding the DDRAM address of the position in the 20x4 matrix

    if      (row == 1) ddram_address += 0x00 + (column - 1);
    else if (row == 2) ddram_address += 0x40 + (column - 1);
    else if (row == 3) ddram_address += 0x14 + (column - 1);
    else if (row == 4) ddram_address += 0x54 + (column - 1);

    LCD_command (unsigned char) (ddram_address >> 4);   // Send the 4 MSBs
    LCD_command (unsigned char) (ddram_address & 0x0F); // Then the 4 LSBs
}


void LCD_Init () {
    // Check the datasheet for the following procedure
    __delay_ms (20);
    LCD_command (unsigned char) (0x3);
    __delay_ms (20);
    LCD_command (unsigned char) (0x3);
    __delay_ms (20);
    LCD_command (unsigned char) (0x3);

    __delay_ms (20);
    LCD_command (unsigned char) (0x2);      // Setup 4-bit mode

    // Since we are using 4-bit mode, every command must be splitted into 2 4-bit commands
    // Use the double lines (2 lines x 40 characters == 4 x 20) with 5x8 font size
    __delay_ms (20);
    LCD_command (unsigned char) (0x2);
    LCD_command (unsigned char) (0x8);

    __delay_ms (20);
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0xC);

    // Set the display off
    __delay_ms (20);
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0x8);

    // Clear the display
    __delay_ms (20);
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0x1);

    //Entry mode set - I/D = 1 (increment cursor) & S = 0 (no shift)
    __delay_ms (20);
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0x6);

    //Display on/off control. D = 1, C and B = 0. (Cursor and blink, last two bits)
    __delay_ms (20);
    LCD_command((unsigned char) 0x0);
    LCD_command((unsigned char) 0xC);
}


void LCD_write_char (char c) {
    RS = 1;                             // Set input to be DATA

    LCD_set_port (c >> 4);       // Send higher 4 bits
    EN = 1;                             // Enable the reading of the bits sent
    __delay_us (50);
    EN = 0;

    LCD_set_port (c & 0x0F);
    EN = 1;
    __delay_us (50);
    EN = 0;
}


void LCD_write_string (char * str) {
    unsigned char j;
    for (j = 0; str[j] != '\0'; ++j) {
        LCD_write_char (str[j]);
    }
}


void LCD_shift_right()
{
    LCD_command((unsigned char) 0x01);
    LCD_command((unsigned char) 0x0C);
}

void LCD_shift_left()
{
    LCD_command((unsigned char) 0x01);
    LCD_command((unsigned char) 0x08);
}



#endif /*LCD_H*/