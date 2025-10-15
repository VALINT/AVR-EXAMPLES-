# MAX7219 LED MATRIX example

## How to build:

avr-gcc and avr-libc should be previously installed using `sudo apt install` command
    
    > mkdir build
    > cd build
    > cmake ../
    
    > cmake --build . #to build
    > avrdude -c usbasp -p atmega8 -U flash:w:slider_led.hex #to flash
    
or
    
    > cmake --build . -t upload #if need to flash automatically after build
    
