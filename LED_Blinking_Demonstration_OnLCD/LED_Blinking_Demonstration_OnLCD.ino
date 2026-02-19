#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 (common) and 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pin definitions
const int redLEDPin = 8;
const int greenLEDPin = 9;
const int yellowLEDPin = 10;
const int blueLEDPin = 11;

void setup() {
  // Initialize LCD
  lcd.begin();
  lcd.backlight();

  // Initialize LED pins as OUTPUT
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  // Display the welcome message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to LED");
  lcd.setCursor(0, 1);
  lcd.print("Blinking");
  delay(2000); // Wait for 2 seconds before showing which LED is blinking
}

void loop() {
  // Blink RED LED
  blinkLED("LEDS - RED", redLEDPin);

  // Blink GREEN LED
  blinkLED("LEDS - GREEN", greenLEDPin);

  // Blink YELLOW LED
  blinkLED("LEDS - YELLOW", yellowLEDPin);

  // Blink BLUE LED
  blinkLED("LEDS - BLUE", blueLEDPin);
}

// Function to blink a specific LED and update LCD
void blinkLED(const char* message, int ledPin) {
  // Display which LED is blinking
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);

  // Blink the LED
  digitalWrite(ledPin, HIGH);
  delay(500); // LED ON for 0.5 seconds
  digitalWrite(ledPin, LOW);
  delay(500); // LED OFF for 0.5 seconds
}
