#ifndef DWG_PCI_H_
#define DWG_PCI_H_

// see CD74HCT4051 MUX datasheet function table
// we are using PIND2, PIND3 and PIND4 on the ATMEGA328P to send addresses to MUX
#define MUXCLEAR 0x00    // 000 // 
#define MUXS0 0x02    // 001
#define MUXS1 0x03    // 010  
#define MUXS2 0x04    // 100



// 0x02 2+3
// 0x03 1+3
// 0x04 1+2
// 0x0

/////  ATMEGA328P reference PORTD pin-2-interrupt
// PIND0 = PCINT16
// PIND1 = PCINT17
// PIND2 = PCINT18
// PIND3 = PCINT19
// PIND4 = PCINT20
// PIND5 = PCINT21
// PIND6 = PCINT22
// PIND7 = PCINT23

// PCI_WaveIncrPin. must change BOTH. See above for reference.
int PCI_WaveIncrPin = PIND5; 
int PCI_WaveIncInt = PCINT21;

int PCI_MUXPIN0 = PIND2;
int PCI_MUXPIN1 = PIND3;
int PCI_MUXPIN2 = PIND4;

void PCI_Setup() {
  
  //set PCI_WaveIncrPin = INPUT (0), PCI_MUXS0 = OUTPUT (1)
  DDRD |= ~_BV(PCI_WaveIncrPin) | _BV(PCI_MUXPIN0) | _BV(PCI_MUXPIN1) | _BV(PCI_MUXPIN2);
  
  
  //set PCI_WaveIncrPin = Hi-Z (1)
  PORTD |= _BV(PCI_WaveIncrPin) | _BV(PCI_MUXPIN0) | _BV(PCI_MUXPIN1) | _BV(PCI_MUXPIN2) ;

  //pinMode(PCI_WaveIncrPin, INPUT);
  //pinMode(PCI_MUXPIN0, OUTPUT);
  //pinMode(PCI_MUXPIN1, OUTPUT);
  //pinMode(PCI_MUXPIN2, OUTPUT);
  
  
  PCICR |= _BV(PCIE2);      // enable interrupts for PD 0-7 ports (PCINT16-23)
  PCMSK2 |= _BV(PCI_WaveIncInt) ;   // enable interrupts for PCI_WaveIncrPin
   
}

void PCI_SetMUX() {
  switch(DSP_Waveform) {
        case SINE:
            // A0 = LLL
            digitalWrite(PCI_MUXPIN2, LOW);
            digitalWrite(PCI_MUXPIN1, LOW);
            digitalWrite(PCI_MUXPIN0, LOW);
          
          break;
        case SQUARE:
            // A1 = LLH
            digitalWrite(PCI_MUXPIN2, LOW);
            digitalWrite(PCI_MUXPIN1, LOW);
            digitalWrite(PCI_MUXPIN0, HIGH);
          break;
        case RAMPUP:
            // A2 = LHL
            digitalWrite(PCI_MUXPIN2, LOW);
            digitalWrite(PCI_MUXPIN1, HIGH);
            digitalWrite(PCI_MUXPIN0, LOW);
          break;
        case RAMPDOWN:
            //A3 = LHH
            digitalWrite(PCI_MUXPIN2, LOW);
            digitalWrite(PCI_MUXPIN1, HIGH);
            digitalWrite(PCI_MUXPIN0, HIGH);
          break;
        case TRIANGLE:
            //A4 = HLL
            digitalWrite(PCI_MUXPIN2, HIGH);
            digitalWrite(PCI_MUXPIN1, LOW);
            digitalWrite(PCI_MUXPIN0, LOW);
          break;
        case STEP8:
            //A5 = HLH
            digitalWrite(PCI_MUXPIN2, HIGH);
            digitalWrite(PCI_MUXPIN1, LOW);
            digitalWrite(PCI_MUXPIN0, HIGH);
          break;
        case STEP4:
            //A6 = HHL
            digitalWrite(PCI_MUXPIN2, HIGH);
            digitalWrite(PCI_MUXPIN1, HIGH);
            digitalWrite(PCI_MUXPIN0, LOW);
          break;
        case PULSE:
            //A7 = HHH
            digitalWrite(PCI_MUXPIN2, HIGH);
            digitalWrite(PCI_MUXPIN1, HIGH);
            digitalWrite(PCI_MUXPIN0, HIGH);
          break;
      }

  
}

#endif
