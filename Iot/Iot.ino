#include <Servo.h>

// Pin Definitions
int ledPin = 3;         // LED pin
int fanPin1 = 5;        // DC motor IN1
int fanPin2 = 6;        // DC motor IN2
int fanEnable = 10;     // DC motor Enable pin (PWM)
int rainSensorPin = A0; // Rain drop sensor analog pin
int threshold = 300;    // Rain sensor threshold value
Servo servoMotor;       // Servo motor object

// State Variables
bool isRaining = false; // Track rain state

void setup() {
  // Setup Pins
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  pinMode(fanEnable, OUTPUT);
  pinMode(rainSensorPin, INPUT);

  // Initialize Servo
  servoMotor.attach(9); // Servo connected to pin D9
  servoMotor.write(0);  // Start servo at 0 degrees

  // Initialize Serial Communication
  Serial.begin(9600);
  Serial.println("System Ready");
  Serial.println("Commands:");
  Serial.println("L1 - Turn LED ON");
  Serial.println("L0 - Turn LED OFF");
  Serial.println("F1 - Turn Fan ON");
  Serial.println("F0 - Turn Fan OFF");
}

void loop() {
  // Serial Control for LED and Fan
  if (Serial.available()) {
    String command = Serial.readString(); // Read the incoming command

    // Handle LED commands
    if (command == "L1") {
      digitalWrite(ledPin, HIGH); // Turn ON LED
      Serial.println("LED ON");
    } else if (command == "L0") {
      digitalWrite(ledPin, LOW);  // Turn OFF LED
      Serial.println("LED OFF");
    }

    // Handle Fan (DC Motor) commands
    else if (command == "F1") {
      digitalWrite(fanPin1, HIGH); // Rotate fan forward
      digitalWrite(fanPin2, LOW);
      analogWrite(fanEnable, 255); // Full speed
      Serial.println("Fan ON");
    } else if (command == "F0") {
      digitalWrite(fanPin1, LOW);  // Turn OFF fan
      digitalWrite(fanPin2, LOW);
      analogWrite(fanEnable, 0);
      Serial.println("Fan OFF");
    }
  }

  // Rain Sensor Control for Servo Motor
  int rainValue = analogRead(rainSensorPin); // Read rain sensor value
  if (rainValue < threshold && !isRaining) { // Detect rain
    servoMotor.write(90);                   // Move servo to 90 degrees
    isRaining = true;                       // Update state
    Serial.println("Rain detected - Clothes moved inside");
  } else if (rainValue >= threshold && isRaining) { // No rain
    servoMotor.write(0);                    // Move servo back to 0 degrees
    isRaining = false;                      // Update state
    Serial.println("No rain - Clothes moved outside");
  }

  delay(200); // Small delay for stability
}
