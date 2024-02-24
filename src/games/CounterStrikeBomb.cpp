#include "CounterStrikeBomb.h"
#include <Arduino.h>
#include "../libs/Buzzer.h"

CounterStrikeBomb::CounterStrikeBomb(LCD_Display& lcd, Buzzer& _buzzer) :
    lcdDisplay(lcd),
    buzzer(_buzzer)
{
}

const char* CounterStrikeBomb::getName() {
    return "CS Bomb";
}

void CounterStrikeBomb::init() {
    cursorPos = 0;
    timeLeft = 0;
    timeLimit = 0;
    isPasswordSet = false;
    isTimeLimitSet = false;
    isConfigSet = false;
    exitGame = 0;
    bombActive = false;

    for (int i = 0; i < passwordSize; i++) {
        password[i] = 0;
        defusePassword[i] = -1;
    }

    status = GameStatus::MENU;
}

void CounterStrikeBomb::showMenu() {

    const int rows = lcdDisplay.getRows();
    const int selectorPos = cursorPos % rows;
    lcdDisplay.clear();
    lcdDisplay.printCursor(selectorPos);

    for (int i = 0; i < rows; i++) {
        int menuIndex = cursorPos - selectorPos + i;
        if (menuIndex >= 0 && menuIndex < menuSize) {
            char* name = menu[menuIndex];
            lcdDisplay.write(name, i % rows == selectorPos ? 2 : 0, i);
        }
    }
}

void CounterStrikeBomb::updateCursor(int update) {
    cursorPos = cursorPos + update;

    if (cursorPos == menuSize) {
        cursorPos = 0;
    }

    if (cursorPos == -1) {
        cursorPos = menuSize - 1;
    }
}

bool CounterStrikeBomb::start() {
    return true;
}

bool CounterStrikeBomb::end() {
    return true;
}

int CounterStrikeBomb::updateStatus(int key) {
    
    switch(status) {
        case GameStatus::MENU:
            updateInMenuStatus(key);
            break; // Add a break statement here
        case GameStatus::CONFIG:
            updateInConfigStatus(key);
            break;
        case GameStatus::IN_GAME:
            updateInGameStatus(key);
            break;
        case GameStatus::PAUSED:
            // Handle PAUSED status
            break;
        default:
            // Handle any other status that might occur
            break;
    }

    return status;
}

void CounterStrikeBomb::updateInMenuStatus(int key) {

    switch(key) {
        case 12:
            updateCursor(-1);
            showMenu();
            break;
        case 13:
            updateCursor(+1);
            showMenu();
            break;
        case 14:
            checkAction(key);
            break;
    }
}

void CounterStrikeBomb::updateInConfigStatus(int key) {

    if (key == 15) status = GameStatus::MENU;
    if (key >= 10 && key < 14 || key == -1) return;

    if (!isPasswordSet) {
        readPassword(key);
    } else if (!isTimeLimitSet) {
        readTimeLimit(key);
    }

    if (isPasswordSet && isTimeLimitSet) {
        status = GameStatus::MENU;
        isConfigSet = true;
        showMenu();
    }
}

void CounterStrikeBomb::updateInGameStatus(int key) {

    if (key == 15) {
        exitGame++;

        if (exitGame == 3) {
            init();
            showMenu();
            return;
        }
    }

    if (!bombActive) {
        if (key >= 0 && key <= 9) {
            if (passwordCursorPos == 0) lcdDisplay.clearRowAfterCol(0, 1);
            lcdDisplay.write(key, passwordCursorPos, 1);

            defusePassword[passwordCursorPos] = key;
            passwordCursorPos++;

            if (passwordCursorPos >= passwordSize) passwordCursorPos = 0;
        } else if (key == 11) {
            if (checkDefusePassword()) {
                bombActive = true;
                for (int i = 0; i < passwordSize; i++) {
                    defusePassword[i] = -1;
                }

                lcdDisplay.clear();
                lcdDisplay.write("Desactivar", 0, 0);
                lcdDisplay.write("Clave", 0, 1);
            }
        }
    } else {
        if (timeLeft > 0) {
            int lapseTime = timer.getIntervalInSeconds();

            if (lapseTime >= 1) {
                timeLeft--;
                showDetonationTime();

                if (timeLeft > 60) buzzer.beep();
                else buzzer.beepTree();
            }

            if (key >= 0 && key <= 9) {
                if (passwordCursorPos == 0) lcdDisplay.clearRowAfterCol(6, 1);
                lcdDisplay.write(key, 6 + passwordCursorPos, 1);

                defusePassword[passwordCursorPos] = key;
                passwordCursorPos++;

                if (passwordCursorPos >= passwordSize) passwordCursorPos = 0;
            } else {
                if (key == 11) { // # => 11
                    Serial.println("Active");
                    if (checkDefusePassword()) {
                        timeLeft = 0;
                    } else {
                        for (int i = 0; i < 4; i++) {
                            lcdDisplay.write("Invalido", 6, 1);
                            delay(250);
                            lcdDisplay.clearRowAfterCol(6, 1);
                            delay(250);
                        }

                        passwordCursorPos = 0;
                    }
                }
            }
        } else {
            lcdDisplay.clear();
            lcdDisplay.write("Ganador equipo:", 0, 0);
            char* winner = checkDefusePassword() ? "Anti terrorista" : "Terrorista";
            lcdDisplay.write(winner, 0, 1);

            if (winner == "Anti terrorista") {
                buzzer.playAntiterroristWin();
            } else {
                buzzer.playTerroristWin();
            }

            status = GameStatus::MENU;
            passwordCursorPos = 0;
            bombActive = false;
            for (int i = 0; i < passwordSize; i++) defusePassword[i] = -1;
            timeLeft = timeLimit;
            showMenu();
        }
    }   
}

void CounterStrikeBomb::readPassword(int key) {

    if (key == 14) {
        isPasswordSet = true;
        passwordCursorPos = 0;

        lcdDisplay.clear();
        lcdDisplay.write("Tiempo (min)", 0, 0);
    } else if (key >= 0 && key <= 9) {
        if (passwordCursorPos == passwordSize) {
            lcdDisplay.clearRow(1);
            passwordCursorPos = 0;
        }

        password[passwordCursorPos] = (char) key;
        lcdDisplay.write(key, passwordCursorPos, 1);
        passwordCursorPos++;
    }
}

void CounterStrikeBomb::readTimeLimit(int key) {
    
    if (key == 14 && timeLimit > 0) {
        isTimeLimitSet = true;
        timeLimit *= 60; // Transform to seconds
        timeLeft = timeLimit;
        status = GameStatus::MENU;
    } else {
        timeLimit = (timeLimit * 10) + key;
        lcdDisplay.write(timeLimit, 0, 1);

        if (timeLimit > 60) {
            lcdDisplay.clearRow(1);
            timeLimit = 0;
        }
    }
}

void CounterStrikeBomb::checkAction(int key) {

    char* currentMenu = menu[cursorPos];

    if (currentMenu == "Empezar" && isConfigSet) {
        status = GameStatus::IN_GAME;
        timer.start(1); // Update at 1s
        lcdDisplay.clear();
        lcdDisplay.write("Cod. Activacion ", 0, 0);
    }

    if (currentMenu == "Configurar") {
        status = GameStatus::CONFIG;
        passwordCursorPos = 0;
        isConfigSet = false;
        isPasswordSet = false;
        isTimeLimitSet = false;
        lcdDisplay.clear();
        lcdDisplay.write("Clave [", 0, 0);
        lcdDisplay.write(passwordSize, 7, 0);
        lcdDisplay.write("]", 8, 0);
    }

    if (currentMenu == "Salir") {
        status = GameStatus::ENDED;
    }
}

bool CounterStrikeBomb::checkDefusePassword() {
    for (int i = 0; i < passwordSize; i++) {
        if (defusePassword[i] != password[i]) return false;
    }

    return true;
}

void CounterStrikeBomb::showDetonationTime() {
    lcdDisplay.clearRowAfterCol(11, 0);

    int min = timeLeft / 60;
    int sec = timeLeft % 60;

    lcdDisplay.write(min / 10, 11, 0);
    lcdDisplay.write(min % 10, 12, 0);
    lcdDisplay.write(":", 13, 0);
    lcdDisplay.write(sec / 10, 14, 0);
    lcdDisplay.write(sec % 10, 15, 0);
}
