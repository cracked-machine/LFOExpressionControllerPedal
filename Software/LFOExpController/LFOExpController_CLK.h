#ifndef DWG_CLK_H_
#define DWG_CLK_H_

///////////////////////////////////////////////////////
////    void setupTimer()
///////////////////////////////////////////////////////
void CLK_Setup() {
  unsigned char _sreg;   // save status register and disable interrupts
  _sreg = SREG;          //
  cli();                 //
  
    ////// Enable FastPWM (TIMER1 MODE 15)
    // OCR1A is used as TOP, overflow intterupt generated at TOP 
    // note, Mode 15 is double-buffered. So manual adjustments of OCR1A are made at BOTTOM i.e. *after* overflow interrupt
    TCCR1A = _BV(WGM10) | _BV(WGM11);                 //  WGM bits set the MODE
    TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS12);     // CS12 bit sets the prescaler as CLKIO/256
  
    //set OCR1A/TOP, just a default....this will be changed constantly by ADC_FreqInput in main loop
    OCR1A = 256;    // ~32KHz
   
    TIMSK1 = _BV(TOIE1);       // enable Timer1 overflow interrupt
    
  sei();                // restore status reg
  SREG = _sreg;         //
}


// quick debug
void CLK_ToggleBuiltInLed() {
  // don't forget to make pin13 output!
  if(digitalRead(13) == HIGH) {
    digitalWrite(13, LOW);
  }
  else {
    digitalWrite(13, HIGH);
  }
}


#endif
