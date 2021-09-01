// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>  //used to access non-volatile board storage
#include "Colors.h"

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6
//#define MW 64
//#define MH 8

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(64, 8, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_RGB            + NEO_KHZ800);

const uint16_t colors[] = {
  LED_RED_HIGH, LED_GREEN_HIGH, LED_BLUE_HIGH, LED_ORANGE_HIGH, LED_PURPLE_HIGH, LED_CYAN_HIGH, LED_WHITE_HIGH };

void setup() {
  //Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[0]);
}

int state = 1;

//wait for bluetooth signal from app
//while(state = 0){
//  if(Serial.available() > 0)
//    state = Serial.read();
//}

void loop() {

//switch case statement
switch(state){
  //text wrap
  case 1:
    //Serial.print("in case statement 1");
    //Serial.println();
    int x    = matrix.width();
    int pass = 0;
    
    while(state == 1){  //while no new signal detected
      //Serial.print("in while loop");
      //Serial.println();
      matrix.fillScreen(0); 
      matrix.setCursor(x, 0);
      matrix.print("GO COUGS");
      if(--x < -48) {
        //Serial.print("in if statement");
        //Serial.println();
        x = matrix.width();
        if(++pass >= 7) pass = 0;
        matrix.setTextColor(colors[pass]); 
      }
      matrix.show();
      delay(100);
//      if(Serial.available() > 0)  //check if signal changed
//        state = Serial.read();
    }
    break;
}
  
}
