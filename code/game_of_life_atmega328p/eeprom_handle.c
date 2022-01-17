/*
 * eeprom_handle.c
 * Created: 1/2/2022 1:21:13 PM
 */

#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>

#include "eeprom_handle.h"

void eeprom_init(void)
{
	DDRB |= (1 << EEPROM_DI_BIT)| (1 << EEPROM_CLK_BIT)| (1 << EEPROM_CS_BIT);
	
	eeprom_ew_enable();
}

void strobe_sck(void)
{
	PORTB |= (1 << EEPROM_CLK_BIT);
	_delay_ms(1);
	PORTB &= ~(1 << EEPROM_CLK_BIT);
}

void eeprom_opcode(uint8_t code)
{
	PORTB &= ~(1 << EEPROM_CS_BIT);// slave select has to go low >250ns between commands
	strobe_sck();
	
	PORTB |= (1 << EEPROM_CS_BIT)| (1 << EEPROM_DI_BIT);
	strobe_sck();
	
	if (code & 0x02) PORTB |= (1 << EEPROM_DI_BIT);
	else PORTB &= ~(1 << EEPROM_DI_BIT);
	strobe_sck();
	
	if (code & 0x01) PORTB |= (1 << EEPROM_DI_BIT);
	else PORTB &= ~(1 << EEPROM_DI_BIT);
	strobe_sck();
}

void eeprom_address(uint8_t address)
{	
	for (int i = 0; i < 11; i++)
	{
		if (address & 0x80) PORTB |= (1 << EEPROM_DI_BIT);
		else PORTB &= ~(1 << EEPROM_DI_BIT);
		strobe_sck();
		address = address << 1;
	}
}

void eeprom_erase(uint8_t address)
{
	eeprom_opcode(ERASE_OPCODE);			// ERASE instruction
	eeprom_address(address);
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

void eeprom_eraseall(void)
{
	eeprom_opcode(ERAL_OPCODE);				// ERASE ALL instruction
	eeprom_address(ERAL_ADDRESS);
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

void eeprom_ew_disable(void)
{
	eeprom_opcode(EWDS_OPCODE);				// ERASE/WRITE DISABLE instruction
	eeprom_address(EWDS_ADDRESS);
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

void eeprom_ew_enable(void)
{
	eeprom_opcode(EWEN_OPCODE);				// ERASE/WRITE ENABLE instruction
	eeprom_address(EWEN_ADDRESS);
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

uint8_t eeprom_read(uint8_t address)
{
	uint8_t divider = 0x80;
	uint8_t dataword = 0x00;
	
	eeprom_opcode(READ_OPCODE);				// READ instruction
	eeprom_address(address);
	
	strobe_sck();							// Fix a bit offset
	for (uint8_t i = 0; i <= 7; i++)
	{
		if (PINB & (1 << EEPROM_DO_BIT)) dataword = dataword + divider;
		divider = divider >> 1;
		strobe_sck();
	}
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
	
	return dataword;
}

void eeprom_write(uint8_t address, uint8_t data)
{
	eeprom_opcode(WRITE_OPCODE);			// WRITE instruction
	eeprom_address(address);
	
	for (uint8_t bit = 0x80; bit; bit >>= 1)
	{
		if (data & bit) PORTB |= (1 << EEPROM_DI_BIT);
		else PORTB &= ~(1 << EEPROM_DI_BIT);
		strobe_sck();
	}
	
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

void eeprom_writeall(uint8_t data)
{
	eeprom_opcode(WRAL_OPCODE);				// WRITE ALL instruction
	eeprom_address(WRAL_ADDRESS);
	
	for (uint8_t bit = 0x80; bit; bit >>= 1)
	{
		if (data & bit) PORTB |= (1 << EEPROM_DI_BIT);
		else PORTB &= ~(1 << EEPROM_DI_BIT);
		strobe_sck();
	}
	
	PORTB &= ~(1 << EEPROM_CS_BIT);			// Put 93C86A into Standby Mode
}

void eeprom_writeString(uint8_t start_addr, uint8_t *data_ptr, uint8_t size)
{
	for (int i = 0; i < size; i++)
	eeprom_write(start_addr + i, (*(data_ptr + i)));
}

void eeprom_readString(uint8_t start_addr, uint8_t *data_ptr, uint8_t size)
{
	for (int i = 0; i < size; i++)
	*(data_ptr + i) = eeprom_read(start_addr + i);
}