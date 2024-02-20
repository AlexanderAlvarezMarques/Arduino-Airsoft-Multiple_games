#ifndef COUNTERSTRIKEBOMB_H_INCLUDED
#define COUNTERSTRIKEBOMB_H_INCLUDED

#include "GameInterface.h"
#include "../libs/LCD_Display.h"
#include "../libs/Timer.h"

class CounterStrikeBomb : public GameInterface {

private:

    const int menuSize = 3;
    const char* menu[3] = {
        "Empezar",
        "Configurar",
        "Salir"
    };

    LCD_Display& lcdDisplay;
    
    int cursorPos;

    int passwordCursorPos = 0;
    const int passwordSize = 5;
    int password[5];
    bool isPasswordSet;

    int defusePassword[5];

    int timeLeft;  // Time left to defuse the bomb in seconds
    int timeLimit;
    bool isTimeLimitSet;

    bool isConfigSet = false;
    int exitGame = 0;

    GameStatus status;
    Timer timer;

    void showConfigMenu();

    void updateCursor(int update);

    void updateInMenuStatus(int key);

    void updateInConfigStatus(int key);

    void updateInGameStatus(int key);

    void checkAction(int key);

    void readPassword(int key);

    void readTimeLimit(int key);

    void showDetonationTime();

    bool checkDefusePassword();

public:
    
    CounterStrikeBomb(LCD_Display& lcd);
    
    const char* getName() override;

    void init() override;

    void showMenu() override;
    
    bool start() override;
    
    bool end() override;
    
    int updateStatus(int key) override;

    void showAttributesInSerialMonitor() override;
};

#endif
