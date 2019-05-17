#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string > State;
State s = { "---",
			"---",
			"---" };
const int n = 3;

int restart = 0;

long tie1 = 0;

struct Move {
	int value;
	int i, j;
	char piece;
	Move(int value, int i, int j, char piece) {
		this->value = value;
		this->i = i;
		this->j = j;
		this->piece = piece;
	}
};


bool isMax = false;

void prints();



char Win();

void print_tie();

void print(State s)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << s[i][j] << " ";
		}
		cout << endl;
	}
}

bool isTerminal(const State& s)
{
	if (s[0][0] != '-' && s[0][1] != '-' && s[0][2] != '-' &&
		s[1][0] != '-' && s[1][1] != '-' && s[1][2] != '-' &&
		s[2][0] != '-' && s[2][1] != '-' && s[2][2] != '-') return true;
	if (s[0][0] != '-' && s[0][0] == s[1][1] && s[0][0] == s[2][2]) return true;
	if (s[0][2] != '-' && s[0][2] == s[1][1] && s[0][2] == s[2][0]) return true;
	for (int i = 0; i < n; i++) {
		if (s[i][0] != '-' && s[i][0] == s[i][1] && s[i][0] == s[i][2]) return true;
		if (s[0][i] != '-' && s[0][i] == s[1][i] && s[0][i] == s[2][i]) return true;
	}
	return false;
}

int utility(const State & s)
{
	static long long count = 0;
	count++;
	if (count % 1000000 == 0) {
		cout << "count = " << count << endl;
	}
	if (s[0][0] != '-' && s[0][0] == s[1][1] && s[0][0] == s[2][2]) {

		return s[0][0] == 'O' ? 1 : -1;
	}
	if (s[0][2] != '-' && s[0][2] == s[1][1] && s[0][2] == s[2][0]) {

		return s[0][2] == 'O' ? 1 : -1;
	}
	for (int i = 0; i < n; i++) {
		if (s[i][0] != '-' && s[i][0] == s[i][1] && s[i][0] == s[i][2]) {

			return s[i][0] == 'O' ? 1 : -1;
		}
		if (s[0][i] != '-' && s[0][i] == s[1][i] && s[0][i] == s[2][i]) {

			return s[0][i] == 'O' ? 1 : -1;;
		}
	}
	return 0;
}

Move min_value(State & s, int alpha, int beta);

Move max_value(State & s, int alpha, int beta)
{
	if (isTerminal(s)) return Move(utility(s), -1, -1, '-');
	Move v(-10, -1, -1, '-');
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i][j] == '-') {
				s[i][j] = 'O';
				Move m = min_value(s, alpha, beta);
				if (m.value > v.value)
					v = Move(m.value, i, j, 'O');
				s[i][j] = '-';
				if (m.value >= beta)
					return Move(m.value, i, j, 'O');
				alpha = max(alpha, m.value);
			}
		}
	}
	return v;
}

Move min_value(State & s, int alpha, int beta)
{
	if (isTerminal(s)) return Move(utility(s), -1, -1, '-');
	Move v = Move(10, -1, -1, '-');
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i][j] == '-') {
				s[i][j] = 'X';
				Move m = max_value(s, alpha, beta);
				if (m.value < v.value)
					v = Move(m.value, i, j, 'X');
				s[i][j] = '-';
				if (m.value <= alpha)
					return Move(m.value, i, j, 'X');
				beta = min(beta, m.value);
			}
		}
	}
	return v;
}

Move value(State & s, bool isMax = true)
{
	if (isMax) return max_value(s, -10, 10);
	else return min_value(s, -10, 10);
}


sf::Texture cell_texture;





sf::Sprite o_sprite;
sf::Sprite x_sprite;
sf::Sprite o_winning_sprite;
sf::Sprite x_winning_sprite;
sf::Sprite blank_sprite;

sf::RenderWindow window(sf::VideoMode(540, 960), "Tic - Tac - Toe", sf::Style::Close);




int main()
{
	//loading texture
	cell_texture.loadFromFile("sprite.png");

	//loading sprites
	o_sprite.setTexture(cell_texture);
	x_sprite.setTexture(cell_texture);
	o_winning_sprite.setTexture(cell_texture);
	x_winning_sprite.setTexture(cell_texture);
	blank_sprite.setTexture(cell_texture);
	o_sprite.setTextureRect(sf::IntRect(151, 0, 152, 150));
	x_sprite.setTextureRect(sf::IntRect(0, 0, 152, 150));
	o_winning_sprite.setTextureRect(sf::IntRect(605, 0, 151, 150));
	x_winning_sprite.setTextureRect(sf::IntRect(455, 0, 149, 150));
	blank_sprite.setTextureRect(sf::IntRect(303, 0, 152, 150));

	sf::Event event;





	while (window.isOpen())
	{
		prints();
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{

			case sf::Event::Closed:
				return 0;
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i localPosition = sf::Mouse::getPosition(window);


					int x = (localPosition.y - 260) / 150;
					int y = (localPosition.x - 35) / 150;
					string tmp;

					

					if (restart == 1) {
						restart = 0;
						tie1 = 0;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								s[i][j] = '-';
							}
						}
						cout << "Game is restarted" << endl;
						cout << endl;
						prints();
					}

					if (localPosition.y > 260 &&
						x < 3 && x >= 0 &&
						y < 3 && y >= 0 &&
						s[x][y] == '-' && restart == 0) {
						if (!isTerminal(s)) {
							Move v = value(s, isMax);

							if (!isMax) {
								tie1++;
								v.i = x;
								v.j = y;
								s[v.i][v.j] = 'X';
								print(s);
								cout << endl;
								prints();

							}
							if (Win() == 'X') {
								tie1 = 0;
								cout << "you win " << endl;
								prints();
								print(s);
								cout << endl;
								restart = 1;


							}
							if (tie1 == 9) {
								cout << "tie" << endl;
								print(s);
								prints();
								cout << endl;
								restart = 1;
							}
							if (restart != 1) {
								isMax = true;
								v = value(s, isMax);
								if (isMax) {
									tie1++;
									s[v.i][v.j] = v.piece;
									prints();
									print(s);
									cout << endl;
								}
								isMax = false;
								if (Win() == 'O') {
									tie1 = 0;
									cout << "you lose " << endl;
									prints();
									print(s);
									cout << endl;
									restart = 1;
									break;
								}
							}



						}
					}
				}
			}
		}
	}
}

char Win()
{
	int player1 = 0;
	//first player
	if (s[0][0] == 'X' && s[0][1] == 'X' && s[0][2] == 'X') {
		s[0][0] = 'W';
		s[0][1] = 'W';
		s[0][2] = 'W';
		player1 = 1;
	}
	if (s[1][0] == 'X' && s[1][1] == 'X' && s[1][2] == 'X') {
		s[1][0] = 'W';
		s[1][0] = 'W';
		s[1][0] = 'W';
		player1 = 1;
	}
	if (s[2][0] == 'X' && s[2][1] == 'X' && s[2][2] == 'X') {
		s[2][0] = 'W';
		s[2][1] = 'W';
		s[2][2] = 'W';
		player1 = 1;
	}
	if (s[0][0] == 'X' && s[1][0] == 'X' && s[2][0] == 'X') {
		s[0][0] = 'W';
		s[1][0] = 'W';
		s[2][0] = 'W';
		player1 = 1;
	}
	if (s[0][1] == 'X' && s[1][1] == 'X' && s[2][1] == 'X') {
		s[0][1] = 'W';
		s[1][1] = 'W';
		s[2][1] = 'W';
		player1 = 1;
	}
	if (s[0][2] == 'X' && s[1][2] == 'X' && s[2][2] == 'X') {
		s[0][2] = 'W';
		s[1][2] = 'W';
		s[2][2] = 'W';
		player1 = 1;
	}
	if (s[0][0] == 'X' && s[1][1] == 'X' && s[2][2] == 'X') {
		s[0][0] = 'W';
		s[1][1] = 'W';
		s[2][2] = 'W';
		player1 = 1;
	}
	if (s[2][0] == 'X' && s[1][1] == 'X' && s[0][2] == 'X') {
		s[2][0] = 'W';
		s[1][1] = 'W';
		s[0][2] = 'W';
		player1 = 1;
	}
	//computer
	if (s[0][0] == 'O' && s[0][1] == 'O' && s[0][2] == 'O') {
		s[0][0] = 'L';
		s[0][1] = 'L';
		s[0][2] = 'L';
		player1 = 2;
	}
	if (s[1][0] == 'O' && s[1][1] == 'O' && s[1][2] == 'O') {
		s[1][0] = 'L';
		s[1][1] = 'L';
		s[1][2] = 'L';
		player1 = 2;
	}
	if (s[2][0] == 'O' && s[2][1] == 'O' && s[2][2] == 'O') {
		s[2][0] = 'L';
		s[2][1] = 'L';
		s[2][2] = 'L';
		player1 = 2;
	}
	if (s[0][0] == 'O' && s[1][0] == 'O' && s[2][0] == 'O') {
		s[0][0] = 'L';
		s[1][0] = 'L';
		s[2][0] = 'L';
		player1 = 2;
	}
	if (s[0][1] == 'O' && s[1][1] == 'O' && s[2][1] == 'O') {
		s[0][1] = 'L';
		s[1][1] = 'L';
		s[2][1] = 'L';
		player1 = 2;
	}
	if (s[0][2] == 'O' && s[1][2] == 'O' && s[2][2] == 'O') {
		s[0][2] = 'L';
		s[1][2] = 'L';
		s[2][2] = 'L';
		player1 = 2;
	}
	if (s[0][0] == 'O' && s[1][1] == 'O' && s[2][2] == 'O') {
		s[0][0] = 'L';
		s[1][1] = 'L';
		s[2][2] = 'L';
		player1 = 2;
	}
	if (s[2][0] == 'O' && s[1][1] == 'O' && s[0][2] == 'O') {
		s[2][0] = 'L';
		s[1][1] = 'L';
		s[0][2] = 'L';
		player1 = 2;
	}

	if (player1 == 1) {
		return 'X';
	}
	else if (player1 == 2) return 'O';

}

void prints()
{
	sf::Font font;
	font.loadFromFile("JennaSue.ttf");
	sf::Text text2("You lose", font, 200);
	text2.setFillColor(sf::Color::Black);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(120.f, 0.f);
	sf::Text text1("You win", font, 200);
	text1.setFillColor(sf::Color::Black);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(120.f, 0.f);
	sf::Text text3("Tie", font, 200);
	text3.setFillColor(sf::Color::Black);
	text3.setStyle(sf::Text::Bold);
	text3.setPosition(230.f, 0.f);
	window.clear(sf::Color::Yellow);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			switch (s[i][j])
			{
			case '-':
				blank_sprite.setPosition(j * 150 + 10 * (j + 1) + 25, i * 150 + 10 * (i + 1) + 250);
				window.draw(blank_sprite);
				break;
			case 'O':

				o_sprite.setPosition(j * 150 + 10 * (j + 1) + 25, i * 150 + 10 * (i + 1) + 250);
				window.draw(o_sprite);
				break;
			case 'X':

				x_sprite.setPosition(j * 150 + 10 * (j + 1) + 25, i * 150 + 10 * (i + 1) + 250);
				window.draw(x_sprite);
				break;
			case 'L':
				o_winning_sprite.setPosition(j * 150 + 10 * (j + 1) + 25, i * 150 + 10 * (i + 1) + 250);

				window.draw(text2);

				window.draw(o_winning_sprite);
				break;
			case 'W':
				x_winning_sprite.setPosition(j * 150 + 10 * (j + 1) + 25, i * 150 + 10 * (i + 1) + 250);

				window.draw(x_winning_sprite);
				window.draw(text1);

				break;
			}
		}
	}
	if (tie1 == 9) {
		window.draw(text3);
	}

	window.display();
}

