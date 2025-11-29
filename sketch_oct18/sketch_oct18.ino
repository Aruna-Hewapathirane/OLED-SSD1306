/*
  Arduino Self-Test + Serial Blink Command
  ----------------------------------------
  Adds a simple serial-controlled LED blink feature:
   - Send an integer (e.g., 5) from your Lazarus app or Serial Monitor
     → LED blinks that many times.
   - Keeps all your self-test features (EEPROM, Vcc, etc.)

  Works on Uno, Nano, Mega, Leonardo, etc.
*/

#include <EEPROM.h>
#include <avr/wdt.h>  // For watchdog test (optional)

// === Function prototypes ===
long readVcc();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial);  // Wait for serial connection (important for Leonardo, Micro)

  Serial.println(F("\n=== Arduino Self-Test + Serial Blink ==="));

  // 1️⃣ CPU Info
  Serial.print(F("MCU: "));
  #if defined(__AVR_ATmega328P__)
    Serial.println(F("ATmega328P"));
  #elif defined(__AVR_ATmega2560__)
    Serial.println(F("ATmega2560"));
  #else
    Serial.println(F("Unknown MCU"));
  #endif

  Serial.print(F("Clock: "));
  Serial.print(F_CPU / 1000000);
  Serial.println(F(" MHz"));

  // 2️⃣ EEPROM boot counter
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

  // 4️⃣ Random number seed
  randomSeed(analogRead(A0));
  Serial.print(F("Random number: "));
  Serial.println(random(0, 1000));

  // 5️⃣ Info about blink command
  Serial.println(F("Type a number (e.g. 3) to blink LED that many times."));
}

void loop() {
  // 👂 Check if serial data is available
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read until newline
    input.trim();  // Remove spaces or line endings

    // Only act if input is numeric
    if (input.length() > 0 && input.charAt(0) >= '0' && input.charAt(0) <= '9') {
      int blinkCount = input.toInt();  // Convert string to integer

      Serial.print(F("Blinking LED "));
      Serial.print(blinkCount);
      Serial.println(F(" times..."));

      for (int i = 0; i < blinkCount; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
      }

      Serial.println(F("Done."));
    } 
    else {
      Serial.print(F("Invalid input: "));
      Serial.println(input);
    }
  }
}

// === Function to measure Vcc ===
long readVcc() {
  // Use the internal 1.1V reference to measure supply voltage (Vcc)
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  long result = ADCL;
  result |= ADCH << 8;
  result = 1125300L / result; // 1.1 * 1023 * 1000
  return result;
}
