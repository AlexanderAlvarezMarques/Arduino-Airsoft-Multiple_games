#include "Keyboard.h"

Keyboard::Keyboard(byte _rowPins[], byte _colPins[])
    :
    keypad(makeKeymap(keys), _rowPins, _colPins, rowsCount, colsCount)
{
  for (int i = 0; i < rowsCount; ++i) {
    rowPins[i] = _rowPins[i];
  }

  for (int i = 0; i < colsCount; ++i) {
    colPins[i] = _colPins[i];
  }
}

char Keyboard::readKeypad () {
  char key;
  key = keypad.getKey();
  return key;
}

int Keyboard::charToInt(char key) {

  if (key >= '0' && key <= '9')
    return key - '0';

  switch (key) {
    case '*': return 10;
    case '#': return 11;
    case 'A': return 12;
    case 'B': return 13;
    case 'C': return 14;
    case 'D': return 15;
    default: return -1;
  }
}

int Keyboard::read() {
  lastKeyPressed = charToInt(readKeypad());
  return lastKeyPressed;
}

int Keyboard::getLastKeyPressed() {
  return lastKeyPressed;
}

bool Keyboard::isLastKeyChar() {
  int key = getLastKeyPressed();
  return key >= 12 && key <= 15;
}
