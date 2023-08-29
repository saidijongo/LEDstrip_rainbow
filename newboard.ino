const int CW_PIN = 5;
const int CCW_PIN = 6;
const int RIGHT_SENSOR_PIN = 11;
const int LEFT_SENSOR_PIN = 10;

const float ANGLE_TO_STEPS_RATIO = 0.72;
const int STEP_DELAY = 10; // Delay between each step in milliseconds

boolean rotating = false;
boolean stopRequested = false;

void setup() {
  pinMode(CW_PIN, OUTPUT);
  pinMode(CCW_PIN, OUTPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT_PULLUP);
  pinMode(LEFT_SENSOR_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void rotateClockwise(float angle) {
  digitalWrite(CW_PIN, HIGH);
  digitalWrite(CCW_PIN, LOW);
  
  int steps = angle / ANGLE_TO_STEPS_RATIO;
  for (int i = 0; i < steps; i++) {
    if (digitalRead(RIGHT_SENSOR_PIN) == LOW) {
      stopRotation('R', i * ANGLE_TO_STEPS_RATIO);
      return;
    }
    if (stopRequested) {
      stopRotation('S', i * ANGLE_TO_STEPS_RATIO);
      return;
    }
    delay(STEP_DELAY);
  }
  digitalWrite(CW_PIN, LOW);
  digitalWrite(CCW_PIN, LOW);
  rotating = false;
}

void rotateCounterClockwise(float angle) {
  digitalWrite(CW_PIN, LOW);
  digitalWrite(CCW_PIN, HIGH);
  
  int steps = angle / ANGLE_TO_STEPS_RATIO;
  for (int i = 0; i < steps; i++) {
    if (digitalRead(LEFT_SENSOR_PIN) == LOW) {
      stopRotation('L', i * ANGLE_TO_STEPS_RATIO);
      return;
    }
    if (stopRequested) {
      stopRotation('S', i * ANGLE_TO_STEPS_RATIO);
      return;
    }
    delay(STEP_DELAY);
  }
  digitalWrite(CW_PIN, LOW);
  digitalWrite(CCW_PIN, LOW);
  rotating = false;
}

void stopRotation(char reason, float angle) {
  rotating = false;
  digitalWrite(CW_PIN, LOW);
  digitalWrite(CCW_PIN, LOW);
  delay(3000); // Wait for 3 seconds
  if (reason == 'R') {
    rotateCounterClockwise(8);
  } else if (reason == 'L') {
    rotateClockwise(8);
  }
  Serial.print("Home Base (");
  Serial.print(reason);
  Serial.print("), Angle: ");
  Serial.println(angle);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (!rotating) {
      stopRequested = false;
      rotating = true;
      if (command == 'C') {
        rotateClockwise(90);
        Serial.println("CW 90 degrees");
      } else if (command == 'D') {
        rotateCounterClockwise(90);
        Serial.println("CCW 90 degrees");
      } else if (command == 'R') {
        while (digitalRead(RIGHT_SENSOR_PIN) == HIGH) {
          rotateClockwise(1);
        }
        rotateClockwise(188);
        Serial.println("Home Base");
      } else if (command == 'S') {
        stopRequested = true;
        Serial.println("Motor Stopped");
      } else if (command == 'I') {
        if (rotating) {
          Serial.println("Rotating");
        } else {
          if (digitalRead(RIGHT_SENSOR_PIN) == LOW || digitalRead(LEFT_SENSOR_PIN) == LOW) {
            Serial.println("Stopped: Home Base");
          } else {
            Serial.println("Stopped: Not Home Base");
          }
        }
      }
    }
  }
}
