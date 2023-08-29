const int RED_PIN = 5;
const int GREEN_PIN = 6;
const int BLUE_PIN = 7;

const int NUM_LEDS = 143;
const int DELAY_MS = 10; 

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void loop() {
  // Continuously shift the rainbow colors
  for (int offset = 0; offset < NUM_LEDS; offset++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      int hue = map((i + offset) % NUM_LEDS, 0, NUM_LEDS, 0, 255);
      int saturation = 255; // Full saturation
      int value = 255; // Full brightness
      
      int red, green, blue;
      hsvToRgb(hue, saturation, value, red, green, blue);
      
      setColor(red, green, blue);
      delay(DELAY_MS);
    }
  }
}

void hsvToRgb(int hue, int saturation, int value, int &red, int &green, int &blue) {
  int c = (value * saturation) >> 8;
  int x = c * (255 - abs((hue / 60) % 2 - 1)) >> 8;
  int m = value - c;

  if (hue < 60) {
    red = c; green = x; blue = 0;
  } else if (hue < 120) {
    red = x; green = c; blue = 0;
  } else if (hue < 180) {
    red = 0; green = c; blue = x;
  } else if (hue < 240) {
    red = 0; green = x; blue = c;
  } else if (hue < 300) {
    red = x; green = 0; blue = c;
  } else {
    red = c; green = 0; blue = x;
  }

  red = (red + m) & 0xFF;
  green = (green + m) & 0xFF;
  blue = (blue + m) & 0xFF;
}
