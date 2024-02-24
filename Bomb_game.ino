// Libs
#include "src/MainSystem.h"
#include "src/libs/LCD_Display.h"
#include "src/libs/Keyboard.h"
#include <EasyBuzzer.h>

// Games
#include "src/games/CounterStrikeBomb.h"
#include "src/games/Domination.h"
#include "src/games/DefuseTheBomb.h"
#include "src/games/HotPoint.h"

const int sdaPin = 20;
const int sclPin = 21;

const int pinRedTeam = 12;
const int pinBlueTeam = 13;

const int displayRows = 2;
const int displayCols = 16;

const byte keyboardColPins[4] = {11, 10, 9, 8};
const byte keyboardRowPins[4] = {7, 6, 5, 4};

const int buzzerPin = 3;

// Libs
LCD_Display lcdDisplay(0x27, displayCols, displayRows, sdaPin, sclPin);
Keyboard keyboard(keyboardColPins, keyboardRowPins);
Buzzer buzzer(buzzerPin);

// System
MainSystem mainSystem(lcdDisplay, keyboard);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
// Games
CounterStrikeBomb counterStrikeBomb(lcdDisplay, buzzer);
Domination domination(lcdDisplay, buzzer, pinRedTeam, pinBlueTeam);
//DefuseTheBomb defuseTheBomb(lcdDisplay);
//HotPoint hotPoint(lcdDisplay);

void setup() {

  Serial.begin(9600);

  // Start display
  lcdDisplay.begin();

  // Config pull up buttons
  pinMode(pinRedTeam, INPUT_PULLUP);
  pinMode(pinBlueTeam, INPUT_PULLUP);
  digitalWrite(pinRedTeam, HIGH);
  digitalWrite(pinBlueTeam, HIGH);

  // Adding games to main system
  mainSystem.addGame(&counterStrikeBomb);
  mainSystem.addGame(&domination);
  //mainSystem.addGame(&defuseTheBomb);
  //mainSystem.addGame(&hotPoint);

  // Start system
  mainSystem.start();
}

void loop() {
  char key = keyboard.read();

  if (key == -1) {
    if (!digitalRead(pinRedTeam)) key = 100;
    if (!digitalRead(pinBlueTeam)) key = 101;
  }

  mainSystem.updateStatus(key);
}
