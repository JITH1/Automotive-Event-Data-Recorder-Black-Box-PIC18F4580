#include <xc.h>
#include "clcd.h"
#include "Clock.h"
#include "adc.h"
#include "Matrix_keypad.h"

unsigned char line1_buffer[17] = "   RTC   GEAR SPD";
unsigned char line2_buffer[17];

void clcd_write(unsigned char byte, unsigned char control_bit)
{
	CLCD_RS = control_bit;
	CLCD_PORT = byte;

	/* Should be atleast 200ns */
	CLCD_EN = HI;
	CLCD_EN = LO;

	PORT_DIR = INPUT;
	CLCD_RW = HI;
	CLCD_RS = INSTRUCTION_COMMAND;

	do
	{
		CLCD_EN = HI;
		CLCD_EN = LO;
	} while (CLCD_BUSY);

	CLCD_RW = LO;
	PORT_DIR = OUTPUT;
}

void init_clcd()
{
	/* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;

	CLCD_RW = LO;

	CURSOR_HOME;
	TWO_LINE_5x8_MATRIX_8_BIT;
	DISP_ON_AND_CURSOR_OFF;
	CLEAR_DISP_SCREEN;
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	clcd_write(data, DATA_COMMAND);
}

void get_line2(unsigned char line2_buffer[])
{
     sprintf(line2_buffer,"%02d:%02d:%02d  %u",hr,min,sec,(unsigned int)(speed/10.23));
}
