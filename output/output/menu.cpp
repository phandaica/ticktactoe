#include "menu.h"


/*Determine outcome based on mouse coordinate
Return: action on mouse click
*/
Menu::MenuResult Menu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++) // check if any mouse is in bound of any menu item
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (x > menuItemRect.left
			&& x < menuItemRect.left + menuItemRect.width
			&& y > menuItemRect.top
			&& y < menuItemRect.height + menuItemRect.top)
		{
			return (*it).action; //MenuItem.action
		}
	}

	return Nothing;
}



/*Return action based on window(input)*/
Menu::MenuResult Menu::GetMenuResponse(sf::RenderWindow& window) {
	sf::Event menuEvent;
	while (true) {
		while (window.pollEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				Menu::MenuResult clickResult = HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				if (clickResult != Nothing) return clickResult;

			}
			if (menuEvent.type == sf::Event::Closed) {
				return Exit;
			}
		}
	}
}
