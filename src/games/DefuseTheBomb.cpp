#include "DefuseTheBomb.h"
#include <Arduino.h>

DefuseTheBomb::DefuseTheBomb(LCD_Display& lcd) : lcdDisplay(lcd), timeLeft(120) {
}

const char* DefuseTheBomb::getName() {
    return "The bomb";
}

void DefuseTheBomb::init() {

    Serial.println("Init game");

    cursorPos = 0;
    timeLeft = 0;
    status = GameStatus::MENU;
}

void DefuseTheBomb::showMenu() {

    const int rows = lcdDisplay.getRows();
    const int selectorPos = cursorPos % rows;
    lcdDisplay.clear();
    lcdDisplay.printCursor(selectorPos);

    
}

bool DefuseTheBomb::start() {
    return true;
}

bool DefuseTheBomb::end() {
    return true;
}

int DefuseTheBomb::updateStatus(int key) {
    return 1;  // Game still in progress
}

void DefuseTheBomb::showAttributesInSerialMonitor() {
    
}
