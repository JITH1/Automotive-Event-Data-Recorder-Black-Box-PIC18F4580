#ifndef EXT_H
#define EXT_H 

extern volatile unsigned char write_count ; 
extern unsigned char store_string[16][17];
extern volatile unsigned char address ;

void EEPROM_wrtie(unsigned char *Tx_string);
void EEPROM_read(unsigned char str[][17]);
void EEPROM_clear(void);

#endif