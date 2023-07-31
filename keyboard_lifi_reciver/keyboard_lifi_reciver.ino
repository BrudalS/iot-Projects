//Receiver Side:
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

 
#define SCREEN_WIDTH 128 // //////oled display width,  in pixels
#define SCREEN_HEIGHT 64 // //////oled display height, in pixels


// declare an SSD1306 display object connected to I2C
// Adafruit_SSD1306 //////oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup()
{
  pinMode(8, INPUT);
  Serial.begin(9600);

    // initialize //////oled display with address 0x3C for 128x64
 /* if (!//////oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
*/
  delay(2000);         // wait for initializing
  //////oled.clearDisplay(); // clear display
  //////oled.setTextSize(1);          // text size
  //////oled.setTextColor(WHITE);     // text color
  //////oled.setCursor(0, 10);        // position to display
  //////oled.display(); 

}
void loop()
{
  unsigned long duration = pulseIn(8, HIGH);
  Serial.println(duration);
  if (duration > 10000 && duration < 17000)
  {
    //////oled.println("Received: 1");
    Serial.println("Recived : 1");
  }
  else if (duration > 20000 && duration < 27000)
  {
    //////oled.println("Received: 2  ");
    Serial.println("Recived : 2");
  }
  else if (duration > 30000 && duration < 37000)
  {
    //////oled.println("Received: 3  ");
    Serial.println("Recived : 3");
  }
  else if (duration > 40000 && duration < 47000)
  {
    //////oled.println("Received: 4 ");
    Serial.println("Recived : 4");
  }
  else if (duration > 50000 && duration < 57000)
  {
    //////oled.println("Received: 5 ");
    Serial.println("Recived : 5");
  }
  else if (duration > 60000 && duration < 67000)
  {
    //////oled.println("Received: 6 ");
    Serial.println("Recived : 6");
  }
  else if (duration > 70000 && duration < 77000)
  {
    //////oled.println("Received: 7 ");
    Serial.println("Recived : 7");
  }
  else if (duration > 80000 && duration < 87000)
  {
    //////oled.println("Received: 8 ");
    Serial.println("Recived : 8");
  }
  else if (duration > 90000 && duration < 97000)
  {
    //////oled.println("Received: 9 ");
    Serial.println("Recived : 9");
  }
  else if (duration > 100000 && duration < 107000)
  {
    //////oled.println("Received: * ");
    Serial.println("Recived : *");
  }
  else if (duration > 110000 && duration < 117000)
  {
    //////oled.println("Received: 0 ");
    Serial.println("Recived : 0");
  }
  else if (duration > 120000 && duration < 127000)
  {
    //////oled.println("Received: # ");
    Serial.println("Recived : #");
  }
  else if (duration > 130000 && duration < 137000)
  {
    //////oled.println("Received: A  ");
    Serial.println("Recived : A");
  }
  else if (duration > 140000 && duration < 147000)
  {
    //////oled.println("Received: B          ");
    Serial.println("Recived : B");
  }
  else if (duration > 150000 && duration < 157000)
  {
    //////oled.println("Received: C ");
    Serial.println("Recived : C");
  }
  else if (duration > 160000 && duration < 167000)
  {
    //////oled.println("Received: D ");
    Serial.println("Recived : D");
  }
//////oled.display();
}
