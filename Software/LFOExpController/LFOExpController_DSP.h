#ifndef DWG_DSP_H_
#define DWG_DSP_H_

//#define LOOKUP_TABLE_ENABLED

// all possible waveforms
enum DSP_EWAVEFORMS { SINE, SQUARE, RAMPUP, RAMPDOWN, TRIANGLE, STEP8, STEP4, PULSE } ;

// available waveforms. if you change this order make sure the last item matches one used  in PCINT2_vect condition!
DSP_EWAVEFORMS const DSP_Waveforms[] = { SINE, SQUARE, RAMPUP, RAMPDOWN, TRIANGLE, STEP8, STEP4, PULSE};

// current selected waveform
int DSP_Waveform;

// sine wave lookup table and sample rate. limit dictated by MCP41050
const int DSP_SampleResolution = 256;  

// counter variable used by all waveforms
int DSP_WaveIndex;

void DSP_Setup() {

  DSP_Waveform = SINE;
}

int DSP_GetAlgorithmicWaveData(DSP_EWAVEFORMS _Waveform) {
      int _multiplier;
      int _halfPeriod=DSP_SampleResolution/2;   // half period
      int _temp;                                 // temp allows serial print debug
      float _tri_temp=0;                        // triangle needs a float
   
      switch(_Waveform) {
          
          case SINE:     
              _temp = (cos(((2.0*PI)/DSP_SampleResolution)*DSP_WaveIndex))*(_halfPeriod-1);
              return _temp += (_halfPeriod-1);
            break;
          
          case SQUARE:
            return (DSP_WaveIndex++ % 256) < 128 ? (0xFF) : 0x00;
            break;

          case RAMPUP:
            _multiplier = 4;
            _temp = DSP_SampleResolution - (_multiplier * (DSP_WaveIndex/4));
            return _temp;
            break;
          
          case RAMPDOWN:
            _multiplier = 4;
            _temp = _multiplier * (DSP_WaveIndex/4);
            return _temp;
            break;
          
          case TRIANGLE:  
            _multiplier = 2;
            _tri_temp = (_halfPeriod - abs(DSP_WaveIndex % (2 * _halfPeriod) - _halfPeriod) );
            _tri_temp = (DSP_SampleResolution-1) - ((_multiplier) * _tri_temp);
            return _tri_temp;
            break;
          
          case STEP8:
            _multiplier = 32;
            _temp = DSP_SampleResolution - (_multiplier * (DSP_WaveIndex/_multiplier));
            return _temp;
            break;
          
          case STEP4:
            _multiplier = 64;
            _temp = DSP_SampleResolution - (_multiplier * (DSP_WaveIndex/_multiplier));
            return _temp;
            break;
            
          case PULSE:
            return (DSP_WaveIndex++ % 256) > 224 ? (0xFF) : 0x00;
            break;
      }
      
 
}





#endif 
