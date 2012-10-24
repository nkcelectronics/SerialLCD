/*
 
 NKC v1 22/OCT/2012 orders@nkcelectronics.com http://www.nkcelectronics.com
 
 What is this?
 
 An arduino library for use with the NKC Electronics Serial LCD Display in RS232, I2C or SPI mode
 
 RS232 (UART) interface:
 
 Digital pin 1 - TX
 or any digital pin using SoftSerial library
 
 I2C interface:
 
 Analog pin 4 - SDA
 Analog pin 5 - SCL
 
 SPI interface:
 
 ICSP
 
 Usage:
 
 see the examples folder of this library distribution.
 
 
 */

#include "SerialLCD.h"
#include <Wire.h>

//--------------------------------------------------------

// (don't change here - specify on calling constructor)

// LCD lines and columns 
int g_num_lines = 2;
int g_num_col = 16;

// Default address, interface and baud of the display

int g_i2c_address = 0x28;
int g_interface = 0; // 0 = Serial; 1 = i2c; 2 = SPI
int g_baudrate = 9600;

// Index to position cursor based on line and column (specific for NKC Serial displays)
int g_index[4] = { 0x00, 0x40, 0x14, 0x54 };


//stuff the library user might call---------------------------------

//constructor.  num_lines must be 1, 2, 3, or 4 currently.

SerialLCD::SerialLCD (int num_lines,int num_col,int i2c_address,int interface){
	
	g_num_lines = num_lines;
	g_num_col = num_col;
	
	switch (interface) {
		case RS232:
			g_baudrate = i2c_address;
			break;
		case I2C:
			g_i2c_address = i2c_address;
			g_interface = interface;
			break;
		case SPI:
			break;
	}
	
	if (g_num_lines < 1 || g_num_lines > 4) {
		g_num_lines = 2;
	}
	
	if (g_num_col < 1 || g_num_col > 40) {
		g_num_col = 16;
	}
}

// Low level functions
// send command without parameter
void sendcommand(unsigned char command) {
	switch (g_interface) {
		case RS232: 
			Serial.write(0xFE);
			Serial.write(command);
			break;
		case I2C:
			Wire.beginTransmission(g_i2c_address);
			Wire.write(0xFE);
			Wire.write(command);
			Wire.endTransmission();
			break;
		case SPI:
			break;
	}
}

// send command without parameter
void sendcommand2(unsigned char command, unsigned char value) {
	switch (g_interface) {
		case RS232: 
			Serial.write(0xFE);
			Serial.write(command);
			Serial.write(value);
			break;
		case I2C:
			Wire.beginTransmission(g_i2c_address);
			Wire.write(0xFE);
			Wire.write(command);
			Wire.write(value);
			Wire.endTransmission();
			break;
		case SPI:
			break;
	}
}

//	Send a command to the display that is not supported
void SerialLCD::command(int value) {
	sendcommand2(COMMAND, value);
}

//Used by the print library to get information to the display
size_t SerialLCD::write(uint8_t value) {
	switch (g_interface) {
		case RS232: 
			Serial.write(value);
			break;
		case I2C:
			Wire.beginTransmission(g_i2c_address);
			Wire.write(value);
			Wire.endTransmission();
			break;
		case SPI:
			break;
	}
}

//send the clear screen command to the LCD

void SerialLCD::clear(){
	sendcommand(CLEAR);
}

//send the Home Cursor command to the LCD
void SerialLCD::home(){
    sendcommand(HOME);	
}

//Turn the LCD ON
void SerialLCD::on(){
    sendcommand(ON);	
}

// Turn the LCD OFF
void SerialLCD::off(){
    sendcommand(OFF);	
}

//Turn the Underline Cursor ON
void SerialLCD::cursorOn(){
    sendcommand(CURSOR_ON);	
}

//Turn the Underline  Cursor OFF
void SerialLCD::cursorOff(){
    sendcommand(CURSOR_OFF);	
}

//Turn the Blink Cursor ON
void SerialLCD::blinkOn(){
    sendcommand(BLINK_ON);	
}

//Turn the Blink  Cursor OFF
void SerialLCD::blinkOff(){
    sendcommand(BLINK_OFF);	
}

//Move the cursor left 1 space
void SerialLCD::left(){
    sendcommand(LEFT);	
}

//Move the cursor right 1 space
void SerialLCD::right(){
	sendcommand(RIGHT);
}

//Backspace
void SerialLCD::backspace(){
    sendcommand(BACKSPACE);
}

//Shift display left 1 position
void SerialLCD::shiftLeft(){
    sendcommand(SHIFTLEFT);
}

//Shift display right 1 position
void SerialLCD::shiftRight(){
    sendcommand(SHIFTRIGHT);
}

//Display firmware version
void SerialLCD::displayVersion(){
    sendcommand(DISPLAYVERSION);
}

//Display Serial interface baud rate
void SerialLCD::displayBaudRate(){
    sendcommand(DISPLAYBAUDRATE);
}

//Display I2C interface address (8-bit)
void SerialLCD::displayI2CAddress(){
    sendcommand(DISPLAYI2CADDRESS);
}

//Change RS232 interface baud rate
void SerialLCD::changeBaudRate(unsigned char baud){
    sendcommand2(CHANGEBAUDRATE, baud);
}

//Change I2C address (in 8-bit format)
void SerialLCD::changeI2CAddress(unsigned char addr){
    sendcommand2(CHANGEI2CADDRESS, addr);
}

// initiatize lcd after a short pause
//while there are hard-coded details here of lines, cursor and blink settings, you can override these original settings after calling .init()

void SerialLCD::init () {
	delay(500);
	switch (g_interface) {
		case RS232:
			Serial.begin(9600);
			break;
		case I2C:
			Wire.begin();
			break;
		case SPI:
			break;
	}
	on();
	clear();
	blinkOff();
	cursorOff(); 
	home();
}

//Set cursor
void SerialLCD::setCursor(int line_num, int x){
	sendcommand2(SETCURSOR, g_index[line_num-1] + x - 1);
}

//Create custom character
void SerialLCD::createChar(unsigned char char_num, unsigned char *rows)
{	
	switch (g_interface) {
		case RS232:
			Serial.write(0xFE);
			Serial.write(LOADCUSTOMCHARACTER);
			Serial.write(char_num);
			Serial.write(rows, CUSTOM_CHAR_SIZE);
			break;
		case I2C:
			Wire.beginTransmission(g_i2c_address);
			Wire.write(0xFE);
			Wire.write(LOADCUSTOMCHARACTER);
			Wire.write(char_num);
			Wire.write(rows, CUSTOM_CHAR_SIZE);
			Wire.endTransmission();
			break;
		case SPI:
			break;
	}
}

void SerialLCD::setBacklightBrightness(unsigned char new_val)
{
	if ((new_val < MIN_BRIGHTNESS)
		|| (new_val > MAX_BRIGHTNESS))
		new_val = MAX_BRIGHTNESS >> 1; // mid point value
	
	sendcommand2(SETBACKLIGHTBRIGHTNESS, new_val);
}

void SerialLCD::setContrast(unsigned char new_val)
{
	if ((new_val < MIN_CONTRAST)
		|| (new_val > MAX_CONTRAST))
		new_val = MAX_CONTRAST >> 1; // mid point value

	sendcommand2(SETCONTRAST, new_val);
}

// Overload 
void  SerialLCD::printstr(const char c[])
{
	byte len;

	len = min(strlen(c), MAX_STRLEN);
	switch (g_interface) {
		case RS232:
			while (len--)
				Serial.write(*c++);
			break;
		case I2C:
			Wire.beginTransmission(g_i2c_address);
			//Wire.write(len);
			while (len--)
				Wire.write(*c++);
			Wire.endTransmission();
			break;
		case SPI:
			break;
		}
}

