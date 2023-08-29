const int RED_PIN = 5;
const int GREEN_PIN = 6;
const int BLUE_PIN = 7;

const int NUM_LEDS = 143;
const int BLINK_DELAY = 5;  // Delay between color changes in milliseconds

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
  for (int i = 0; i < NUM_LEDS; i++) {
    int hue = map(i, 0, NUM_LEDS, 0, 255);
    int rgb[3];
    calculateRGB(hue, rgb);
    setColor(rgb[0], rgb[1], rgb[2]);
    delay(BLINK_DELAY);
  }
}

void calculateRGB(int hue, int rgb[]) {
  int segment = hue / 43;  // Divide the color wheel into 6 segments
  int offset = hue % 43;    // Calculate the position within the segment
  
  int rampUp = offset * 6;
  int rampDown = 255 - rampUp;
  
  switch (segment) {
    case 0:  // Red to Yellow
      rgb[0] = 255;
      rgb[1] = rampUp;
      rgb[2] = 0;
      break;
    case 1:  // Yellow to Green
      rgb[0] = rampDown;
      rgb[1] = 255;
      rgb[2] = 0;
      break;
    case 2:  // Green to Cyan
      rgb[0] = 0;
      rgb[1] = 255;
      rgb[2] = rampUp;
      break;
    case 3:  // Cyan to Blue
      rgb[0] = 0;
      rgb[1] = rampDown;
      rgb[2] = 255;
      break;
    case 4:  // Blue to Magenta
      rgb[0] = rampUp;
      rgb[1] = 0;
      rgb[2] = 255;
      break;
    default: // Magenta to Red
      rgb[0] = 255;
      rgb[1] = 0;
      rgb[2] = rampDown;
      break;
  }
}
