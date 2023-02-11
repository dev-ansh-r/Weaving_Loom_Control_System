/* 
 * File:   eeprom.c
 * Author: Siva V
 *
 * Created on September 7, 2021, 6:05 PM
 */

#include <xc.h>
#include "config.h"

unsigned char ReadEEPROM(unsigned short Address)
{
   if ((EECON1 & 0x80) == 0x80)
   {
      EECON1 = 0;
   }

   EEADR = Address & 0xff; // Lower Address to be read
   EEADRH = ((Address & 0x300) >> 8); // Higher Address to be read
   EECON1 = 0x01; //Selecting EEPROM Data Memory
   return EEDATA;
}

unsigned short ReadEEPROM16b(unsigned short Address)
{
   unsigned short EepromData;
   EepromData = ReadEEPROM(Address + 1);
   EepromData = (EepromData & 0x00ff) << 8;
   EepromData |= ReadEEPROM(Address);
   return EepromData; //Returning data
}

void WriteEEPROM(unsigned short Address, unsigned char datas)
{
   unsigned char INTCON_SAVE; //To save INTCON register value
   INTCON_SAVE = INTCON; //Backup INCON interrupt register
   INTCON = 0; //Disables the interrupt
   do
   {
      if ((EECON1 & 0x80) == 0x80)
      {
         EECON1 = 0;
      }
      EEADR = Address & 0xff; // Lower Address to be write
      EEADRH = ((Address & 0x300) >> 8); // Higher Address to be write
      EEDATA = datas; //Data to write
      EECON1 = 0x04; //Selecting EEPROM Data Memory, Enable writing of EEPROM
      EECON2 = 0x55; //Required sequence for write to internal EEPROM
      EECON2 = 0xAA; //Required sequence for write to internal EEPROM
      EECON1 |= 0x02; //Initialize write cycle
      //   EECON1 &= ~(1 << 2); //To disable write
      while ((PIR2 & 0x10) != 0x10); //Checking for compilation of write operation
      PIR2 &= ~(1 << 4); //Clearing EEIF bit
   }
   while ((EECON1 & 0x80) == 0x80);
   INTCON = INTCON_SAVE; //Enables Interrupt
}

void WriteEeprom16B(unsigned short Address, unsigned short datas)
{
   WriteEEPROM(Address, (unsigned char) ((datas & 0x00ff)));
   DelayMs(5);
   WriteEEPROM(Address + 1, (unsigned char) ((datas & 0xff00) >> 8));
   DelayMs(5);
}