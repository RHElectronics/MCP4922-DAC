/*
Example to output a rising voltage on both DACs
Note this doesn't use the SPI library, not tested with other SPI devices other than the MCP4922

Usage: DAC.Write(VALUE,DAC) DAC 0 for A, DAC 1 for B
SLAVESELECT Line can be any pin, SPI bus is fixed. 
Arduino Uno/ATMEGA328 use the settings below

*/
#include <MCP4922.h>
MCP4922 DAC(10,11,13);  //SLAVESELECT, DATAOUT, SPICLOCK

int i;

void setup() {
  // put your setup code here, to run once:

  DAC.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  for(i=0; i<4096; i++){
    DAC.Write(i,0);   //DAC A output
    DAC.Write(i,1);   //DAC B output 

  }


}
