#include <MQ2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the LCD and MQ2 sensor
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address is 0x27, with 16x2 dimensions
int Analog_Input = A0; // Analog pin connected to the MQ2 sensor
float lpg, co, smoke;
MQ2 mq2(Analog_Input);

void setup() {
  Serial.begin(9600);
  lcd.begin(); // Initialize the LCD
  lcd.backlight(); // Turn on the LCD backlight

  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("SMOKE DETECTOR");
  delay(2000); // Display the message for 2 seconds

  mq2.begin(); // Initialize the MQ2 sensor
}

void loop() {
  // Read sensor values
  float* values = mq2.read(false); // Pass false to avoid printing in Serial Monitor
  lpg = mq2.readLPG();   // Read LPG concentration
  co = mq2.readCO();     // Read CO concentration
  smoke = mq2.readSmoke(); // Read smoke concentration

  lcd.clear(); // Clear the display for new readings

  // Display smoke detection status
  if (smoke > 10) { // Adjust the threshold value as needed
    lcd.setCursor(0, 0);
    lcd.print("SMOKE DETECTED!");
    lcd.setCursor(0, 1);
    lcd.print("SMOKE: ");
    lcd.print(smoke);
    lcd.print(" PPM");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("SMOKE NOT");
    lcd.setCursor(0, 1);
    lcd.print("DETECTED");
  }

  delay(2000); // Pause for 2 seconds

  // Display LPG detection status
  lcd.clear();
  if (lpg > 10) { // Adjust the threshold value as needed
    lcd.setCursor(0, 0);
    lcd.print("LPG DETECTED!");
    lcd.setCursor(0, 1);
    lcd.print("LPG: ");
    lcd.print(lpg);
    lcd.print(" PPM");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("LPG NOT");
    lcd.setCursor(0, 1);
    lcd.print("DETECTED");
  }

  delay(2000); // Pause for 2 seconds

  // Display CO detection status
  lcd.clear();
  if (co > 10) { // Adjust the threshold value as needed
    lcd.setCursor(0, 0);
    lcd.print("CO DETECTED!");
    lcd.setCursor(0, 1);
    lcd.print("CO: ");
    lcd.print(co);
    lcd.print(" PPM");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("CO NOT");
    lcd.setCursor(0, 1);
    lcd.print("DETECTED");
  }

  delay(2000); // Pause for 2 seconds
}
