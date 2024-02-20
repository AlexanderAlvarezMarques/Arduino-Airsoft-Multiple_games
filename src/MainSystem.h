#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#ifndef KEYBOARD_H_INCLUDED
  #define KEYBOARD_H_INCLUDED
  #include "libs/Keyboard.h"
#endif

#include "games/GameInterface.h"
#include "libs/LCD_Display.h"
#include <ArduinoSTL.h>
#include <vector>

class MainSystem {

  private:

    GameInterface* currentGame;
    std::vector<GameInterface*> availableGames;
    
    LCD_Display& lcdDisplay;
    Keyboard& keyboard;

    // Cursor
    int cursorPos;
    int nGame;

    enum Status {
      MAIN_MENU,
      IN_GAME,
      PAUSED,
      ENDED
    };

    Status status;

    void runGame();

    void stopGame();

    void pauseGame();

    void changeGame();

    void showMainMenu();

    void updateInMainMenuStatus(int key);

    void updateInGameStatus(int key);

    void updateCursor(int update);

  public:

    MainSystem(LCD_Display& _lcd, Keyboard& _keyboard);

    void start();

    void updateStatus(int key);

    void addGame(GameInterface* newGame);
};

#endif