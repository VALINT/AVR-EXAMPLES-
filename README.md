# AVR-EXAMPLES-
Examples of code that appeared in the study of this architecture.

# EXAMPLES

1. Simple example work with I/O ports in output mode
  - Blink LED (Hello World project).
  - Slider with LEDs.

2. Simple example work with I/O ports in input mode 
  - Simple_Buttons (Reaction on the pushed button).
  - Buttons - Simple structure and function that handle short and long clicks.
    An example of using is in a Saturn2 project. 

3. Example work with PWM and RGB LED
  - RGB LED controlled by PWM signal.
  
4. Example work with ADC
  - MCU read analog signal and show his altitude on 7-seg display
  - MCU read analog signal and show his altitude on the 8-LEDs bar (VU-meter)
  - VU_metr was built on a special soviet vacuum indicator(ILT6-30V) (the project was frozen)
  - External ADC build on R2R matrix and comparator for ATTiny2313 (Voltmeter on ATTiny2313)
  - Demo project (we have 3 light sensors that control different color channels. Шf we obscure any of the channels, the color of the LED's glow is shifted towards the color to which the sensor is attached.
  
5. Example work with SPI
  - Simple example master SPI (MCU send color who can set by buttons)
  - Simple example slave SPI (MCU receive color and display his on RGB LED)
  
6. Example work with Timers
  - Simple Demo project on Timer/Counter 0 overflow interrupt MCU incrementing 8-bit counter and show sum on 8-LEDs bar
  - Simple Demo project. Clock on AtMega8a. Clock crystal connected to XTAL PINs, Timer2 works in asynchronous mode and counts time. Timer1     control dynamic indication on 7-seg LEDs display.
  
7. Example work with LCD
  - Example work with HD44780 LCD
  - Example work with Siemens A51 LCD
  - Demo project. The watch on HD44780. Clock crystal connected to XTAL PINs, Timer2 works in asynchronous mode and counts time. Time shows on     LCD. In LCD draws big symbols.

8. Examples work with UART/USART interface
  - Demo project. Realized serial connection with PC like an Arduino's Serial. Print. I think that it very good for debugging on MCU without JTAG or one wire
  
9. Examples work with SD card
  - Example work with SD card, used FAT32 file system. Plays *.WAV files from SD

10. Example work with hardware interfaces

11. Example work with RTC
  - In current time only for DS3231

12. Example work with DHT11/DHT22

13. Simple example of work with MAX7219.
  - Only with an 8x8 led matrix. Can handle 1 - 4 matrixes.
