#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int pin) : buzzerPin(pin){}

void Buzzer::beep(int duration = defaultDuration) {
	tone(buzzerPin, NOTE_B7, duration);
}

void Buzzer::beepTree(int duration = defaultDuration) {
	for (int i = 0; i < 3; i++) {
        beep();
        delay(100);
	}
}

void Buzzer::playAntiterroristWin() {

	int antiterroristWin[] = {
	  	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_E7, NOTE_REST, NOTE_A7, NOTE_REST,
    	NOTE_E7, NOTE_REST, NOTE_A7, NOTE_REST,
    	NOTE_E7, NOTE_REST, NOTE_A7, NOTE_REST,
    	NOTE_E7, NOTE_REST, NOTE_A7, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
    	NOTE_C6, NOTE_REST, NOTE_G6, NOTE_REST,
	};

	for (int i = 0; i < sizeof(antiterroristWin) / sizeof(antiterroristWin[0]); i++) {
	    if (antiterroristWin[i] == NOTE_REST) {
      		delay(defaultDuration);
	    } else {
	      	tone(buzzerPin, antiterroristWin[i], defaultDuration);
	      	delay(defaultDuration);
	    }
	    noTone(buzzerPin);
	}
}

void Buzzer::playTerroristWin() {

	int terroristWin[] = {
  		NOTE_B7, NOTE_E7, NOTE_G7, NOTE_B7, NOTE_REST,
	    NOTE_E7, NOTE_G7, NOTE_B7, NOTE_E7, NOTE_REST,
	    NOTE_G7, NOTE_B7, NOTE_E7, NOTE_G7, NOTE_REST,
	    NOTE_B7, NOTE_E7, NOTE_G7, NOTE_B7, NOTE_REST,
	    NOTE_B7, NOTE_E7, NOTE_G7, NOTE_B7, NOTE_REST,
	    NOTE_E7, NOTE_G7, NOTE_B7, NOTE_E7, NOTE_REST,
	    NOTE_G7, NOTE_B7, NOTE_E7, NOTE_G7, NOTE_REST,
	    NOTE_B7, NOTE_E7, NOTE_G7, NOTE_B7, NOTE_REST,
	    NOTE_B7, NOTE_D7, NOTE_F7, NOTE_A7, NOTE_REST,
	    NOTE_D7, NOTE_F7, NOTE_A7, NOTE_D7, NOTE_REST,
	    NOTE_F7, NOTE_A7, NOTE_D7, NOTE_F7, NOTE_REST,
	    NOTE_A7, NOTE_D7, NOTE_F7, NOTE_A7, NOTE_REST,
	};

	for (int i = 0; i < sizeof(terroristWin) / sizeof(terroristWin[0]); i++) {
	    if (terroristWin[i] == NOTE_REST) {
      		delay(defaultDuration);
	    } else {
	      	tone(buzzerPin, terroristWin[i], defaultDuration);
	      	delay(defaultDuration);
	    }
	    noTone(8);
	}
}
