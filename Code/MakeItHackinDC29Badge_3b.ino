
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////  2021 MakeItHackin DEF CON 29 Badge - DEMO CODE 
//////////////////////////////////////////////////////////////////////////////////////////////////


/* 
  IF YOU HAVE ANY QUESTIONS OR COMMENTS, FEEL FREE TO INITIATE AN ISSUE ON GITHUB.  I PLAN TO ADD ADDITIONAL COMMENTS IN THE CODE, AND MAYBE SOME MORE FEATURES!
  
  ALL LIBRARIES FOR COMPONENTS WILL BE INCLUDED IN GITHUB LINK, SO FEEL FREE TO TINKER AROUND!
  https://github.com/MakeItHackin/DEFCON29Badge/

  Create output code for bitmaps:  https://javl.github.io/image2cpp/
  Background color: black
  Invert image colors: yes
  Canvas size: 128x32
  Code output format: Arduino
  Draw mode: Vertical - 1 bit per pixel
  
 */




/*

  LIBRARIES FOR NEOPIXELS WERE DERIVED FROM LIBRARIES BY ADAFRUIT

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
  
 */


////////////////////////////////////////////////////////////////
//////////  ATTINY 85 PINOUT
////////////////////////////////////////////////////////////////

 
/*
  
  GND - BATTERY NEGATIVE TERMINAL
  VCC - BATTERY POSITIVE TERMINAL
  PBO - I2C BUS - SDA
  PB1 - NEOPIXEL OUT
  PB2 - I2C BUS - SCL
  PB3 - LIGHT SENSOR INPUT
  PB4 - BUTTON INPUT
  PB5 - RESET BUTTON
  
 */


////////////////////////////////////////////////////////////////
//////////  VARIABLES AND LIBRARIES
////////////////////////////////////////////////////////////////

#include "TinyWireM.h" // USED FOR I2C CAPABILITIES
#include "TinyOzOLED.h" // USED FOR THE SSD1306 OLED SCREEN

#include <tinyNeoPixel_Static.h>  // USED FOR NEOPIXELS
#define PIN 1
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Parameter 4 = array to store pixel data in      
#define NUMPIXELS 14  // There are Four on the Badge... and allowing 10 more for SAOs
// Since this is for the static version of the library, we need to supply the pixel array
// This saves space by eliminating use of malloc() and free(), and makes the RAM used for
// the frame buffer show up when the sketch is compiled.
byte pixels[NUMPIXELS * 3];
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values. Finally, for the 4th argument we pass the array we
// defined above.
tinyNeoPixel strip = tinyNeoPixel(NUMPIXELS, PIN, NEO_GRB, pixels);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BUTTON_PIN   4    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

                          

#define LIGHT_SENSOR_PIN A3  // THIS IS PB3, BUT MUST LABEL IT A3 IN ORDER FOR THE ANALOG FUNCTIONS TO WORK
int lightSensorValue = 0;

// 'makeithackin', 128x32px
const unsigned char MakeItHackinBitmap [] PROGMEM = { //MakeItHackin
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 
  0x18, 0x18, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x3e, 0x36, 0x22, 0x00, 0x00, 0x00, 0x00, 0x1c, 
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
  0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x0f, 0x3e, 0x78, 0x70, 0x7c, 0x1e, 0x07, 0x7f, 0x7f, 0x00, 
  0x60, 0x78, 0x7c, 0x1f, 0x1f, 0x1b, 0x1f, 0x3e, 0x78, 0x60, 0x00, 0x7f, 0x7f, 0x0c, 0x1e, 0x3e, 
  0x73, 0x63, 0x41, 0x00, 0x00, 0x7f, 0x7f, 0x6d, 0x6d, 0x6d, 0x6d, 0x6d, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7f, 0x7f, 0x7f, 0x01, 0x03, 0x03, 0x7f, 0x7f, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xf0, 0xfd, 
  0x70, 0x20, 0x00, 0xff, 0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0xff, 0xff, 0xff, 0x00, 0xc0, 0xf0, 
  0x7c, 0x7f, 0x7f, 0x77, 0x7f, 0x7e, 0xf8, 0xe0, 0x80, 0x7e, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 
  0xc7, 0xe7, 0xe6, 0x00, 0xff, 0xff, 0x1c, 0x1c, 0x3c, 0x7e, 0xe7, 0xc3, 0x81, 0x01, 0x00, 0xff, 
  0xff, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x1e, 0x3c, 0x78, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1c, 0x3e, 0x23, 
  0x37, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'hackthisbadge', 128x32px
const unsigned char hackThisBadgeBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0xfc, 0xfc, 
  0x00, 0x00, 0x00, 0x80, 0xf0, 0xfc, 0x1c, 0x7c, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 
  0x38, 0x1c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x80, 0xe0, 0xf0, 0x7c, 0x1c, 
  0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0xfc, 0xfc, 0x0c, 0x0c, 0x0c, 0x0c, 
  0x00, 0xfc, 0xfc, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0xfc, 0xfc, 0x00, 0x0c, 0xfc, 0xfc, 
  0xfc, 0x0c, 0x00, 0x70, 0xf8, 0xfc, 0xcc, 0x8c, 0x8c, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3f, 0x3f, 0x3f, 
  0x00, 0x30, 0x3e, 0x3f, 0x07, 0x06, 0x06, 0x06, 0x07, 0x1f, 0x3f, 0x38, 0x00, 0x07, 0x0f, 0x1f, 
  0x1c, 0x38, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x01, 0x03, 0x0f, 0x1e, 0x3c, 
  0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3f, 0x3f, 0x3f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x3f, 0x3f, 0x3f, 0x00, 0x30, 0x3f, 0x3f, 
  0x3f, 0x30, 0x00, 0x18, 0x30, 0x31, 0x31, 0x33, 0x3f, 0x1f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x8c, 0x8c, 0xdc, 0xfc, 0x78, 
  0x10, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x7c, 0x1c, 0xfc, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xfc, 
  0xfc, 0x0c, 0x0c, 0x0c, 0x0c, 0x1c, 0xf8, 0xf8, 0xe0, 0x00, 0xc0, 0xf0, 0xf8, 0x38, 0x1c, 0x0c, 
  0x8c, 0x8c, 0x8c, 0x9c, 0x80, 0x00, 0x00, 0xfc, 0xfc, 0x8c, 0x8c, 0x8c, 0x8c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 
  0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x31, 0x31, 0x31, 0x3f, 0x1f, 
  0x0e, 0x00, 0x38, 0x3e, 0x3f, 0x07, 0x06, 0x06, 0x06, 0x07, 0x3f, 0x3e, 0x30, 0x00, 0x00, 0x3f, 
  0x3f, 0x30, 0x30, 0x30, 0x30, 0x18, 0x1f, 0x0f, 0x07, 0x00, 0x03, 0x0f, 0x1f, 0x18, 0x38, 0x30, 
  0x31, 0x31, 0x3f, 0x1f, 0x1f, 0x00, 0x00, 0x3f, 0x3f, 0x31, 0x31, 0x31, 0x31, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3b, 0x3b, 0x3b, 0x00, 0x00, 0x00, 0x3b, 0x3b, 0x00, 0x00, 0x00, 0x3b, 
  0x3b, 0x3b, 0x00, 0x00, 0x00, 0x3b, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'custom', 128x32px
const unsigned char dc29Bitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
  0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 
  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
  0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
  0x01, 0x03, 0x07, 0x0f, 0xff, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0xff, 0xff, 
  0x0f, 0x07, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x1f, 0x1f, 0x0f, 0x0e, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0x0f, 0x0f, 0x03, 
  0x01, 0x01, 0x01, 0x81, 0xc3, 0xff, 0xff, 0xff, 0x3e, 0x00, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xff, 
  0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
  0x80, 0xc0, 0xc0, 0xf0, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xff, 0xff, 
  0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0xfc, 0xf8, 0x38, 0x08, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 
  0xbc, 0x9e, 0x8f, 0x8f, 0x87, 0x83, 0x81, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xe3, 0xe3, 
  0xe7, 0x87, 0x87, 0x87, 0x83, 0xc3, 0xff, 0xff, 0xff, 0x7f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
  0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
  0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// 'custom', 128x32px
const unsigned char customBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
  0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 
  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
  0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
  0x01, 0x03, 0x07, 0x0f, 0xff, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0xff, 0xff, 
  0x0f, 0x07, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x07, 0x1f, 0x1f, 0x0f, 0x0e, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0f, 0x0f, 0x0f, 0x03, 
  0x01, 0x01, 0x01, 0x81, 0xc3, 0xff, 0xff, 0xff, 0x3e, 0x00, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xff, 
  0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
  0x80, 0xc0, 0xc0, 0xf0, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xff, 0xff, 
  0xf0, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0xfc, 0xf8, 0x38, 0x08, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 
  0xbc, 0x9e, 0x8f, 0x8f, 0x87, 0x83, 0x81, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xe3, 0xe3, 
  0xe7, 0x87, 0x87, 0x87, 0x83, 0xc3, 0xff, 0xff, 0xff, 0x7f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
  0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
  0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



// MENU VARIABLES
int NewMenuVar = 1;
int MenuCount = 4;
int OldMenuVar = MenuCount + 1; 

// BUTTON VARIABLES
bool newState;
bool oldState = HIGH;


int badgeType = 7; //CHAGE THIS VALUE TO CHANGE THE BADGE TYPE

//bool CustomBitmapBoolean = 0;

//String customLine1 = String("  FIRST LINE  ");
//String customLine2 = String("  SECOND LINE  ");


#define customLine1 "    FIRST LINE  "
#define customLine2 "   SECOND LINE  "

int nightLightThreshold = 100;

int demodelay = 2000;
int theaterChaseDelay = 100;
int neoPixelIntensity = 64; // (255 is max, 0 is min)

int secretBrightnessHigh = 700;
int secretBrightnessLow = 1;

 
int morseCodeDelay = 300;


////////////////////////////////////////////////////////////////
//////////  SETUP LOOP
////////////////////////////////////////////////////////////////

void setup() {

  //Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(PIN,OUTPUT); //set pin output - this is not done internally by the library for Static version of library



  //Start Neopixels
  //strip.begin(); //Static version does not use this.
  strip.show(); // Initialize all pixels to 'off'

  //Start Screen.  Some of these settings are to get the screen in the right orientation.
  OzOled.init();                 
  OzOled.clearDisplay(); 
  OzOled.setNormalDisplay();  
  OzOled.sendCommand(0xA1);
  OzOled.sendCommand(0xC8);
  OzOled.setHorizontalMode(); 
  OzOled.setBrightness(255);    

///////////////////////////////////////////////////////////////////////////
/// CYPHER STUFF
///////////////////////////////////////////////////////////////////////////
  //if (digitalRead(BUTTON_PIN)==LOW && analogRead(LIGHT_SENSOR_PIN) < secretBrightnessLow){
  //  secret1();
  //}
  if (digitalRead(BUTTON_PIN)==LOW && analogRead(LIGHT_SENSOR_PIN) > secretBrightnessHigh){
    secret2();
  }
  else if (digitalRead(BUTTON_PIN)==LOW){
    secret1();
  }
//  else  if (analogRead(LIGHT_SENSOR_PIN) < secretBrightnessLow){
//    secret3();
//  }
//  else  if (analogRead(LIGHT_SENSOR_PIN) > secretBrightnessHigh){
//    secret4();
//  }

  
  //Draw the SPACE APPS logo
   OzOled.drawBitmap(MakeItHackinBitmap, 0, 0, 16, 8);

  delay(500);

  OzOled.drawBitmap(dc29Bitmap, 0, 0, 16, 8);

  //if (CustomBitmapBoolean == 1){
    //delay(500);
    //OzOled.drawBitmap(CustomBitmap, 0, 0, 16, 8);
  //}

  delay(500);

  if (badgeType != 7){
    goToAwardMenu();
    delay(1000);
  }

  OzOled.clearDisplay();  
  
}


////////////////////////////////////////////////////////////////
//////////  MAIN LOOP
////////////////////////////////////////////////////////////////

void loop() {

  // Check the button for activity
  DoButton();

  // Change the menu if button has been pushed
  MenuChange();

  //Reinitialize menu variables
  OldMenuVar = NewMenuVar;

}


////////////////////////////////////////////////////////////////
//////////  OTHER FUNCTIONS
////////////////////////////////////////////////////////////////

void secret1(){
  //colorWipe(strip.Color(neoPixelIntensity, 0, 0), 0);
  /*
  strip.setPixelColor(0, strip.Color(neoPixelIntensity,0,0)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(1000);
  colorWipe(strip.Color(0, 0, 0), 0);
  */

/*

    OzOled.setCursorXY(0,0);   
    OzOled.printString("KEY");  
    OzOled.setCursorXY(0,2);  
    OzOled.printString("makeithackin");  
    delay(3000);
  */
  
  /*
  dot();dot();dot();
  delay(300);
  dash();dash();dash();
  delay(300);
  dot();dot();dot();

  */
  
  /*
  OzOled.drawBitmap(QRCodeBitmap, 0, 0, 16, 8); 
   */
    
    OzOled.clearDisplay(); 
    OzOled.setCursorXY(0,0);   
    OzOled.printString("   YOU HAVE  ");  
    OzOled.setCursorXY(0,1);   
    OzOled.printString(" UNLOCKED A KEY!");  
    OzOled.setCursorXY(0,2);  
    OzOled.printString("   IT IS... ");  
    delay(3000);

    OzOled.clearDisplay(); 
    OzOled.setCursorXY(0,0);   
    OzOled.printString("THE TITLE OF MY ");  
    OzOled.setCursorXY(0,1);   
    OzOled.printString("  MOST VIEWED");
    OzOled.setCursorXY(0,2);  
    OzOled.printString(" TIKTOK VIDEO ");  
    delay(3000);
  
}

void dot(){
  strip.setPixelColor(0, strip.Color(neoPixelIntensity,neoPixelIntensity,neoPixelIntensity)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(100);
  strip.setPixelColor(0, strip.Color(0,0,0)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(100);
}

void dash(){
  strip.setPixelColor(0, strip.Color(neoPixelIntensity,neoPixelIntensity,neoPixelIntensity)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(300);
  strip.setPixelColor(0, strip.Color(0,0,0)); // Moderately bright green color.
  strip.show(); // This sends the updated pixel color to the hardware.
  delay(300);  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void secret2(){

  OzOled.clearDisplay(); 
  OzOled.setCursorXY(0,0);   
  OzOled.printString("   YOU HAVE  ");  
  OzOled.setCursorXY(0,1);   
  OzOled.printString(" UNLOCKED A KEY!");  
  //OzOled.setCursorXY(0,2);  
  //OzOled.printString(" WATCH THE  ");  
  //delay(3000);
    
  dot();dash();
  delay(morseCodeDelay);
  dash();dot();dot();dot();
  delay(morseCodeDelay);
  dot();dash();
  delay(morseCodeDelay);
  dash();dot();dot();
  delay(morseCodeDelay);
  dot();dash();dash();dash();dash();
  delay(morseCodeDelay);
  dash();dot();dot();
  delay(morseCodeDelay);
  dot();
  delay(morseCodeDelay);
  dot();dash();
  delay(morseCodeDelay);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void secret3(){

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void secret4(){
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void secret5(){
  //colorWipe(strip.Color(neoPixelIntensity, 0, neoPixelIntensity), 0);
  //delay(1000);
  //colorWipe(strip.Color(0, 0, 0), 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void goToAwardMenu(){
 
  OzOled.clearDisplay();

  if (badgeType == 0){
    //DEVELOPER MODE
    OzOled.setCursorXY(0,1);   
    OzOled.printString("    DEVELOPER ");  
    OzOled.setCursorXY(0,3);  
    OzOled.printString("   SECRET MODE ");  
  }
  else if (badgeType == 1){
    //SHENETWORKS
    //OzOled.drawBitmap(shenetworksBitmap, 0, 0, 16, 8);              
  }
  else if (badgeType == 2){
    //BYT3BOY 
    //OzOled.drawBitmap(byt3boyBitmap, 0, 0, 16, 8);   
  }
  else if (badgeType == 3){
    //LLAMARUNNER
    //OzOled.drawBitmap(llamarunnerBitmap, 0, 0, 16, 8);   
  }
  else if (badgeType == 4){
    //CYBERPORTER
   // OzOled.drawBitmap(cyberporterBitmap, 0, 0, 16, 8);
  }
  else if (badgeType == 5){
    //CUSTOM TEXT SCREEN
    OzOled.setCursorXY(0,0);   
    OzOled.printString(customLine1);  
    OzOled.setCursorXY(0,2);  
    OzOled.printString(customLine2);  
  }
  else if (badgeType == 6){
    //MAKEITHACKIN IMAGE
    OzOled.drawBitmap(MakeItHackinBitmap, 0, 0, 16, 8);
  }
  else if (badgeType == 7){
    //DC29 IMAGE
    OzOled.drawBitmap(dc29Bitmap, 0, 0, 16, 8);
  }  
  else if (badgeType == 8){
    //CUSTOM IMAGE
    OzOled.drawBitmap(customBitmap, 0, 0, 16, 8);
  }
  else {
    //do nothing
    //PLACE HOLDER
  }
        
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DoButton(){

    // Get current button state.
  newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      NewMenuVar = OldMenuVar + 1;
      OzOled.clearDisplay();  
    }
    else {
      NewMenuVar = OldMenuVar;
    }
    if (NewMenuVar == MenuCount+1) {
       NewMenuVar = 1;
       }      
  }

  // Set the last button state to the old state.
  oldState = newState;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuChange() {
  
         if (NewMenuVar == MenuCount+1) {
              NewMenuVar = 1;
             }
         
         if (NewMenuVar == 0) {
            NewMenuVar = MenuCount;
          }
      
        if (NewMenuVar == 1)
          {
              OzOled.setCursorXY(0,0);   
              OzOled.printString("   MAIN MENU");  
              OzOled.setCursorXY(0,2);  
              OzOled.printString(" PRESS BUTTON TO ");  
              OzOled.setCursorXY(0,3);  
              OzOled.printString(" TEST COMPONENTS "); 
              //rainbow(20);
          } 
        else if (NewMenuVar == 2)
          {
            showLightSensor();
          }     
        else if (NewMenuVar == 3)
          {
            nightLight();
          }     
        else if (NewMenuVar == 4)
          {
            //showLightSensor();
            OzOled.setCursorXY(0,0);   
            OzOled.printString(" STARTING ");
            OzOled.setCursorXY(0,1); 
            OzOled.printString(" DEMO MODE... ");
            OzOled.setCursorXY(0,2);   
            OzOled.printString(" PRESS RESET ");
            OzOled.setCursorXY(0,3);   
            OzOled.printString(" TO EXIT ");
            colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
            delay(1000);
            StartDemoMode();
          }
           else 
              {
               // OnOffBool1 = 0;
              }  

  //delay(100);        
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StartDemoMode(){

  OzOled.clearDisplay();

  OzOled.drawBitmap(MakeItHackinBitmap, 0, 0, 16, 8);

  //theaterChase(strip.Color(0, 0, neoPixelIntensity), theaterChaseDelay); // blue
  colorWipe(strip.Color(neoPixelIntensity, 0, neoPixelIntensity), 350);
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  OzOled.drawBitmap(dc29Bitmap, 0, 0, 16, 8);

/*
  theaterChase(strip.Color(0, neoPixelIntensity, 0), theaterChaseDelay); // blue
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  OzOled.clearDisplay();
  OzOled.setCursorXY(0,1);   
  OzOled.printString("    PRESENT");
            
  theaterChase(strip.Color(neoPixelIntensity, neoPixelIntensity, neoPixelIntensity), theaterChaseDelay); // white
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  OzOled.drawBitmap(dc29Bitmap, 0, 0, 16, 8);
*/

  //theaterChase(strip.Color(0, 0, neoPixelIntensity), theaterChaseDelay); // Blue
  colorWipe(strip.Color(0, 0, neoPixelIntensity), 350);
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off



  OzOled.drawBitmap(hackThisBadgeBitmap, 0, 0, 16, 8);
  /*
  OzOled.clearDisplay();
  OzOled.setCursorXY(0,1);   
  OzOled.printString("   HACK THIS ");
  OzOled.setCursorXY(0,3);   
  OzOled.printString("   BADGE!!! ");
  */
  
  //theaterChase(strip.Color(neoPixelIntensity, neoPixelIntensity, neoPixelIntensity), theaterChaseDelay); // white
  //colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  colorWipe(strip.Color(0, neoPixelIntensity, 0), 350);
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  goToAwardMenu();

  rainbow(100);
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  DisplayLightSensorForDemo();

/*
  OzOled.clearDisplay();
  OzOled.setCursorXY(0,1);   
  OzOled.printString("   HACK THIS ");
  OzOled.setCursorXY(0,3);   
  OzOled.printString("   BADGE!!! ");
*/

  goToAwardMenu();

  rainbowCycle(20); //20
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off


  //theaterChaseRainbow(50); //50
  //colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  OzOled.clearDisplay();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayLightSensorForDemo(){
  OzOled.clearDisplay();
  for (int i=0; i < 100; i++){
    lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
    
    OzOled.setCursorXY(0,0);   
    OzOled.printString("LIGHT SENSOR");  
    OzOled.printString("VALUE",0,1.2);  
   //OzOled.setCursorXY(0,2);  
    OzOled.printNumber(long(lightSensorValue), 0, 3); 
    OzOled.printString("    ");
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showLightSensor(){
  lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
    
  OzOled.setCursorXY(0,0);   
  OzOled.printString("LIGHT SENSOR");  
  OzOled.printString("VALUE",0,1.2);  
 //OzOled.setCursorXY(0,2);  
  OzOled.printNumber(long(lightSensorValue), 0, 3); 
  OzOled.printString("    "); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nightLight(){
  lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
    
  OzOled.setCursorXY(0,0);   
  OzOled.printString("NIGHT LIGHT");  
  OzOled.printString("THRESHOLD:",0,1.2);  
  OzOled.printNumber(long(nightLightThreshold));
 //OzOled.setCursorXY(0,2);  
  OzOled.printNumber(long(lightSensorValue), 0, 3); 
  OzOled.printString("    "); 

  if (lightSensorValue < nightLightThreshold){
    colorWipe(strip.Color(neoPixelIntensity, neoPixelIntensity, neoPixelIntensity), 0);
  }
  else{
    colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
  }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void showBitmap(){
  OzOled.drawBitmap(dc29Bitmap, 0, 0, 16, 8);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Theatre-style crawling lights with rainbow effect
void showMode(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      delay(wait);
      
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
