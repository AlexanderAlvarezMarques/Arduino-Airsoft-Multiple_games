#include "Domination.h"
#include <EasyBuzzer.h>

Domination::Domination(LCD_Display& lcd, Buzzer& _buzzer, int _redTeamPin, int _blueTeamPin)
	:
    lcdDisplay(lcd),
    buzzer(_buzzer),
    pinRedTeam(_redTeamPin),
    pinBlueTeam(_blueTeamPin)
{
}

const char* Domination::getName() {
    return "Dominacion";
}

void Domination::init() {
    timeLimit = 0;
    timeLeftRedTeam = 0;
    timeLeftBlueTeam = 0;
    isConfigured = false;
    isTimeLimitSet = false;
    isCaptureTimeSet = false;
    cursorTimeLimitPos = 0;
    capturingFlag = 0;
    exitGame = 0;
    captureFlagTime = 0;
    status = GameStatus::MENU;
    timer_2.start(1);
}

void Domination::showMenu(){
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

bool Domination::start() {
    return true;
}

bool Domination::end() {
    return true;
}

int Domination::updateStatus(int key) {
    
    switch(status) {
        case GameStatus::MENU:
            updateInMenuStatus(key);
            break;
        case GameStatus::CONFIG:
            updateInConfigStatus(key);
            break;
        case GameStatus::IN_GAME:
            updateInGameStatus(key);
            break;
    }

    return status;
}

void Domination::updateInMenuStatus(int key) {

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
            checkAction();
            break;
    }

}

void Domination::updateInConfigStatus(int key) {
    
    if (!isConfigured) {
        if (key >= 0 && key <= 9) {
            if (!isTimeLimitSet) {
                timeLimit *= 10;
                timeLimit += key;

                lcdDisplay.write(key, cursorTimeLimitPos + 11, 1);
                cursorTimeLimitPos++;
                if (timeLimit > 60) {
                    cursorTimeLimitPos = 0;
                    lcdDisplay.clearRowAfterCol(11, 1);
                    timeLimit = 0;
                }
            } else if (!isCaptureTimeSet) {
                captureFlagTime = key;
                lcdDisplay.write(key, 12, 1);
            }

        } else if (key == 14) {
            if (!isTimeLimitSet) {
                isTimeLimitSet = true;
                timeLimit *= 60;
                timeLeftRedTeam = timeLeftBlueTeam = timeLimit;

                lcdDisplay.clear();
                lcdDisplay.write("Tiempo captura", 0, 0);
                lcdDisplay.write("Segundos => 0s", 0, 1);

            } else if (!isCaptureTimeSet) {
                isCaptureTimeSet = true;isConfigured = true;
                status = GameStatus::MENU;
                showMenu();
            }
        }
    }

}

void Domination::updateInGameStatus(int key) {
    
    if (currentTeam == 0) { // No team set
        if (key == 100) currentTeam = -1;
        if (key == 101) currentTeam = 1;

        if (currentTeam != 0) {
            timer.start(1);
            showRemainingTimeText();
            showRemainingTime();
        }
    } else {

        // Red team button
        if (key == 100) {
            if (currentTeam == 1)
                showProgressBar(pinRedTeam);
        }

        // Blue team button
        if (key == 101) { // Blue to active?
            if (currentTeam == -1)
                showProgressBar(pinBlueTeam);
        }

        // Exit button
        if (key == 15) {
            exitGame++;

            if (exitGame == 3) {
                status = GameStatus::MENU;
                timeLeftRedTeam = timeLeftBlueTeam = timeLimit;
                showMenu();
                return;
            }
        }

        // Discount second
        int timeElapse = timer.getIntervalInSeconds();

        if (timeElapse >= 1) {
            if (currentTeam == -1) {
                timeLeftRedTeam--;
            } else {
                timeLeftBlueTeam--;
            }

            int remainigTime = currentTeam == -1 ? timeLeftRedTeam : timeLeftBlueTeam;
            if (remainigTime > 60) buzzer.beep();
            else buzzer.beepTree();

            showRemainingTime();
        }
    }
}

void Domination::checkAction() {

    char* currentMenu = menu[cursorPos];

    if (currentMenu == "Empezar" && isConfigured) {
        status = GameStatus::IN_GAME;
        timer.start(1);
        lcdDisplay.clear();
        lcdDisplay.write("Dominando", 0, 0);
        lcdDisplay.write("Nadie", 0, 1);
    }

    if (currentMenu == "Configurar") {
        status = GameStatus::CONFIG;
        isCaptureTimeSet = false;
        isTimeLimitSet = false;
        isConfigured = false;
        lcdDisplay.clear();
        lcdDisplay.write("Tiempo total", 0, 0);
        lcdDisplay.write("Minutos =>", 0, 1);
    }

    if (currentMenu == "Salir") {
        status = GameStatus::ENDED;
    }
}

void Domination::updateCursor(int update) {
    cursorPos = cursorPos + update;

    if (cursorPos == menuSize) {
        cursorPos = 0;
    }

    if (cursorPos == -1) {
        cursorPos = menuSize - 1;
    }
}

void Domination::showRemainingTimeText() {

    lcdDisplay.clear();

    char* teamName = currentTeam == -1 ? "Rojo" : "Azul";
    lcdDisplay.write("Equipo", 0, 0);
    lcdDisplay.write(teamName, 7, 0);
    lcdDisplay.write("Tiempo =>", 0, 1);
}

void Domination::showRemainingTime() {
    lcdDisplay.clearRowAfterCol(11, 1);

    int remainigTime = currentTeam == -1 ? timeLeftRedTeam : timeLeftBlueTeam;

    int min = remainigTime / 60;
    int sec = remainigTime % 60;

    lcdDisplay.write(min / 10, 11, 1);
    lcdDisplay.write(min % 10, 12, 1);
    lcdDisplay.write(":", 13, 1);
    lcdDisplay.write(sec / 10, 14, 1);
    lcdDisplay.write(sec % 10, 15, 1);
}

void Domination::endGame(bool team) {

    lcdDisplay.clear();
    lcdDisplay.write("Ganador", 0, 0);
    lcdDisplay.write("Equipo", 0, 1);

    char* winnerTeam = team ? "Rojo" : "Azul";
    for (int i = 0; i < 4; i++) {
        lcdDisplay.write(winnerTeam, 7, 1);
        delay(500);
        lcdDisplay.clearRowAfterCol(7, 1);
        delay(500);
    }

    status = GameStatus::MENU;
    timeLeftRedTeam = timeLeftBlueTeam = timeLimit;
    currentTeam = 0;
    showMenu();
}

void Domination::showProgressBar(int pin) {
    lcdDisplay.clear();
    lcdDisplay.write("Capturando ...", 0, 0);

    do {
        int timeElapse = timer_2.getIntervalInSeconds();

        if (timeElapse >= 1) {
            capturingFlag++;
            const int cols = lcdDisplay.getCols();
            int colsToPrint = (capturingFlag * cols) / captureFlagTime;
            for (int i = 0; i <= colsToPrint; i++) {
                lcdDisplay.printLoadBar(i, 1);
            }
        }
    } while (!digitalRead(pin) && capturingFlag <= captureFlagTime);

    if (capturingFlag >= captureFlagTime) {
        currentTeam = currentTeam == -1 ? 1 : -1;
    }

    capturingFlag = 0;

    showRemainingTimeText();
}
