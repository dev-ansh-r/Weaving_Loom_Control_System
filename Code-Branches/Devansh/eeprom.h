 #ifndef XC_HEADER_EEPROM_H
#define	XC_HEADER_EEPROM_H

unsigned char ReadEEPROM(unsigned short address);
unsigned short ReadEEPROM16b(unsigned short Address);
void WriteEEPROM(unsigned short address, unsigned char datas);
void WriteEeprom16B(unsigned short Address, unsigned short datas);
#endif	/* XC_HEADER_TEMPLATE_H */
