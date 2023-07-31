#include <Keypad.h>

#include<LiquidCrystal.h>

#include<EEPROM.h>

LiquidCrystal lcd(9,8,7,6,5,4);

char password[4];

char initial_password[4],new_password[4];

int i=0;

int relay_pin = 10;

char key_pressed=0;

const byte rows = 4; 

const byte columns = 4; 

char hexaKeys[rows][columns] = {

{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}

};

byte row_pins[rows] = {A0,A1,A2,A3};

byte column_pins[columns] = {A4,A5,3,2};   

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);




void setup()

{

  Serial.begin(9600);

  pinMode(relay_pin, OUTPUT);

  lcd.begin(16,2);

  Serial.println("Electronic Lock");

  lcd.setCursor(0,1);

  lcd.print("Electronic Lock ");

  delay(2000);

  lcd.clear();

  lcd.print("Enter Password");

  Serial.println("Enterr Passward");

  lcd.setCursor(0,1);

  initialpassword();

}




void loop()

{

  digitalWrite(relay_pin, LOW);

  key_pressed = keypad_key.getKey();

  if(key_pressed=='#')

    change();

  if (key_pressed)

  {

    password[i++]=key_pressed;

    lcd.print(key_pressed);

    Serial.println(key_pressed);

      }

  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++)

      initial_password[j]=EEPROM.read(j);

    if(!(strncmp(password, initial_password,4)))

    {

      lcd.clear();

      lcd.print("Pass Accepted");

      Serial.println("Pass Accepted");

      digitalWrite(relay_pin, HIGH);

      delay(2000);

      lcd.setCursor(0,1);

      lcd.print("Pres # to change");

      Serial.println("Pres # to change");

      delay(2000);

      lcd.clear();

      Serial.println("Enter Password:");

      lcd.print("Enter Password:");

      lcd.setCursor(0,1);

      i=0;




    }

    else

    {

      digitalWrite(relay_pin, LOW );




      lcd.clear();

      lcd.print("Wrong Password");

      Serial.println("Wrong Password");

      lcd.setCursor(0,1);

      lcd.print("Pres # to Change");

      Serial.println("Pres # to Change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password");

      Serial.println("Enter Password");

      lcd.setCursor(0,1);

      i=0;




    }

  }

}

void change()

{

  int j=0;

  lcd.clear();

  lcd.print("Current Password");

  Serial.println("Current Password");
 
  lcd.setCursor(0,1);

  while(j<4)

  {

    char key=keypad_key.getKey();

    if(key)

    {

      new_password[j++]=key;

      lcd.print(key);

      Serial.println(key);

       

    }

    key=0;

  }

  delay(500);




  if((strncmp(new_password, initial_password, 4)))

  {

    lcd.clear();

    lcd.print("Wrong Password");

    Serial.println("Wrong Password");

    lcd.setCursor(0,1);

    lcd.print("Try Again");

    Serial.println("Try Again");

    delay(1000);

  }

  else

  {

    j=0;

    lcd.clear();

    lcd.print("New Password:");

    Serial.println("New Password:");

    lcd.setCursor(0,1);

    while(j<4)

    {

      char key=keypad_key.getKey();

      if(key)

      {

        initial_password[j]=key;

        lcd.print(key);

        Serial.println(key);

        EEPROM.write(j,key);

        j++;

     

      }

    }

    lcd.print("Pass Changed");

    Serial.println("Pass Changed");

    delay(1000);

  }

  lcd.clear();

  lcd.print("Enter Password");

  Serial.println("Enter Password");

  lcd.setCursor(0,1);

  key_pressed=0;

}




void initialpassword(){

  for(int j=0;j<4;j++)

    EEPROM.write(j, j+49);

  for(int j=0;j<4;j++)

    initial_password[j]=EEPROM.read(j);

} 
