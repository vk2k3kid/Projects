//Multi-LED Blink and Sound Symphony with Arduino
// Pin definitions
const int redLED = 2;
const int greenLED = 3;
const int yellowLED = 4;
const int buzzer = 5;

// Frequencies for different sounds
const int sound1 = 261; // Frequency for "Do" (C)
const int sound2 = 294; // Frequency for "Re" (D)
const int sound3 = 329; // Frequency for "Mi" (E)
const int sound4 = 349; // Frequency for "Fa" (F)
const int sound5 = 392; // Frequency for "So" (G)
const int sound6 = 440; // Frequency for "La" (A) - New sound for Red + Yellow

// Time delay for each blink in milliseconds
const int blinkDelay = 500;

void setup() {
  // Initialize LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  // Initialize buzzer pin as output
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Blink Red LED
  digitalWrite(redLED, HIGH);
  tone(buzzer, sound1); // Play sound for Red LED
  delay(blinkDelay);
  digitalWrite(redLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);

  // Blink Green LED
  digitalWrite(greenLED, HIGH);
  tone(buzzer, sound2); // Play sound for Green LED
  delay(blinkDelay);
  digitalWrite(greenLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);

  // Blink Yellow LED
  digitalWrite(yellowLED, HIGH);
  tone(buzzer, sound3); // Play sound for Yellow LED
  delay(blinkDelay);
  digitalWrite(yellowLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);

  // Blink Red and Green LEDs simultaneously
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  tone(buzzer, sound4); // Play sound for Red + Green LEDs
  delay(blinkDelay);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);

  // Blink Green and Yellow LEDs simultaneously
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  tone(buzzer, sound5); // Play sound for Green + Yellow LEDs
  delay(blinkDelay);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);

  // Blink Red and Yellow LEDs simultaneously
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  tone(buzzer, sound6); // Play sound for Red + Yellow LEDs
  delay(blinkDelay);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  noTone(buzzer);
  delay(blinkDelay);
}
