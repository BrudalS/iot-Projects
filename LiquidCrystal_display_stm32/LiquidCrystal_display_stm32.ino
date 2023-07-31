#include<LiquidCrystal.h>
LiquidCrystal lcd(PB0,PB1,PB3,PB4,PB5,PB6); //RS-PB0,enable-PB1,D4-D7=PB3-PB6
void setup() { 
 lcd.begin(16,2);
  

}

void loop(){
  lcd.setCursor(0,1);
  lcd.print("yo");

}
