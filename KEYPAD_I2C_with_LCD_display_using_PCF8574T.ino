#include <Wire.h>
#include <LiquidCrystal_I2C.h>
String  pressedCharacter;
float buttonTimer = 0;
bool buttonPressed=false;
int d;
LiquidCrystal_I2C lcd(0x27, 16, 2);
/* !NOTICE!
 * There is no wiring schematics provided since I only used the i2C pins in this demonstration
 * SDA: A4, SCL: A5
 * Both the LCD and the PCF8574 module are compatible with 5 V
 * The pins on the keypad are connected to the PCF8574 in an ascending order:
 * P0: 1st pin on the keypad, P1: 2nd pin on the keypad...etc., P7: 8th pin on the keypad
 * Notice that the keypad's first actual pin is the 2nd physical pin (at least on the one I used)
 */

void setup() {
Wire.begin();
  Wire.setClock(400000L);
  Serial.begin(115200);
  lcd.begin();
  lcd.clear();
}

void loop() {

        readKeyPad();//read the keypad
        printLED();//do something if a key was pressed
  
}
void readKeyPad()
{
  if (buttonPressed == true)
  {
    if (millis() - buttonTimer > 300)
    {
      //The button pressed is only set back to false after 300 ms, so we cannot press a button twice quickly
      buttonTimer = millis();
      buttonPressed = false;
    }
  }
  else
  {
    //B11101111
    Wire.beginTransmission(0x20); //00100000
    Wire.write(B11101111);
     //[P7]B11101111[P0] -> [P7]1110[P4] - activates last row, [P3]1111[P0] - Sets all pins high on the MUX
    Wire.endTransmission();
    
    Wire.requestFrom(0x20, 1);
    d = Wire.read();
    switch (d)
    {

      case 231: //Button A
        Serial.println("A");
        pressedCharacter = "A";
        buttonPressed = true;
        break;

      case 235: //Button B
        Serial.println("B");
        pressedCharacter = "B";
        buttonPressed = true;
        break;

      case 237: //Button C
        Serial.println("C");
        pressedCharacter = "C";
        buttonPressed = true;
        break;

      case 238: //Button D
        Serial.println("D");
        pressedCharacter = "D";
        buttonPressed = true;
        break;
    }
    //-------------------------------------------
    //B11011111
    Wire.beginTransmission(0x20); //00100000
    Wire.write(B11011111);
//[P7]B11011111[P0] -> [P7]1101[P4] - activates third row, [P3]1111[P0] - Sets all pins high on the MUX
    Wire.endTransmission();

    Wire.requestFrom(0x20, 1);
    d = Wire.read();
    switch (d)
    {

      case 215: //Button 3
        Serial.println("3");
        pressedCharacter = "3";
        buttonPressed = true;
        break;

      case 219: //Button 6
        Serial.println("6");
        pressedCharacter = "6";
        buttonPressed = true;
        break;

      case 221: //Button 9
        Serial.println("9");
        pressedCharacter = "9";
        buttonPressed = true;
        break;

      case 222: //Button #
        Serial.println("#");
        pressedCharacter = "#";
        buttonPressed = true;
        break;
    }
    //-------------------------------------------
    //B10111111
    Wire.beginTransmission(0x20); //00100000
    Wire.write(B10111111);
    //[P7]B10111111[P0] -> [P7]1011[P4] - activates second row, [P3]1111[P0] - Sets all pins high on the MUX
    Wire.endTransmission();

    Wire.requestFrom(0x20, 1);
    d = Wire.read();
    switch (d)
    {
      case 183: //Button 2
        Serial.println("2");
        pressedCharacter = "2";
        buttonPressed = true;
        break;

      case 187: //Button 5
        Serial.println("5");
        pressedCharacter = "5";
        buttonPressed = true;
        break;

      case 189: //Button 8
        Serial.println("8");
        pressedCharacter = "8";
        buttonPressed = true;
        break;

      case 190: //Button 0
        Serial.println("0");
        pressedCharacter = "0";
        buttonPressed = true;
        break;
    }
    //-------------------------------------------
    //B01111111
    Wire.beginTransmission(0x20); //00100000
    Wire.write(B01111111);
    //[P7]B01111111[P0] -> [P7]0111[P4] - activates First row, [P3]1111[P0] - Sets all pins high on the MUX
    Wire.endTransmission();

    Wire.requestFrom(0x20, 1);
    d = Wire.read();
    switch (d)
    {
      case 119: //Button 1
        Serial.println("1");
        pressedCharacter = "1";
        buttonPressed = true;
        break;

      case 123: //Button 4
        Serial.println("4");
        pressedCharacter = "4";
        buttonPressed = true;
        break;

      case 125: //Button 7
       Serial.println("7");
        pressedCharacter = "7";
        buttonPressed = true;
        break;

      case 126: //Button *
        Serial.println("*");
        pressedCharacter = "*";
        buttonPressed = true;
        break;
    }
    buttonTimer = millis();
  }
}
  
  void printLED()
{
  if (buttonPressed == true) //if a button was pressed...
  {
      lcd.clear();
      //Print the string on the LCD
      lcd.setCursor(0, 0);
      lcd.print(pressedCharacter);
      lcd.setCursor(2, 1);
      lcd.print("is pressed.");
      buttonPressed == false;
  }
}
