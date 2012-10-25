/*
  NKC Electronics serial display - Demo
 
 Demonstrates different functions of the Serial LCD module
 
  The circuit:
 * LCD SCL pin to Arduino SCL pin or Analog 5
 * LCD SDA pin to Arduino SDA pin or Analog 4
 * LCD VSS pin to GND
 * LCD VDD pin to +5V
 */
 
#include <SerialLCD.h>
#include <Wire.h>

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

// Constructor.  Parameters: rows, columns, baud/i2c_address, interface (RS232, I2C, SPI)
SerialLCD lcd(2,40,9600,RS232);

void setup() {
  
  // Initialize LCD module
  lcd.init();
  
  // create a new character
  lcd.createChar(0, heart);
  // create a new character
  lcd.createChar(1, smiley);
  // create a new character
  lcd.createChar(2, frownie);
  // create a new character
  lcd.createChar(3, armsDown);
  // create a new character
  lcd.createChar(4, armsUp);
    
  // Set Contrast
  lcd.setContrast(40);
  // Set Backlight
  lcd.setBacklightBrightness(8);
}

void loop() {
  int i;
  
  lcd.home();
  lcd.displayVersion();
  delay(2000);
  lcd.clear();
  lcd.displayBaudRate();
  delay(2000);
  lcd.clear();
  lcd.displayI2CAddress();
  delay(2000);
  lcd.clear();
  
  // Write some text to the display.  Show custom characters
  lcd.home();
  lcd.setCursor(1, 1);
  lcd.print("CustomChars");
  lcd.write((byte)0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  
  // blinking cursor, move cursor and change text
  lcd.setCursor(2, 1);
  lcd.print("This is original");
  
  delay(2000);
  
  lcd.setCursor(2, 1);
  lcd.blinkOn();
  
  for (i=0; i<8; i++) {
    lcd.right();
    delay(100);
  }
  lcd.print("modified");
    
  lcd.blinkOff();

  delay(2000);
  
  lcd.setCursor(2, 1);
  lcd.print("scrolling text..");
  lcd.setCursor(1,6);
  for (i=0; i<15; i++) {
    delay(100);
    lcd.shiftRight();
  }
  for (i=0; i<15; i++) {
    delay(100);
    lcd.shiftLeft();
  }
  
  delay(2000);
  
  for (i=0; i<MAX_CONTRAST; i++) {
    lcd.setContrast(i);
    delay(100);
  }
  
  delay(2000);
  
  for (i=0; i<MAX_BRIGHTNESS; i++) {
    lcd.setBacklightBrightness(i);
    delay(100);
  }
  
  delay(2000);
  
    // Set Contrast
  lcd.setContrast(40);
  // Set Backlight
  lcd.setBacklightBrightness(8);
  
  delay(2000);
}

  



