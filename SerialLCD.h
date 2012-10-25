/* NKC Electronics */
#ifndef SerialLCD_h
#define SerialLCD_h

// Include files
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

// #include "Print.h"

// Min and Max values
#define MIN_BRIGHTNESS		1
#define MAX_BRIGHTNESS		8
#define VALUE_OUT_OF_RANGE	1
#define MIN_CONTRAST		1
#define MAX_CONTRAST		50
#define MAX_STRLEN			40

// Baud Rate parameters in UART mode
#define BAUD_300				1
#define BAUD_1200				2	
#define BAUD_2400				3	
#define BAUD_9600				4	
#define BAUD_14400			5	
#define BAUD_19200			6	
#define BAUD_57600			7	
#define BAUD_115200			8	

// Interface values
#define RS232					1
#define I2C					2
#define SPI					3

// Custom Character constants
#define NUM_CUSTOM_CHARS 8		// 0 to 7
#define CUSTOM_CHAR_SIZE 8

// Serial LCD module commands
#define ON					0x41
#define OFF					0x42
#define SETCURSOR			0x45
#define HOME				0x46
#define CURSOR_ON			0x47
#define CURSOR_OFF			0x48
#define LEFT				0x49
#define RIGHT				0x4A
#define BLINK_ON			0x4B
#define BLINK_OFF			0x4C
#define BACKSPACE			0x4E
#define CLEAR				0x51
#define SETCONTRAST			0x52
#define SETBACKLIGHTBRIGHTNESS	0x53
#define LOADCUSTOMCHARACTER	0x54
#define SHIFTLEFT			0x55
#define SHIFTRIGHT			0x56
#define CHANGEBAUDRATE		0x61
#define CHANGEI2CADDRESS	0x62
#define DISPLAYVERSION		0x70
#define DISPLAYBAUDRATE		0x71
#define DISPLAYI2CADDRESS	0x72
#define COMMAND				0xFE

#define SPIDELAY			5

class SerialLCD : public Print {

public: 

  SerialLCD(int num_lines,int num_col,int i2c_address,int interface);
	  
  void command(int value);
  void init();
  virtual size_t write(uint8_t);
  void clear();
  void home();
  void on();
  void off();
  void cursorOn();
  void cursorOff();
  void blinkOn();
  void blinkOff();
  void left();
  void right();
  void backspace();
  void shiftLeft();
  void shiftRight();
  void displayVersion();
  void displayBaudRate();
  void displayI2CAddress();
  void changeBaudRate(unsigned char baud);
  void changeI2CAddress(unsigned char addr);
 
  // Overload the Print class function for strings because
  // the base class implementation causes problems by doing
  // an I2C I/O for every character
  void printstr(const char[]);
  void setCursor(int line_num, int x);
  void createChar(unsigned char char_num, unsigned char *rows);
  void setBacklightBrightness(unsigned char new_val);
  void setContrast(unsigned char new_val);
	
private:	

};
#endif

