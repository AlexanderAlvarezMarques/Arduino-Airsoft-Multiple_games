#include "LCD_Display.h"

const byte menuArrorChar[8] = {
      B11000,
      B01100,
      B00110,
      B00011,
      B00011,
      B00110,
      B01100,
      B11000
    };

const byte LoadBarChar[8] = {
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
    };

// Constructor implementation
LCD_Display::LCD_Display(byte _address, int _cols, int _rows, int _sda, int _scl)
    : // With this line we init all attributes
    address(_address),
    rows(_rows),
    cols(_cols),
    sda(_sda),
    scl(_scl),
    lcd(_address, _cols, _rows)
{
}

void LCD_Display::begin() {
  lcd.begin();

  // Custom chars
  lcd.createChar(0, menuArrorChar);
  lcd.createChar(1, LoadBarChar);
}

void LCD_Display::clear() {
  lcd.clear();
}

void LCD_Display::clearRow(int row) {
  lcd.setCursor(0, row);
  for (int i = 0; i < cols; i++) {
    lcd.print(" ");
  }
}

void LCD_Display::clearCol(int col) {
  for (int i = 0; i < rows; i++) {
    lcd.setCursor(col, i);
    lcd.print(" ");
  }
}

void LCD_Display::clearRowAfterCol(int col, int row) {
  lcd.setCursor(col, row);
  for (int i = col; i < cols; i++) {
    lcd.print(" ");
  }
}

void LCD_Display::printCursor(int row) {
  lcd.setCursor(0, row);
  lcd.write((uint8_t)0); // o => index of char defined in begin function
}

void LCD_Display::printLoadBar(int col, int row) {
  lcd.setCursor(col, row);
  lcd.write((uint8_t) 1);
}

void LCD_Display::write(char* msg, int col, int row) {
  lcd.setCursor(col, row);
  lcd.print(msg);
}

void LCD_Display::write(int num, int col, int row) {
  String strNum = String(num);
  char* charPtr = strNum.c_str();
  write(charPtr, col, row);
}

void LCD_Display::showMainMenu(int cursorRowPosition) {
  return;
}

void LCD_Display::showPassword(int cursorRowPosition) {
  return;
}

void LCD_Display::timeLimit(int minutes, int seconds) {
  return;
}

int LCD_Display::getRows() {
  return rows;
}

int LCD_Display::getCols() {
  return cols;
}