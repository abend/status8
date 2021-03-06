#include <Adafruit_NeoPixel.h>

// use "Arduino Uno" board when uploading to femtoduino

#define PIN 5
#define LED_COUNT 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


// how many LEDs?
uint32_t colors[LED_COUNT];
uint32_t black = strip.Color(0,0,0);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // generate colors
  float step = 256.0 / LED_COUNT;
  for (int i = 0; i < LED_COUNT; i++) {
    uint8_t c = ((int)(i * step)) & 255;
    colors[i] = Color(c);
  }

  Serial.begin(9600);
  Serial.println("Connected");
}

void loop() 
{
	int x;
	String str;

    if (Serial.available() > 0)
    {
        x = Serial.parseInt();
        str = Serial.readStringUntil('\n');
		str.trim();
		Serial.println(str + ": " + String(x));
		if (checkLED(x)) {
			changeToColor(x, str == "on" ? colors[x] : black);
		}
    }
}

// valid number for the LED?
boolean checkLED(int i) {
	return i > 0 && i <= LED_COUNT;
}

void changeToColor(int led, uint32_t newColor) {
	uint32_t curColor = strip.getPixelColor(led - 1);

	int steps = 256;

	uint8_t
		cr = (uint8_t)(curColor >> 16),
		cg = (uint8_t)(curColor >>  8),
		cb = (uint8_t) curColor;

	uint8_t
		nr = (uint8_t)(newColor >> 16),
		ng = (uint8_t)(newColor >>  8),
		nb = (uint8_t) newColor;

	float
		dr = nr - cr,
		dg = ng - cg,
		db = nb - cb;

	float
		sr = dr / steps,
		sg = dg / steps,
		sb = db / steps;

	uint8_t ir, ig, ib;

	for (int i = 0; i < steps; ++i) {
		ir = cr + (int)(sr * i);
		ig = cg + (int)(sg * i);
		ib = cb + (int)(sb * i);
		strip.setPixelColor(led - 1, strip.Color(ir, ig, ib));
		strip.show();
		delay(7);
	}
	strip.setPixelColor(led - 1, newColor);
	strip.show();
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

