#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#include <Keypad.h>

class Keyboard {

private:

  static const byte rowsCount = 4;
  static const byte colsCount = 4;

  char keys[rowsCount][colsCount] = {
    { '1','2','3', 'A' },
    { '4','5','6', 'B' },
    { '7','8','9', 'C' },
    { '*','0','#', 'D' }
  };

  byte rowPins[rowsCount];
  byte colPins[colsCount];
  int lastKeyPressed = -1;

  Keypad keypad;

  char readKeypad();

  int charToInt(char key);

public:

  Keyboard(byte _rowPins[rowsCount], byte _colPins[colsCount]);

  int read();

  int getLastKeyPressed();

  bool isLastKeyChar();

};

#endif