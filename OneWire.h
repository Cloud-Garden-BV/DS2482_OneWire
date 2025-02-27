#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include <stddef.h>
#include <inttypes.h>
#include <vne_i2c.h>
#include "Arduino.h"


// Chose between a table based CRC (flash expensive, fast)
// or a computed CRC (smaller, slow)
#define ONEWIRE_CRC8_TABLE 			1

#define DS2482_COMMAND_RESET		0xF0	// Device reset

#define DS2482_COMMAND_SRP			0xE1 	// Set read pointer
	#define DS2482_POINTER_STATUS		0xF0
		#define DS2482_STATUS_BUSY			(1<<0)
		#define DS2482_STATUS_PPD			(1<<1)
		#define DS2482_STATUS_SD			(1<<2)
		#define DS2482_STATUS_LL			(1<<3)
		#define DS2482_STATUS_RST 			(1<<4)
		#define DS2482_STATUS_SBR			(1<<5)
		#define DS2482_STATUS_TSB 			(1<<6)
		#define DS2482_STATUS_DIR 			(1<<7)
	#define DS2482_POINTER_DATA			0xE1
	#define DS2482_POINTER_CONFIG		0xC3
		#define DS2482_CONFIG_APU			(1<<0)
		#define DS2482_CONFIG_SPU			(1<<2)
		#define DS2482_CONFIG_1WS			(1<<3)


#define DS2482_COMMAND_WRITECONFIG	0xD2
#define DS2482_COMMAND_RESETWIRE	0xB4
#define DS2482_COMMAND_WRITEBYTE	0xA5
#define DS2482_COMMAND_READBYTE		0x96
#define DS2482_COMMAND_SINGLEBIT	0x87
#define DS2482_COMMAND_TRIPLET		0x78

#define WIRE_COMMAND_SKIP			0xCC
#define WIRE_COMMAND_SELECT			0x55
#define WIRE_COMMAND_SEARCH			0xF0

#define DS2482_ERROR_TIMEOUT		(1<<0)
#define DS2482_ERROR_SHORT			(1<<1)
#define DS2482_ERROR_CONFIG			(1<<2)

class OneWire
{
public:
	OneWire( VNE_WIRE *UseWire);
	OneWire(uint8_t address,  VNE_WIRE *UseWire);

	uint8_t getAddress();
	uint8_t getError();
	uint8_t checkPresence();
	// I2C helper functions
	uint8_t I2CGetByte(uint8_t address);
	uint8_t I2CGetByteFrom(uint8_t address, uint8_t reg);
	void I2CSetByte(uint8_t address, uint8_t reg, uint8_t value);
	void I2CSetAddress(uint8_t address, uint8_t value);


	void deviceReset();
	void setReadPointer(uint8_t readPointer);
	uint8_t readStatus();
	uint8_t readData();
	uint8_t waitOnBusy();
	uint8_t readConfig();
	void writeConfig(uint8_t config);
	void setStrongPullup();
    uint8_t setChannel(uint8_t ch);
	void clearStrongPullup();
	void clearActivePullup();
	void setActivePullup();
	uint8_t wireReset();
	void wireWriteByte(uint8_t data, uint8_t power = 0);
	uint8_t wireReadByte();
	void wireWriteBit(uint8_t data, uint8_t power = 0);
	uint8_t wireReadBit();
	void wireSkip();
	void wireSelect(const uint8_t rom[8]);
	void wireResetSearch();
	uint8_t wireSearch(uint8_t *address);

	// emulation of original OneWire library
	void reset_search();
	uint8_t search(uint8_t *newAddr);
	static uint8_t crc8(const uint8_t *addr, uint8_t len);
	uint8_t reset(void);
	void select(const uint8_t rom[8]);
	void skip(void);
	void write(uint8_t v, uint8_t power = 0);
	uint8_t read(void);
	uint8_t read_bit(void);
	void write_bit(uint8_t v);
	void printError();

private:
	void writeByte(uint8_t);
	uint8_t readByte();

	uint8_t mAddress;
	uint8_t mError;
	VNE_WIRE *_Wire;

	uint8_t searchAddress[8];
	uint8_t searchLastDiscrepancy;
	uint8_t searchLastDeviceFlag;
};

#endif
