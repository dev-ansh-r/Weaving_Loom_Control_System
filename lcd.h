#include <xc.h> // include processor files - each processor file is guarded.  


#ifndef XC_HEADER_LCD_H
#define	XC_HEADER_LCD_H

#include <xc.h>

#define LCD_ON_CURSOR_BLINKING          0X0F
#define LCD_CLEAR_DISPLAY               0X01
#define LCD_RETURN_HOME                 0X02
#define LCD_RESET                       0X03
#define LCD_DECREMENT_CURSOR            0X10 //(SHIFT CURSOR TO LEFT) 
#define LCD_INCREMENT_CURSOR            0X14 //(SHIFT CURSOR TO RIGHT)
#define LCD_SHIFT_DISPLAY_RIGHT         0X05
#define LCD_SHIFT_DISPLAY_LEFT          0X07
#define LCD_DISPLAY_ON_CURSOR_ON        0X0E
#define LCD_4BYTE_DISPLAY_MODE          0X28
#define LCD_FIRST_LINE                  0X80
#define LCD_SECOND_LINE                 0XC0
#define LCD_2_LINES_AND_5X7_MATRIX      0X38
#define LCD_ACTIVATE_SECOND_LINE        0X3C
#define LCD_DISPLAY_OFF_CURSOR_OFF      0X08
#define LCD_DISPLAY_ON_CURSOR_OFF       0X0C

void LcdInit( void );
void LcdRefresh( void );

void LcdDisplayString(unsigned char RowNum, unsigned char Pos, char * Data);

void LcdDisplayChar(unsigned char RowNum, unsigned char Pos, char  Data);

void LcdDisplayCharNumber(unsigned char RowNum, unsigned char Pos, unsigned char Data);

void LcdClearDisplay (void);

unsigned char LcdDisplayNumber(unsigned char RowNum, unsigned char Pos, unsigned short Data);

void LcdDisplayOnCursorOn( unsigned char RowNum, unsigned char Pos );

void LcdSetPos( unsigned char RowNum, unsigned char Pos );

void LcdDisplayOnCursorOff( void );

void LcdDisplayOffCursorOff( void );

void LcdDisplayShiftCursorRight( void );

void LcdMenuIncrementChar( void );

#endif