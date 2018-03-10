
// DWG auxiliary source
#include "LFOExpController_CLK.h"
#include "LFOExpController_SPI.h"



unsigned long DWG_LastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long DWG_DebounceDelay = 400;    // the debounce time; increase if the output flickers
volatile uint8_t DWG_Portdhistory = 0xFF; 

void setup() {
  Serial.begin(9600);
 
  
  PCI_Setup();
  CLK_Setup();
  DSP_Setup();
  SPI_Setup();
  ADC_Setup();
  
}

void loop() {
  int _freqLow = 2;         // increases lower limit of frequency range
  int _logTaper = 384;      // audio/log taper 
  
  if (ADC_FreqInput > 10) {
    // add log taper so that linear potentiometer can be used.
    OCR1A = map(ADC_FreqInput * _freqLow, 0, 1023, 0, _logTaper);
    
  }
  // set LED based on value of DSP_Waveform
  PCI_SetMUX();

}

/////////////////////////////////////////////
/////////////////////////////////////////////
/////  ITERRUPT SERVICE ROUTINES
/////////////////////////////////////////////
/////////////////////////////////////////////



ISR(TIMER1_OVF_vect) {
   // reset SPI pins...?
    DDRB |= _BV(_SS);               // set SS pin to output before enabling SPI (req. for master)
    SPCR |=  _BV(SPE) | _BV(MSTR);  // enable spi as master
    //DDRB |= _BV(_SCK) | _BV(_MOSI); // set pins to output
 
   SPI_SendData();
}

// Interrupt service routine for the ADC completion
ISR(ADC_vect){
  
  
  ADCInput = ADCL;
  ADCInput += ADCH << 8;

  
   switch(ADMUX) {
    case 0x00:
      ADC_FreqInput = ADCInput;
      
     // ADMUX = 0x01;
    break;
    
    /*case 0x01:
      ADC_FreqInput = ADCInput;
      ADMUX = 0x00;
    break;
    */
    
    
  }
  ADCSRA |= _BV(ADSC);
 
}

ISR(PCINT2_vect) {  
   //Serial.println("Test");
    if(PIND & _BV(PCI_WaveIncrPin)) {
      
      (DSP_Waveform == PULSE) ? DSP_Waveform = SINE : DSP_Waveform++;      
      PCI_SetMUX();
      
     
    }
  
}

