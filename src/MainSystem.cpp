#include "MainSystem.h"

MainSystem::MainSystem(LCD_Display& _lcd, Keyboard& _keyboard) :
  currentGame(nullptr),
  lcdDisplay(_lcd),
  keyboard(_keyboard)
{
}

/* ----------------- */
/* ---- Private ---- */
/* ----------------- */
void MainSystem::showMainMenu() {

    const int rows = lcdDisplay.getRows();
    const int selectorPos = cursorPos % rows;
    lcdDisplay.clear();
    lcdDisplay.printCursor(selectorPos);

    for (int i = 0; i < rows; i++) {
        int gameIndex = cursorPos - selectorPos + i;
        if (gameIndex >= 0 && gameIndex < availableGames.size()) {
            char* name = availableGames.at(gameIndex)->getName();
            lcdDisplay.write(name, i % rows == selectorPos ? 2 : 0, i);
        }
    }

}

void MainSystem::updateCursor(int update) {
    cursorPos = cursorPos + update;

    if (cursorPos == availableGames.size()) {
        cursorPos = 0;
    }

    if (cursorPos == -1) {
        cursorPos = availableGames.size() - 1;
    }
}

void MainSystem::runGame() {
    currentGame = availableGames.at(cursorPos);
    status = Status::IN_GAME;

    currentGame->init();
    currentGame->showMenu();
}

/* ---------------- */
/* ---- PUBLIC ---- */
/* ---------------- */
void MainSystem::start() {
    showMainMenu();
}

void MainSystem::updateStatus(int key) {

    switch(status) {
        case Status::MAIN_MENU:
            updateInMainMenuStatus(key);
            break;
        case Status::IN_GAME:
            updateInGameStatus(key);
            break;
        default:
            break;
    }

}

void MainSystem::updateInMainMenuStatus(int key) {
    if (status == Status::MAIN_MENU) {
        if (keyboard.isLastKeyChar()){
            switch(key) {
                case 12:
                    updateCursor(-1);
                    showMainMenu();
                    break;
                case 13:
                    updateCursor(1);
                    showMainMenu();
                    break;
                case 14:
                    runGame();
                    break;
            }
        }
    }
}

void MainSystem::updateInGameStatus(int key) {

    int gameStatus = currentGame->updateStatus(key);

    if (gameStatus == GameInterface::GameStatus::ENDED) {
        status = Status::MAIN_MENU;
        showMainMenu();
    }
}

void MainSystem::addGame(GameInterface* newGame) {
    availableGames.push_back(newGame);
}


