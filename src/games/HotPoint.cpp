#include "HotPoint.h"
#include <Arduino.h>

HotPoint::HotPoint(LCD_Display& lcd) : lcdDisplay(lcd), timeLeft(120) {
}

const char* HotPoint::getName() {
    return "Hot Point";
}

void HotPoint::init() {

    Serial.println("Init game");

    cursorPos = 0;
    timeLeft = 0;
    status = GameStatus::MENU;
}

void HotPoint::showMenu() {

    const int rows = lcdDisplay.getRows();
    const int selectorPos = cursorPos % rows;
    lcdDisplay.clear();
    lcdDisplay.printCursor(selectorPos);

    
}

bool HotPoint::start() {
    return true;
}

bool HotPoint::end() {
    return true;
}

int HotPoint::updateStatus(int key) {
    return 1;  // Game still in progress
}

void HotPoint::showAttributesInSerialMonitor() {

}
