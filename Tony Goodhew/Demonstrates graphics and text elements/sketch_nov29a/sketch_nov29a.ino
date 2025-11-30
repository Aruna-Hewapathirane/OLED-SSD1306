/* Arduino UNO with SSD1306 128x64 I2C OLED display
 * Demonstrates graphics and text elements
 * Tony Goodhew  6th June 2020
 */
#include <SPI.h>           // Not needed with I2C
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void show() { // Often used sequence - Function to simplify code
  display.display(); delay(2000); display.fillScreen(SSD1306_BLACK);
}
void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Old Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
// Initialise variables
  int x0 = 5; // 3 pairs of co-ordinates
  int y0 = 5;
  int x1 = 120;
  int y1 = 23;
  int x2 = 55;
  int y2 = 60;
  int w = 105; // width
  int h = 55;  // height
  int r = 25;  // radius
  int cw = SSD1306_WHITE; // colour white
  int cb = SSD1306_BLACK; // colour black
  int wait = 2000; // 2 second delay
  
// Title screen
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(cw);
  display.setCursor(28,25);
  display.println("Screen");
  display.setCursor(28,33);
  display.println("Primitives");
  display.display(); delay(wait);
  randomSeed(analogRead(3));
  display.fillScreen(cw);              // Fill screen WHITE
  display.display(); delay(wait); 
  display.fillScreen(cb);              // Fill screen BLACK
  display.display();
  
// Pixels
  for (int i = 0; i <= 25; i++)  {     // 25 random pixels
    int xx = random(127);
    int yy = random(63);
    display.drawPixel(xx, yy, cw);
    display.display();
    delay(200);
  }
  delay(wait); display.fillScreen(cb);
  float sine[127]; 
  // Initialise variables
  display.fillScreen(cb);
  display.drawFastHLine(0, 32, 127 ,cw);
  for (int i = 0; i < 128; i++){
    sine[i] = (sin(radians(i *2.8125))) * -1; 
    display.drawPixel(i,int(sine[i]*25+32),cw);
    display.display();
  }

// Basic Draw & Fill
  show();
  display.drawLine(x0, y0, x1, y1 + 30, cw);
  show();
  display.drawFastVLine(35, 15, h, cw);  // Fast vertical line of length l
  show();
  display.drawFastHLine(5, 25, w ,cw);   // Fast horizontal line of length w 
  show();
  display.drawRect(x0, y0, w, h, cw);
  show();
  display.fillRect(x0, y0, w, h, cw);
  show();
  display.drawRoundRect(x0, y0, w, h, 8, cw);  // Rounded corners of radius 8  
  show();
  display.fillRoundRect(x0, y0, w, h, 8, cw);
  show();
  display.drawCircle(63, 31, r, cw);
  show();
  display.fillCircle(63, 31, r, cw);
  show();
  display.drawTriangle(x0, y0, x1, y1, x2, y2, cw);
  show();
  display.fillTriangle(x0, y0, x1, y1, x2, y2, cw);
  show();

// Screen rotation - 4 0ptions 0, 90 180 and 270 degrees 
  display.clearDisplay();
  display.setCursor(17,25);   // Title splash
  display.print("Rotate Screen");
  display.display(); delay(wait);
  for (int rot = 0; rot <= 4; rot++){
    display.setRotation(rot % 4);          // 0, 1, 2 or 3
    display.clearDisplay();
    display.fillTriangle(0,0,0,30,30,0,1);
    display.fillTriangle(0,15,40,50,15,0,1);
    display.fillTriangle(15,0,50,40,0,15,1);
    display.setTextSize(2);                // Middle size
    display.setTextColor(SSD1306_BLACK); 
    display.setCursor(5,5);             
    display.println(rot % 4);
    display.display(); delay(wait);  
  }
  display.setRotation(0);             // Normal rotation
  display.clearDisplay();
  // Finish
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(50,30);             
  display.println("Done");
  display.display();
}
void loop() {
  // put your main code here, to run repeatedly:
}