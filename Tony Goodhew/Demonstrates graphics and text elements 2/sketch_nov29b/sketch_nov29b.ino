/* Arduino UNO with SSD1306 128x64 I2C OLED display
 * Demonstrates graphics and text elements
 * Tony Goodhew  26 May 2020  */
#include <SPI.h>           // Not needed with I2C
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void show() { // Often used sequence - Function to simplify code
  display.display(); delay(2000); display.fillScreen(SSD1306_BLACK);
}
void setup() {
  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Old Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Initialise variables
  int cw = SSD1306_WHITE;
  int cb = SSD1306_BLACK;

  // Title screen
  display.clearDisplay();
  display.setTextSize(2);                
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setCursor(20,10);
  display.setTextSize(2);                // Medium
  display.println("Playing");
  display.setCursor(20,25);
  display.println("with");
  display.setCursor(20,40);
  display.println("Text");
  show();
  display.setTextSize(1);
  
  // Text Sizes
  display.clearDisplay();
  display.setTextSize(1);                // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);   // Draw white text
  display.setCursor(0,0);                // Start at top-left corner
  display.println("Text Size Demo");
  display.setTextSize(2);                // Medium
  display.println("SSD1306");
  display.setTextSize(3);                // Large - rather blocky  
  display.println("SSD1306");
  display.setTextSize(1);
  display.println(" ");
  display.println("      Tony Go");
  show();
  
  // Text on a path
  char msg[] =  "Arduino+SSD1306=MAGIC";
  char msg2[] = "+ Follow the Cosine +";
  char msg3[] = "...Tangents go up.//|";
  char bigMsg[] = ".+Arduino+.";
  display.clearDisplay();
  for (int i = 0; i < 21; i++){    // Sine curve
    char ch = msg[i];
    int xx = i*6;
    float y1 = (sin(radians(xx *2.8125)) * -1);
    int yy = int(y1 *25.0 + 32);
    display.drawChar(xx, yy, ch, cw, cb, 1);
    display.display();
  }
  show();
  display.clearDisplay();
  for (int i = 0; i < 21; i++){    // Cosine curve
    char ch = msg2[i];
    int xx = i*6;
    float y1 = (cos(radians(xx *2.8125)) * -1);
    int yy = int(y1 *25.0 + 32);
    display.drawChar(xx, yy, ch, cw, cb, 1);
    display.display();
  }
  show();
  display.clearDisplay();
  for (int i = 0; i < 21; i++){   // Tangent curve
    char ch = msg3[i];
    int xx = i*6;
    float y1 = (tan(radians(xx *2.8125/4)) * -1);
    int yy = int(y1 *5.4 + 58);
    display.drawChar(xx, yy, ch, cw, cb, 1);
    display.display();
  }
  show();
  display.clearDisplay();
  int y2 = 50;
  for (int i = 0; i < 11; i++){  // Diagonal
    char ch = bigMsg[i];
    int xx = i*12;
    display.drawChar(xx, y2, ch, cw, cb, 2);
    y2 = y2 - 5;
    display.display();
  }
  // Overwrite method #1  - Same text but write in background colour
  for (int i = 0; i < 5; i++){
    display.setTextColor(cb); // Black text overwrite previous
    display.setCursor(100,56);
    display.println("Done");
    display.display();
    delay(500);
    display.setTextColor(cw);
    display.setCursor(100,56);
    display.println("Done"); // White text overwrite
    display.display();
    delay(500);
  }
  // Overwrite method #2  - Filled background rectangle over text
  int x = 50;
  int y = 40;
  display.clearDisplay();
  display.setTextSize(3);
  
  for (int i = 95; i < 9999; i++){
    display.setCursor(x, y);
    display.setTextColor(cw);
    display.println(i);
    display.display();
    delay(200);
    display.fillRect(x,y, 127, 63, cb); // Overwrite with black rectangle
    display.display();
    
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}