#ifndef LCD_DISPLAY_H_INCLUDED
#define LCD_DISPLAY_H_INCLUDED

#ifndef ARDUINO_H_INCLUDED
  #define ARDUINO_H_INCLUDED
  #include <Arduino.h>
#endif

#include <LiquidCrystal_I2C.h>

class LCD_Display {

  private:
  
    // Attributes
    byte address;
    int scl;
    int sda;
    int rows;
    int cols;

    LiquidCrystal_I2C lcd;

    // Const
    const int mainMenuSize;
    const int configMenuSize;

    static const char* mainMenu[];
    static const char* configMenu[];

  public:
  
    // Constructor
    LCD_Display(byte _address, int _cols, int _rows, int _sda, int _scl);

    void begin();

    void clear();

    void clearRow(int row);

    void clearCol(int col);

    void clearRowAfterCol(int col, int row);

    void printCursor(int row);

    void write(char* msg, int col, int row);

    void write(int num, int col, int row);

    void showMainMenu(int cursorRowPosition);

    void showPassword(int cursorRowPosition);

    void timeLimit(int minutes, int seconds);

    int getRows();
};

#endif
