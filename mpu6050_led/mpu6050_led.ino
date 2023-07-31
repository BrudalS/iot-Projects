#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int led_left2 = PB3;
int led_left1 = PB15;
int led_mid0 = PB14;
int led_right1 = PB13;
int led_right2 = PB12;

 
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);

 pinMode(led_left2, OUTPUT);
  pinMode(led_left1, OUTPUT);
  pinMode(led_mid0, OUTPUT);
  pinMode(led_right1, OUTPUT);
  pinMode(led_right2, OUTPUT);
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}
 display.display();
 delay(2);
 display.clearDisplay();
 
 display.clearDisplay();
 display.setTextColor(WHITE);
 display.setTextSize(2);
 display.setCursor(0,5);
 display.print("MPU Angles");
 display.display();
 delay(3000);
 
}
void loop()
{
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);
Serial.println("-----------------------------------------");
 
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0,0);
display.print("X: ");
display.println(x);
 
display.setTextSize(2);
display.setCursor(0,20);
display.print("Y: ");
display.println(y);
 
display.setTextSize(2);
display.setCursor(0,40);
display.print("Z: ");
display.println(z);
display.display();
 
delay(1000);

 if((x>270)&&(x<360))
       {
        // turn on level led 
        digitalWrite(led_left2,HIGH);
        delay(1000);
        digitalWrite(led_left2,LOW);
        delay(1000);
        digitalWrite(led_left1,LOW);
        
        digitalWrite(led_mid0,LOW);
        digitalWrite(led_right1,LOW);
        digitalWrite(led_right2,LOW);
       }
       else if((x>180)&&(x<270.00))
       {
        // turn on level led 
        digitalWrite(led_left2,LOW);
        digitalWrite(led_left1,HIGH);
        delay(1000);
        digitalWrite(led_left1,LOW);
        delay(1000);
        digitalWrite(led_mid0,LOW);
        digitalWrite(led_right1,LOW);
        digitalWrite(led_right2,LOW);
        }

       else if ((x>90.99)&&(x<180.00))
       {
        // turn on level led 
        digitalWrite(led_left2,LOW);
        digitalWrite(led_left1,LOW );
        digitalWrite(led_mid0,HIGH);
        delay(1000);
        digitalWrite(led_mid0,LOW);
        delay(1000);
        digitalWrite(led_right1,LOW);
        digitalWrite(led_right2,LOW);
       }  
       else if((x>45.01)&&(x<90.00))
       {
        // turn on level led 
        digitalWrite(led_left2,LOW );
        digitalWrite(led_left1,LOW );
        digitalWrite(led_mid0,LOW );
        digitalWrite(led_right1,HIGH );
        delay(1000);
        digitalWrite(led_right1,LOW );
        delay(1000);
        digitalWrite(led_right2,LOW );
       } 
       else if((x>0.00)&&(x<45))
       // turn on level led 
       {
        digitalWrite(led_left2,LOW );
       digitalWrite(led_left1,LOW );
       digitalWrite(led_mid0,LOW );
       digitalWrite(led_right1,LOW );
       digitalWrite(led_right2,HIGH );
       delay(1000);
       digitalWrite(led_right2,LOW );
       delay(1000);
       }
}
