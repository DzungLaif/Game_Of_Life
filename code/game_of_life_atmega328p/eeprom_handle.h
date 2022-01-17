/*
 * eeprom_handle.h
 * Created: 1/2/2022 2:42:48 PM
 */ 

#ifndef EEPROM_HANDLE_H_
#define EEPROM_HANDLE_H_

//*** 93C86A IC INSTRUCTION CODE ***//
#define WRITE_OPCODE	0x01
#define READ_OPCODE		0x02
#define ERASE_OPCODE	0x03

#define EWEN_OPCODE		0x00
#define ERAL_OPCODE		0x00
#define WRAL_OPCODE		0x00
#define EWDS_OPCODE		0x00

#define EWEN_ADDRESS	0xC0
#define ERAL_ADDRESS	0x80
#define WRAL_ADDRESS	0x40
#define EWDS_ADDRESS	0x00

//*** PIN MAPPING ***//
#define EEPROM_CS_SSR	DDRB
#define EEPROM_CS_PORT	PORTB
#define EEPROM_CS_BIT	PORTB2

#define EEPROM_CLK_SSR	DDRB
#define EEPROM_CLK_PORT	PORTB
#define EEPROM_CLK_BIT	PORTB3

#define EEPROM_DI_SSR	DDRB		//EEPROM_DI_BIT
#define EEPROM_DI_PORT	PORTB
#define EEPROM_DI_BIT	PORTB4

#define EEPROM_DO_SSR	DDRB		//EEPROM_DO_BIT
#define EEPROM_DO_PORT	PORTB
#define EEPROM_DO_BIT	PORTB5

#define SET_EEPROM_CS_PIN(state) ((state)?(EEPROM_CS_PORT |= (1 << EEPROM_CS_BIT)):(EEPROM_CS_PORT &= ~(1 << EEPROM_CS_BIT)))
#define SET_EEPROM_DI_PIN(state) ((state)?(EEPROM_DI_PORT |= (1 << EEPROM_DI_BIT)):(EEPROM_DI_PORT &= ~(1 << EEPROM_DI_BIT)))
#define SET_EEPROM_DO_PIN(state) ((state)?(EEPROM_DO_PORT |= (1 << EEPROM_DO_BIT)):(EEPROM_DO_PORT &= ~(1 << EEPROM_DO_BIT)))

void eeprom_init(void);
void strobe_sck(void);
void eeprom_opcode(uint8_t code);
void eeprom_address(uint8_t address);
void eeprom_erase(uint8_t address);
void eeprom_eraseall(void);
void eeprom_ew_disable(void);
void eeprom_ew_enable(void);
uint8_t eeprom_read(uint8_t address);
void eeprom_write(uint8_t address, uint8_t data);
void eeprom_writeall(uint8_t data);
void eeprom_writeString(uint8_t start_addr, uint8_t *data_ptr, uint8_t size);
void eeprom_readString(uint8_t start_addr, uint8_t *data_ptr, uint8_t size);

#endif /* 93C86A_HANDLE_H_ */