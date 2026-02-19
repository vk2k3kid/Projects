#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pulsePin = A0;                 // Pulse Sensor purple wire connected to analog pin A0
int blinkPin = 13;                 // Pin to blink LED at each beat

// Volatile variables for interrupt routine
volatile int BPM = 0;              // Heart rate in beats per minute
volatile int Signal = 0;           // Holds the incoming raw data
volatile int IBI = 600;            // Time interval between beats
volatile boolean Pulse = false;    // "True" when a live heartbeat is detected
volatile boolean QS = false;       // Becomes true when Arduino finds a beat

volatile int rate[10];             // Array to hold the last ten IBI values
volatile unsigned long sampleCounter = 0;  // Used to determine pulse timing
volatile unsigned long lastBeatTime = 0;   // Used to find IBI
volatile int P = 512;              // Peak in pulse wave
volatile int T = 512;              // Trough in pulse wave
volatile int thresh = 550;         // Threshold for heartbeat detection
volatile int amp = 100;            // Amplitude of pulse waveform
volatile boolean firstBeat = true; // Seed rate array for reasonable BPM at startup
volatile boolean secondBeat = false;

void setup() {
  Serial.begin(115200); // Begin serial communication for Serial Plotter
  interruptSetup();
  
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Heart Rate Monitor");
  delay(3000);
  lcd.clear();
  
  pinMode(blinkPin, OUTPUT);
}

void loop() {
  if (QS == true) {
    displayHeartRate(); // Display heart rate on LCD
    QS = false;         // Reset Quantified Self flag
  }

  if (BPM == 0) {       // No valid signal detected
    lcd.setCursor(0, 0);
    lcd.print("No Signal       ");
    lcd.setCursor(0, 1);
    lcd.print("Place Finger    ");
  }

  // Send data to Serial Plotter
  Serial.print("Signal: ");
  Serial.print(Signal);
  Serial.print(", Threshold: ");
  Serial.print(thresh);
  Serial.print(", BPM: ");
  Serial.println(BPM);

  delay(20); // Small delay for smoother execution
}

void interruptSetup() {
  TCCR2A = 0x02;   // Disable PWM and enable CTC mode
  TCCR2B = 0x06;   // 256 prescaler
  OCR2A = 0X7C;    // Set the top count for 500Hz sample rate
  TIMSK2 = 0x02;   // Enable interrupt on match
  sei();           // Enable global interrupts
}

void displayHeartRate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heart-Beat Found");
  lcd.setCursor(0, 1);
  lcd.print("BPM: ");
  lcd.setCursor(5, 1);
  lcd.print(BPM);
}

ISR(TIMER2_COMPA_vect) {
  cli();
  Signal = (Signal * 0.9) + (analogRead(pulsePin) * 0.1); // Low-pass filter
  sampleCounter += 2;
  int N = sampleCounter - lastBeatTime;

  if (Signal < thresh && N > (IBI / 5) * 3) {
    T = min(T, Signal);
  }

  if (Signal > thresh && Signal > P) {
    P = max(P, Signal);
  }

  if (N > 250) {
    if ((Signal > thresh) && !Pulse && (N > 300)) {
      Pulse = true;
      digitalWrite(blinkPin, HIGH);
      IBI = sampleCounter - lastBeatTime;
      lastBeatTime = sampleCounter;

      if (secondBeat) {
        secondBeat = false;
        for (int i = 0; i < 10; i++) rate[i] = IBI;
      }

      if (firstBeat) {
        firstBeat = false;
        secondBeat = true;
        sei();
        return;
      }

      long runningTotal = 0;
      for (int i = 0; i < 9; i++) {
        rate[i] = rate[i + 1];
        runningTotal += rate[i];
      }

      rate[9] = IBI;
      runningTotal += rate[9];
      runningTotal /= 10;
      BPM = 60000 / runningTotal;
      QS = true;
    }
  }

  if (Signal < thresh && Pulse) {
    Pulse = false;
    digitalWrite(blinkPin, LOW);
    amp = P - T;
    thresh = amp / 2 + T;
    P = thresh;
    T = thresh;
  }

  if (N > 2500) {
    BPM = 0; // No heartbeat detected
    thresh = 512;
    P = 512;
    T = 512;
    lastBeatTime = sampleCounter;
    firstBeat = true;
    secondBeat = false;
  }

  sei();
}
