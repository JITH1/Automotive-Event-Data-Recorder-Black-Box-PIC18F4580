#ifndef EXT_H
#define EXT_H 

extern volatile unsigned char write_count ; 
extern volatile unsigned char init_add ;
extern unsigned char store_string[16][17];

void EEPROM_wrtie(unsigned char *Tx_string);
void EEPROM_read(unsigned char *Rx_string);
void EEPROM_clear(void);

#endif