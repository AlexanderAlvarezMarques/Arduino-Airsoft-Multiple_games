#ifndef BUZZER_H_INCLUDED
#define BUZZER_H_INCLUDED

#include "pitches.h"

class Buzzer {

private:

	const int buzzerPin;
	const static int defaultDuration = 100;

public:

	Buzzer(int _pin);

	void beep(int duration = defaultDuration);

	void beepTree(int duration = defaultDuration);

	void playAntiterroristWin();

	void playTerroristWin();

};

#endif