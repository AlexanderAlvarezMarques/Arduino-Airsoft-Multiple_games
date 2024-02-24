#ifndef DEFUSETHEBOMB_H_INCLUDED
#define DEFUSETHEBOMB_H_INCLUDED

#include "GameInterface.h"
#include "../libs/LCD_Display.h"

class DefuseTheBomb : public GameInterface {

private:

    const int menuSize = 3;
    const char* menu[3] = {
        "Empezar",
        "Configurar",
        "Salir"
    };

    LCD_Display& lcdDisplay;
    
    int timeLeft;  // Time left to defuse the bomb in seconds
    int cursorPos;

    GameStatus status;


public:
    
    DefuseTheBomb(LCD_Display& lcd);
    
    const char* getName() override;

    void init() override;

    void showMenu() override;
    
    bool start() override;
    
    bool end() override;
    
    int updateStatus(int key) override;

    void showAttributesInSerialMonitor();
};

#endif
