// Libs
#include "src/MainSystem.h"
#include "src/libs/LCD_Display.h"
#include "src/libs/Keyboard.h"

// Games
#include "src/games/CounterStrikeBomb.h"
#include "src/games/Domination.h"
#include "src/games/DefuseTheBomb.h"
#include "src/games/HotPoint.h"

const int sdaPin = 20;
const int sclPin = 21;

const int displayRows = 2;
const int displayCols = 16;

const byte keyboardColPins[4] = {11, 10, 9, 8};
const byte keyboardRowPins[4] = {7,6, 5, 4};

// Libs
LCD_Display lcdDisplay(0x27, displayCols, displayRows, sdaPin, sclPin);
Keyboard keyboard(keyboardColPins, keyboardRowPins);

// System
MainSystem mainSystem(lcdDisplay, keyboard);

// Games
CounterStrikeBomb counterStrikeBomb(lcdDisplay);
Domination domination(lcdDisplay);
DefuseTheBomb defuseTheBomb(lcdDisplay);
HotPoint hotPoint(lcdDisplay);

void setup() {

  Serial.begin(9600);

  // Start display
  lcdDisplay.begin();

  // Adding games to main system
  mainSystem.addGame(&counterStrikeBomb);
  mainSystem.addGame(&domination);
  mainSystem.addGame(&defuseTheBomb);
  mainSystem.addGame(&hotPoint);

  // Start system
  mainSystem.start();
}

void loop() {

  char key = keyboard.read();

  if (key == -1) {
    
  }

  mainSystem.updateStatus(key);
}
