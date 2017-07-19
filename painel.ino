float tempC = 0;
float tempF = 0;
float humidity = 0;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 3

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800);

#include <SHT1X.h>
//Create an instance of the SHT1X sensor
SHT1x sht15(0, 1);//Data, SCK

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void loop() {
  tempC = sht15.readTemperatureC();
  if(tempC <= 10){
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 255, 255), 50);// branco
  }
  else if(tempC <= 12){
  colorWipe(strip.Color(0, 0, 255), 50); //azul
}
  else if(tempC <=15){
  colorWipe(strip.Color(0, 191, 255), 50); // deep sky blue
  }
  else if(tempC <=18){
  colorWipe(strip.Color(124, 252, 0), 50); // lawn green
  }
  else if(tempC <=20){
  colorWipe(strip.Color(0, 255, 0), 50); // green
  }
  else if(tempC <=23){
  colorWipe(strip.Color(255, 255, 0), 50); // yellow
  }
  else if(tempC <=25){
  colorWipe(strip.Color(250, 128, 114), 50); // salmao
  }
  else if(tempC <=28){
  colorWipe(strip.Color(255, 0, 0), 50); // red
  }
  else if(tempC > 28){
  colorWipe(strip.Color(138, 43, 226), 50); // blue violet
  }
  //else{
  //colorWipe(strip.Color(0, 0, 0), 50);
  //}
    //rainbow(20);
  }

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
