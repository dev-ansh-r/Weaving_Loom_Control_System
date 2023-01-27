#include <xc.h>
#include "lcd.h"
#include "config.h"
#define LATD LATD
#define TRISD TRISD

static char DataArray[5];

#define _XTAL_FREQ 20000000

static void SendLcdCommand( unsigned char Command)
{
    LATD &= ~(1<<2); //  Register Select as Command
    LATD = (Command & 0XF0)|(LATD &0x0F) ; // Write 4 bit MSB in Data line 
    
    LATD |= (1<<3); // LCD Enable
    __delay_ms(5); // Delay
    LATD &= ~(1<<3); // LCD Disable
    
    LATD = (unsigned char)((Command & 0X0F) << 4) |(LATD &0x0F); // Write 4 bit LSB in Data line 
    
    LATD |= (1<<3); // LCD Enable
    __delay_ms(5); // Delay
    LATD &= ~(1<<3); // LCD Disable
}

static void SendLcdData( unsigned char Data)
{
    LATD |= (1<<2); //  Register Select as Data
    LATD = (Data & 0XF0) |(LATD &0x0F) ; // Write 4 bit MSB in Data line 
    
    LATD |= (1<<3); // LCD Enable
    __delay_ms(5); // Delay
    LATD &= ~(1<<3); // LCD Disable
    
    LATD = (unsigned char)((Data & 0X0F) << 4) |(LATD &0x0F); // Write 4 bit LSB in Data line 
    
    LATD |= (1<<3); // LCD Enable
    __delay_ms(5); // Delay
    LATD &= ~(1<<3); // LCD Disable
}

void LcdRefresh( void )
{
    TRISD = 0; //  Select All Pins as Output
    LATD = 0xff;
    __delay_ms(2); // Delay
    LATD = 0;
    SendLcdCommand( LCD_RESET ); //  LCD Reset
}

void LcdInit( void )
{
    TRISD = 0; //  Select All Pins as Output
    LATD = 0;
    __delay_ms(1); // Delay
    SendLcdCommand( LCD_RESET ); //  LCD Reset
    __delay_ms(5); // Delay
    SendLcdCommand( LCD_RESET ); //  LCD Reset
    __delay_ms(5); // Delay
    SendLcdCommand(LCD_RESET); //  LCD Reset
    __delay_ms(5); // Delay
    SendLcdCommand(LCD_RESET); //  LCD Reset
    __delay_ms(5); // Delay
    SendLcdCommand( LCD_RETURN_HOME); //  Set LCD command as 4 byte mode
    SendLcdCommand( LCD_4BYTE_DISPLAY_MODE); // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    SendLcdCommand( LCD_INCREMENT_CURSOR); //Shift cursor to left 
    SendLcdCommand( LCD_CLEAR_DISPLAY); // Clear display screen
    SendLcdCommand( LCD_DISPLAY_ON_CURSOR_OFF); // Display ON Cursor Off
}

void LcdDisplayString(unsigned char RowNum, unsigned char Pos, char * Data)
{
    if( RowNum == 1)
    {
        SendLcdCommand(LCD_FIRST_LINE | Pos);
    }
    else if( RowNum == 2)
    {
        SendLcdCommand(LCD_SECOND_LINE | Pos);
    }

    while( *Data != '\0')
    {
        SendLcdData(*Data);
        Data++;
    }
}

void LcdDisplayChar(unsigned char RowNum, unsigned char Pos, char  Data)
{
    if( RowNum == 1)
    {
        SendLcdCommand(LCD_FIRST_LINE | Pos);
    }
    else if( RowNum == 2)
    {
        SendLcdCommand(LCD_SECOND_LINE | Pos);
    }
    
    SendLcdData(Data);
}

unsigned char ValidateNumber( char *Data )
{
    while( *Data != 0)
    {
        if( (*Data < '0') || (*Data>'9') )
        {
            return 0;
        }
        Data++;
    }
    return 1;
}

void LcdDisplayCharNumber(unsigned char RowNum, unsigned char Pos, unsigned char Data)
{
   if ((Data >= '0') && (Data <= '9'))
   {
      LcdDisplayChar(RowNum, Pos, Data);
   }
   else
   {
      LcdDisplayChar(RowNum, Pos, '0');
   }
}

unsigned char LcdDisplayNumber(unsigned char RowNum, unsigned char Pos, unsigned short Data)
{
    DataArray[0] = (unsigned char)(((Data)/1000)+48);
    DataArray[1] = (unsigned char) ((((Data)/100)%10)+48);
    DataArray[2] = (unsigned char) ((((Data)/10)%10)+48);
    DataArray[3] = (unsigned char)(((Data)%10)+48);
    DataArray[4] = 0;
    if( ValidateNumber(DataArray))
    {
        LcdDisplayString(RowNum,Pos,DataArray);
        return 1;
    }
    else
    {
       LcdDisplayString(RowNum,Pos,"0000"); 
       return 0;
    }
}

void LcdClearDisplay( void )
{
    SendLcdCommand( LCD_CLEAR_DISPLAY); // Clear display screen
}

void LcdDisplayOnCursorOn( unsigned char RowNum, unsigned char Pos )
{
    SendLcdCommand( LCD_ON_CURSOR_BLINKING); // Display ON Cursor ON
    
    if( RowNum == 1)
    {
        SendLcdCommand(LCD_FIRST_LINE | Pos);
    }
    else if( RowNum == 2)
    {
        SendLcdCommand(LCD_SECOND_LINE | Pos);
    }
}

void LcdDisplayOnCursorOff( void )
{
    SendLcdCommand( LCD_DISPLAY_ON_CURSOR_OFF); // Display ON Cursor Off
}

void LcdDisplayOffCursorOff( void )
{
    SendLcdCommand( LCD_DISPLAY_OFF_CURSOR_OFF ); // Display OFF Cursor Off
}

void LcdDisplayShiftCursorRight( void )
{
    SendLcdCommand( LCD_INCREMENT_CURSOR ); // Display ON Cursor Off
}

void LcdSetPos( unsigned char RowNum, unsigned char Pos )
{
    if( RowNum == 1)
    {
        SendLcdCommand(LCD_FIRST_LINE | Pos);
    }
    else if( RowNum == 2)
    {
        SendLcdCommand(LCD_SECOND_LINE | Pos);
    }
}