#ifndef DOMINATION_H_INCLUDED
#define DOMINATION_H_INCLUDED

#include "GameInterface.h"
#include "../libs/LCD_Display.h"

class Domination : public GameInterface {

private:

	LCD_Display& lcdDisplay;
	int maxTime;

public:

	Domination(LCD_Display& lcd);

	const char* getName() override;

	void init() override;

	void showMenu() override;
    
    bool start() override;
    
    bool end() override;
    
    int updateStatus(int key) override;

    void showAttributesInSerialMonitor() override;

};

#endif