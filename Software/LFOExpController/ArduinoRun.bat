SET WINAVR=H:\Programs\WinAVR-20100110
SET TMPHEXDIR=C:\Users\chris\AppData\Local\Temp\arduino_build_829921

%WINAVR%\bin\avrdude -P COM11 -b 19200 -c avrisp -p m328p -u -U flash:w:"%TMPHEXDIR%/LFOExpController.ino.hex":i