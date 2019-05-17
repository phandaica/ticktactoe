#include "mainMenu.h"
#include "menu.h"


/* Descr: Displaying Main menu window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	// Load menu image from file
	sf::Texture image;
	//image.loadFromFile("src/images/menubackground.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	sf::Font font;
	font.loadFromFile("src/images/JennaSue.ttf");




	// "Start game menu" button coordinates
	MenuItem playButton;
	playButton.rect.top = 275;
	playButton.rect.height = 69;
	playButton.rect.left = 360;
	playButton.rect.width = 395;
	playButton.action = Play;

	sf::Text text2("Play", font, 50);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(515.f, 285.f);


	
	window.draw(sprite);

	window.display();

	return Menu::GetMenuResponse(window);
}

