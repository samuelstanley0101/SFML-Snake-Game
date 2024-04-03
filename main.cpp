#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Coords.hpp"
#include "World.hpp"
#include "Tiles.hpp"
#include "Snake.hpp"
using namespace sf;
using std::cout;
using std::cin;
using std::endl;
using std::string;

const int TILESIZE = 30;
const int WORLDWIDTH = 20;
const int WORLDHEIGHT = 20;
const float TICKSPEED = 0.07;
const string windowName = "Snake";

int main()
{
	int number_of_players;
	//Player settings
	cout << "Welcome to Snake!" << endl;
	cout << "How many players do you want? Enter 1 or 2" << endl;
	cin >> number_of_players;
	if (number_of_players >= 2)
	{
		number_of_players = 2;
		cout << "Player 1, you are green. You use the WASD keys." << endl;
		cout << "Player 2, you are blue. You use the arrow keys." << endl;
		cout << "You may both use the shift key on your side to sprint, but watch out for your stamina." << endl;
	}
	else
	{
		number_of_players = 1;
		cout << "Use the WASD keys to control where you go." << endl;
		cout << "You may use the left shift key to sprint, but watch out for your stamina." << endl;
	}

	Clock clock;
	while (clock.getElapsedTime().asSeconds() < 5 && !Keyboard::isKeyPressed(Keyboard::Scan::Space));

	//Window and board settings
	VideoMode mode(TILESIZE * WORLDWIDTH, TILESIZE * WORLDHEIGHT);
	RenderWindow window(mode, windowName, Style::Default);
	window.setKeyRepeatEnabled(false);

	World world(WORLDWIDTH, WORLDHEIGHT, TILESIZE);
	vector<Snake> snakes;
	snakes.push_back(Snake(world.randomCoords(), Color(0, 150, 0), world));
	if (number_of_players == 2)
		snakes.push_back(Snake(world.randomCoords(), Color(0, 0, 150), world));

	

	clock.restart();
	int i = 0;
    while (window.isOpen() && snakes[0].alive && (number_of_players == 1 || snakes[1].alive))
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.scancode == Keyboard::Scan::W)
					snakes[0].direction = Coords::UP;
				else if (event.key.scancode == Keyboard::Scan::D)
					snakes[0].direction = Coords::RIGHT;
				else if (event.key.scancode == Keyboard::Scan::S)
					snakes[0].direction = Coords::DOWN;
				else if (event.key.scancode == Keyboard::Scan::A)
					snakes[0].direction = Coords::LEFT;

				if (number_of_players == 2)
				{
					if (event.key.scancode == Keyboard::Scan::Up)
						snakes[1].direction = Coords::UP;
					else if (event.key.scancode == Keyboard::Scan::Right)
						snakes[1].direction = Coords::RIGHT;
					else if (event.key.scancode == Keyboard::Scan::Down)
						snakes[1].direction = Coords::DOWN;
					else if (event.key.scancode == Keyboard::Scan::Left)
						snakes[1].direction = Coords::LEFT;
				}
			}
        }
		if (clock.getElapsedTime().asSeconds() > TICKSPEED)
		{
			if (Keyboard::isKeyPressed(Keyboard::Scan::LShift))
				snakes[0].sprint();
			snakes[0].manage_stamina();
			if (snakes[0].alive)
				snakes[0].alive = snakes[0].move();
			if (number_of_players == 2)
			{
				if (Keyboard::isKeyPressed(Keyboard::Scan::RShift))
					snakes[1].sprint();
				snakes[1].manage_stamina();
				if (snakes[1].alive)
					snakes[1].alive = snakes[1].move();
			}
			world.balance_apples();
			window.clear();
			for (int y = 0; y < WORLDHEIGHT; y++)
			{
				for (int x = 0; x < WORLDWIDTH; x++)
				{
					world.at(x, y)->draw(window);
				}
			}
			window.display();
			clock.restart();
		}
    }
	clock.restart();
	while (clock.getElapsedTime().asSeconds() < 1);

	if (number_of_players == 1)
	{
		cout << "GAME OVER!" << endl;
		cout << "Your final score was " << snakes[0].size() << endl;
	}
	else
	{
		cout << "GAME OVER!" << endl;
		if (!snakes[0].alive && !snakes[1].alive)
		{
			cout << "Nobody wins!" << endl;
		}
		else if (snakes[0].alive)
		{
			cout << "Player 1 wins!" << endl;
		}
		else if (snakes[1].alive)
		{
			cout << "Player 2 wins!" << endl;
		}
		cout << "Final Scores:" << endl;
		cout << "Player 1: " << snakes[0].size() << endl;
		cout << "Player 2: " << snakes[1].size() << endl;
	}


	window.close();

    return 0;
}