/*
  MCP4922 DAC with SPI
*/

#include "Arduino.h"
#include "MCP4922.h"

//Declare
MCP4922::MCP4922(byte SLAVESELECT0, byte DATAOUT, byte SPICLOCK){
  _DATAOUT = DATAOUT;
  _SPICLOCK = SPICLOCK;
  _SLAVESELECT0 = SLAVESELECT0;
}

//Begin
MCP4922::begin(){
  pinMode(_DATAOUT, OUTPUT);
  pinMode(_SPICLOCK,OUTPUT);
  pinMode(_SLAVESELECT0,OUTPUT);
  
  SPI_setup();

  Write(0,0);
  Write(0,0);
}


void MCP4922::SPI_setup(){

  byte clr;
  digitalWrite(_SLAVESELECT0,HIGH); //disable device

  SPCR = (1<<SPE)|(1<<MSTR) | (0<<SPR1) | (0<<SPR0);
  clr=SPSR;
  clr=SPDR;
  delay(10);
}

// write out through DAC - 0 is DAC A, 1 is DAC B
void MCP4922::Write(int sample, byte DAC)
{
  // splits int sample in to two bytes
  byte dacSPI0 = 0;
  byte dacSPI1 = 0;
  dacSPI0 = (sample >> 8) & 0x00FF;
  
  if(DAC == 1){ dacSPI0 |= (1 << 7);}    //If DAC B: DACa or DACb
  
  dacSPI0 |= 0x10;
  dacSPI1 = sample & 0x00FF;
  dacSPI0 |= (1<<5); 
  
  digitalWrite(_SLAVESELECT0,LOW);
  SPDR = dacSPI0; 
  while (!(SPSR & (1<<SPIF))){ };

  SPDR = dacSPI1;
  while (!(SPSR & (1<<SPIF))){ };
  digitalWrite(_SLAVESELECT0,HIGH);
}