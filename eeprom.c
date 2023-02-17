/* 
 * File:   eeprom.c
 * Author: Siva V
 *
 * Created on September 7, 2021, 6:05 PM
 */

#include <xc.h>
#include "config.h"
#include "eeprom.h"

unsigned char readEEPROM(unsigned char address)
{
  EEADR = address; //Address to be read
  EECON1.EEPGD = 0;//Selecting EEPROM Data Memory
  EECON1.RD = 1; //Initialise read cycle
  return EEDATA; //Returning data
}

unsigned short ReadEEPROM16b(unsigned short Address)
{
   unsigned short EepromData;
   EepromData = ReadEEPROM(Address + 1);
   EepromData = (EepromData & 0x00ff) << 8;
   EepromData |= ReadEEPROM(Address);
   return EepromData; //Returning data
}

/*void WriteEEPROM(unsigned short Address, unsigned char datas)
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
}*/

void writeEEPROM(unsigned char address, unsigned char datas)
{
    unsigned char INTCON_SAVE;//To save INTCON register value
  EEADR = address; //Address to write
  EEDATA = datas; //Data to write
  EECON1.EEPGD = 0; //Selecting EEPROM Data Memory
  EECON1.WREN = 1; //Enable writing of EEPROM
  INTCON_SAVE=INTCON;//Backup INCON interupt register
  INTCON=0; //Diables the interrupt
  EECON2=0x55; //Required sequence for write to internal EEPROM
  EECON2=0xAA; //Required sequence for write to internal EEPROM
  EECON1.WR = 1; // Initialise write cycle
  INTCON = INTCON_SAVE;//Enables Interrupt
  EECON1.WREN = 0; //To disable write
  while(PIR2.EEIF == 0)//Checking for complition of write operation
  {
    asm nop; //do nothing
  }
  PIR2.EEIF = 0; //Clearing EEIF bit
}

void WriteEeprom16B(unsigned short Address, unsigned short datas)
{
   WriteEEPROM(Address, (unsigned char) ((datas & 0x00ff)));
   DelayMs(5);
   WriteEEPROM(Address + 1, (unsigned char) ((datas & 0xff00) >> 8));
   DelayMs(5);
}