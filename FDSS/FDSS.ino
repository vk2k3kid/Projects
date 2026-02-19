#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the I2C address for the LCD (0x27 is common)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the pins for the ultrasonic sensor, LEDs, and buzzer
const int trigPin = 9;
const int echoPin = 10;
const int greenLED = 3;
const int yellowLED = 4;
const int redLED = 5;
const int buzzer = 6;  // Buzzer pin

// Variables to store the duration and distance
long duration;
int distance;

// Define the threshold distances for the flood zones
const int safeZone = 25;    // Above 25 cm is safe
const int mediumZone = 15;  // Between 15 cm and 25 cm is medium
const int dangerZone = 15;  // Below 15 cm is danger

void setup() {
  // Initialize the serial monitor for debugging
  Serial.begin(9600);

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the LED and buzzer pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize the LCD
  lcd.begin();
  lcd.backlight();
  
  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Flood");
  lcd.setCursor(0, 1);
  lcd.print("Detection System");
  
  // Pause for 3 seconds to show the welcome message
  delay(3000);

  // Clear the welcome message
  lcd.clear();
}

void loop() {
  // Send a 10us pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in cm)
  distance = duration * 0.034 / 2;

  // Display the distance on the serial monitor for debugging
  Serial.print("Measured Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the water level and status on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(distance);
  lcd.print(" cm  ");

  // Determine the flood zone based on the distance
  if (distance > safeZone) {
    // Safe Zone (Green LED)
    lcd.setCursor(0, 1);
    lcd.print("Zone: SAFE     ");
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);  // Turn off buzzer
  } 
  else if (distance > mediumZone && distance <= safeZone) {
    // Medium Zone (Yellow LED)
    lcd.setCursor(0, 1);
    lcd.print("Zone: MEDIUM   ");
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);  // Turn off buzzer
  } 
  else if (distance <= mediumZone) {
    // Danger Zone (Red LED and Buzzer)
    lcd.setCursor(0, 1);
    lcd.print("Zone: DANGER   ");
    
    // Blink red LED and buzzer
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
  }

  // Small delay before the next reading
  delay(500);
}
