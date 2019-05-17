#ifndef TOWER_DEFENCE__MAINMENU_H
#define TOWER_DEFENCE__MAINMENU_H

#include "menu.h"

// Class for main menu
class MainMenu :public Menu
{

public:
	MenuResult Show(sf::RenderWindow& window);
	//MenuResult GetMenuResponse(sf::RenderWindow& window);
	//MenuResult HandleClick(int x, int y);
};

#endif


