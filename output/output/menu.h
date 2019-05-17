#ifndef TOWER_DEFENCE__MENU_HH
#define TOWER_DEFENCE__MENU_HH

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include <list>
#include <stdio.h>
#include <iostream>
#include "ui.h"


class Menu {
public:
	/* types of response on clicking menu*/
	enum MenuResult { Play,Exit };
	struct MenuItem {
	public:
		sf::Rect<int> rect;
		MenuResult action; /* menu item has an action tied to it*/
	};
	virtual MenuResult Show(sf::RenderWindow& window) = 0;
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);

protected:
	std::list<MenuItem> _menuItems;
};


#endif
