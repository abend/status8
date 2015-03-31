#include <Adafruit_NeoPixel.h>

#define PIN 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  waves(1500, 60);
//
//  blackout();
//  blinks(5, 200, 30, false);
//
//  rainbow(1000);
//
//  waves(1500, 12);
//
//  rainbow(1000);
//
//  blackout();
//  blinks(5, 200, 30, true);
}

void waves(int length, int inc) {
  int count = strip.numPixels();
  int half_count = count / 2;
  /* int inc = 20; */

  // generate colors
  uint32_t colors[inc];
  float step = 256.0 / inc;
  uint8_t c;
  for (int i = 0; i < inc; i++) {
    c = ((int)(i * step)) & 255;
    colors[i] = strip.Color(c, c, c);
  }

  // for a while
  for (int run = length; run >= 0; run--) {
    for (int i = 0; i <= half_count; i++) {
      int offset = (i + run) % inc;

      strip.setPixelColor(i, colors[offset]);
      strip.setPixelColor(count - i, colors[offset]);
    }

    strip.show();
    delay(15);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Color(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

