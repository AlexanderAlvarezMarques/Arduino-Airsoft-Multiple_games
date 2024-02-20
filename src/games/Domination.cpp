#include "Domination.h"

Domination::Domination(LCD_Display& lcd)
	: lcdDisplay(lcd)
{
}

const char* Domination::getName() {
    return "Dominacion";
}

void Domination::init() {
    
}

void Domination::showMenu(){
    
}

bool Domination::start() {
    return true;
}

bool Domination::end() {
    return true;
}

int Domination::updateStatus(int key) {
    return 1;  // Game still in progress
}

void Domination::showAttributesInSerialMonitor() {

}
