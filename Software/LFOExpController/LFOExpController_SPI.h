#ifndef DWG_SPI_H_
#define DWG_SPI_H_

#include "SPI.h"

#include "LFOExpController_DSP.h"
#include "LFOExpController_ADC.h"
#include "LFOExpController_PCI.h"

//// SPI PIN Definitions
int _MOSI = 3;
int _SCK = 5;
int _SS = 2;

//DIG POT

#define SPI_POTWRITE  0x11
#define SPI_POTSDOWN  0x21

///////////////////////////////
// DAC/SPI specific settings - MCP4921 datasheet http://ww1.microchip.com/downloads/en/DeviceDoc/22248a.pdf
//
// config portion of MCP4921 command register, first 4 bits:
// note that MSB=1 sets ignore flag and LSB=0 sets shutdown

#define SPI_DACSHUTDOWN      0x00
#define SPI_DACUNBUFFX2      0x01
#define SPI_DACUNBUFFX1      0x03
#define SPI_DACBUFFRDX2      0x05
#define SPI_DACBUFFRDX1      0x07
#define SPI_DACIGNORE        0x08

///////////////////////////////////////////////////////
////    void setupSPI()
///////////////////////////////////////////////////////
void SPI_Setup() {
  
  unsigned char sreg;   // save status register and disable interrupts
  sreg = SREG;          //
  cli();                //

    DDRB |= _BV(_SS);               // set SS pin to output before enabling SPI (req. for master)
    
    SPCR |=  _BV(SPE) | _BV(MSTR);  // enable spi as master
    
    DDRB |= _BV(_SCK) | _BV(_MOSI); // set pins to output

  sei();                // enable interrupts and restore status register 
  SREG = sreg;          //
  
}


///////////////////////////////////////////////////////
////    void sendSPIData()
///////////////////////////////////////////////////////
void SPI_SendData() {
  
  PORTB = ~_BV(_SS);    // begin 16bit DIGPOT packet. set slave select LOW
  
  word _newPacket = SPI_POTWRITE;                           // add command byte to 8bit word. 
                                                            // newPacket = 00000000PCOMMAND
  
  
  
  int _sample = DSP_GetAlgorithmicWaveData(DSP_Waveform);
  
  //Serial.println(_sample);

  
  _newPacket = (_newPacket << 8) | _sample;               // shift command left 8 bits and add payload data to the end. 
                                                          // newPacket = PCOMMANDWAVEDATA 
  //Serial.println(_newPacket);
  SPDR = _newPacket >> 8;                                  // send first 8bits... PCOMMAND
  while (!(SPSR & _BV(SPIF))) ; // wait for slave ack
  SPDR = _newPacket & 0xFF;                                // send WAVEDATA
  while (!(SPSR & _BV(SPIF))) ; // wait for slave ack
 
  (DSP_WaveIndex < DSP_SampleResolution) ? DSP_WaveIndex++ : DSP_WaveIndex=0;   // increment the index  
  
  
  PORTB = _BV(_SS);     // 16bit SPI packet finished. set DAC slave select HIGH 
}

#endif
