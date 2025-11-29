/*
  Arduino Self-Test Demo + User Blink Input
  -----------------------------------------
  This version adds user input to control the number of LED blinks.
  Enter a number in the Serial Monitor when prompted.
*/

#include <EEPROM.h>
#include <avr/wdt.h>  // For watchdog test (optional)

int blinkCount = 0;   // Number of times to blink LED

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial); // Wait for serial connection (important for Leonardo etc.)

  Serial.println(F("\n=== Arduino Self-Test ==="));

  // 1️⃣ CPU Info
  Serial.print(F("MCU: "));
  #if defined(__AVR_ATmega328P__)
    Serial.println(F("ATmega328P"));
  #elif defined(__AVR_ATmega2560__)
    Serial.println(F("ATmega2560"));
  #elif defined(__AVR_ATmega32U4__)
    Serial.println(F("ATmega32U4"));
  #else
    Serial.println(F("Unknown MCU"));
  #endif

  Serial.print(F("Clock: "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));

  // 2️⃣ EEPROM test
  int addr = 0;
  byte counter = EEPROM.read(addr);
  EEPROM.write(addr, counter + 1);
  Serial.print(F("EEPROM boot count: "));
  Serial.println(counter);

  // 3️⃣ Voltage check
  long vcc = readVcc();
  Serial.print(F("Vcc: "));
  Serial.print(vcc / 1000.0, 3);
  Serial.println(F(" V"));

  // 4️⃣ Random noise seed
  randomSeed(analogRead(A0)); // Floating input = noise
  Serial.print(F("Random number: "));
  Serial.println(random(0, 1000));

  // 5️⃣ Ask user how many times to blink
  Serial.println(F("\nEnter number of times to blink LED: "));
}

void loop() {
  // Wait for user input
  if (Serial.available() > 0) {
    blinkCount = Serial.parseInt();  // Reads an integer
    if (blinkCount > 0) {
      Serial.print(F("\nBlinking LED "));
      Serial.print(blinkCount);
      Serial.println(F(" times..."));

      for (int i = 0; i < blinkCount; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
      }

      Serial.println(F("\nDone! Enter another number to blink again:"));
    } else {
      Serial.println(F("Please enter a positive number."));
    }
  }
}

// Reads Vcc using internal 1.1V reference
long readVcc() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  long result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result; // 1.1 * 1023 * 1000
  return result;
}
