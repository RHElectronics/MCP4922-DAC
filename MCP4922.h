/*
  MCP4922 DAC with SPI
*/
#ifndef MCP4922_h
#define MCP4922_h

#include "Arduino.h"

class MCP4922{

  public:
    MCP4922(byte SLAVESELECT0, byte DATAOUT, byte SPICLOCK);
	begin();
	void Write(int sample,byte DAC);

	
  private:
	byte _CSPin;
	byte _DATAOUT;
	byte _SPICLOCK;
	byte _SLAVESELECT0;
	void SPI_setup();
};

#endif