#ifndef DOMINATION_H_INCLUDED
#define DOMINATION_H_INCLUDED

#include "GameInterface.h"
#include "../libs/LCD_Display.h"
#include "../libs/Timer.h"
#include "../libs/Buzzer.h"

class Domination : public GameInterface {

private:

	LCD_Display& lcdDisplay;
	Buzzer& buzzer;

	const int menuSize = 3;
    const char* menu[3] = {
        "Empezar",
        "Configurar",
        "Salir"
    };

    int pinRedTeam;
    int pinBlueTeam;
    int cursorPos = 0;
	
	int timeLimit;
	int timeLeftRedTeam;
	int timeLeftBlueTeam;
	int captureFlagTime;
	int capturingFlag;
	int currentTeam = 0; // 0 None, -1 Red, 1 Blue

	bool isConfigured = false;
	bool isTimeLimitSet = false;
	bool isCaptureTimeSet = false;
	int cursorTimeLimitPos = 0;

	int lastKeyPressed;

	GameStatus status;
	int exitGame = 0;

	Timer timer;
	Timer timer_2;

    void updateInMenuStatus(int key);
    
    void updateInConfigStatus(int key);
    
    void updateInGameStatus(int key);

    void checkAction();

    void updateCursor(int update);

    void showRemainingTimeText();

    void showRemainingTime(); // True red team, false blue team

    void showProgressBar(int pin);

    void endGame(bool team); // True red, false blue

public:

	Domination(LCD_Display& lcd, Buzzer& _buzzer, int _blueTeamPin, int _redTeamPin);

	const char* getName() override;

	void init() override;

	void showMenu() override;
    
    bool start() override;
    
    bool end() override;
    
    int updateStatus(int key) override;

    void showAttributesInSerialMonitor();

};

#endif