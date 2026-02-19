#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int irSensorPin = 2;   // IR sensor connected to digital pin D2
const int buzzerPin = 7;     // Buzzer connected to digital pin D7
const int ledPin = 13;       // LED connected to digital pin D13

// Initialize the LCD with I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the pins
  pinMode(irSensorPin, INPUT);  // IR sensor as input
  pinMode(buzzerPin, OUTPUT);   // Buzzer as output
  pinMode(ledPin, OUTPUT);      // LED as output

  // Start with buzzer and LED off
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  // Initialize the LCD
  lcd.init();         // Use lcd.init() instead of lcd.begin()
  lcd.backlight();    // Turn on the backlight

  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Obstacle Detector");

  delay(3000); // Keep the message for 3 seconds
  lcd.clear();
}

void loop() {
  // Read the state of the IR sensor
  int irSensorState = digitalRead(irSensorPin);

  // Check if the IR sensor detects an object
  if (irSensorState == LOW) {  // Change to HIGH if the sensor logic is reversed
    // Object detected, turn on buzzer and LED
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);

    // Display "Object Detected" on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Object Detected  ");
  } else {
    // No object detected, turn off buzzer and LED
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);

    // Clear the LCD screen
    lcd.setCursor(0, 0);
    lcd.print("No Obstacle      ");
  }

  // Small delay for stability
  delay(100);
}
