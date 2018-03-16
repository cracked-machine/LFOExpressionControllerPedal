# LFOExpressionControllerPedal
This pedal replaces the traditional treadle/rocker expression pedal as an input into other guitar effects pedals.
Traditional expression pedals allow the player to control a variable resistance via an analog potentiometer in the expression pedal. This pedal creates an LFO signal that sweeps a digital potentiometer. 

The DSP is provided by an ATMEGA328P MCU, which transmits the binary encoded waveform data to a MCP41050 digital potentiometer via SPI. Eight waveforms are available: Sine, Square, RampUp, RampDown, Triangle, 8Step, 4Step and Pulse.
These waveforms can be selected via a single SPDT switch. LEDs indicate the selected waveform. A separate analog pot adjusts the frequency speed.

Documentation:

<ul>
  <li><a href="Hardware/SMT/documentation/LFOControllerPedal_SMT.xml">BOM</a></li>
  <li><a href="Hardware/SMT/documentation/LFOExpController_SMT.pdf">Schematic</a></li>
  <li><a href="Hardware/SMT/documentation/LFOExpController_SMT-TOPbrd.svg">Board Layout (TOP)</a></li>
  <li><a href="Hardware/SMT/documentation/LFOExpController_SMT-BOTTOMbrd.svg">Board Layout (BOTTOM)</a></li>
</ul>
