#include <Servo.h>

// Pin Assignments
const int stepPin = 5;
const int dirPin = 6;
const int enPin = 8;
const int ms1Pin = 2;
const int ms2Pin = 3;
const int ms3Pin = 4;
const int servoPin = 7; 

Servo myServo;
bool servoPos = false; 

// --- CONFIGURATION ---
int stepDelay = 800;      
int stepsPerPress = 200;  
// ----------------------

void setup() {
  Serial.begin(9600);

  myServo.attach(servoPin);
  // Setting 90 as the "Home" position is usually best for 180-degree movement
  myServo.write(90); 

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
  
  digitalWrite(enPin, LOW); 
  digitalWrite(ms1Pin, LOW); 
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
}

void moveSteps(int steps, int direction) {
  digitalWrite(dirPin, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'F') {
      moveSteps(stepsPerPress, LOW);
      Serial.println("Done Forward");
    } 
    else if (command == 'B') {
      moveSteps(stepsPerPress, HIGH);
      Serial.println("Done Backward");
    }
    else if (command == 'X') {
      if (!servoPos) {
        // Move to 180 degrees (far "right")
        myServo.write(180);
        servoPos = true;
        Serial.println("Servo to 180");
      } else {
        // Return to 90 degrees (center)
        myServo.write(90);
        servoPos = false;
        Serial.println("Servo to 90");
      }
    }
  }
}