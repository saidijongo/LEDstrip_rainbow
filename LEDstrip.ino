const int NUM_LEDS = 143;
const int RED_PIN = 5;
const int GREEN_PIN = 7;
const int BLUE_PIN = 6;
const int DELAY_MS = 5;  // Delay between color changes

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

void rainbowEffect() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    int red = map(i, 0, NUM_LEDS - 1, 255, 0);
    int green = map(i, 0, NUM_LEDS - 1, 0, 255);
    int blue = 255 - green;
    
    setColor(red, green, blue);
    delay(DELAY_MS);
  }
  
  for (int i = 0; i < NUM_LEDS; ++i) {
    int red = map(i, 0, NUM_LEDS - 1, 0, 255);
    int green = map(i, 0, NUM_LEDS - 1, 255, 0);
    int blue = 255 - red;
    
    setColor(red, green, blue);
    delay(DELAY_MS);
  }
  
  for (int i = 0; i < NUM_LEDS; ++i) {
    int red = map(i, 0, NUM_LEDS - 1, 0, 255);
    int green = 255 - red;
    int blue = map(i, 0, NUM_LEDS - 1, 0, 255);
    
    setColor(red, green, blue);
    delay(DELAY_MS);
  }
}

void loop() {
  rainbowEffect();
}
