#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dot.h"
#include <vector>

const int WINDOW_LENGTH = 800;
const int WINDOW_HEIGHT = 600;

void setDotsColor(std::map <std::string, sf::Color>& _labelColors, std::vector<Dot>& _dots);
std::string dominantLabel(std::vector<Dot>& _dots);
std::vector<sf::Color> getColors();
std::map <std::string, sf::Color> generateLabelColor(std::vector<Dot> _dots);

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "KNN demonstration | Zaleks");
	sf::Event event;

	std::vector<Dot> dots;
	dots.push_back(Dot(sf::Vector2i(20, 20), "a"));
	dots.push_back(Dot(sf::Vector2i(400, 20), "b"));
	dots.push_back(Dot(sf::Vector2i(20, 400), "c"));
	dots.push_back(Dot(sf::Vector2i(40, 90), "a"));
	dots.push_back(Dot(sf::Vector2i(500, 400), "a"));
	dots.push_back(Dot(sf::Vector2i(400, 500), "b"));
	dots.push_back(Dot(sf::Vector2i(700, 450), "b"));
	dots.push_back(Dot(sf::Vector2i(650, 550), "c"));
	dots.push_back(Dot(sf::Vector2i(330, 205), "c"));
	dots.push_back(Dot(sf::Vector2i(100, 100), "c"));
	dots.push_back(Dot(sf::Vector2i(400, 400), "c"));

	std::map <std::string, sf::Color> labelColors = generateLabelColor(dots);

	setDotsColor(labelColors ,dots);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		for (int x(0); x < WINDOW_LENGTH; x++)
		{
			for (int y(0); y < WINDOW_HEIGHT; y++)
			{
				std::vector<Dot> closers = Dot::findClosestDots(dots, x, y, 1);
				std::string label = dominantLabel(closers);

				sf::RectangleShape pix;
				pix.setPosition(sf::Vector2f(x, y));
				pix.setSize(sf::Vector2f(1, 1));
				pix.setFillColor(labelColors[label]);
				window.draw(pix);
			}
			std::cout << x << std::endl;
		}

		

		for (int i(0); i < dots.size(); i++)
		{
			window.draw(dots[i]);
		}

		window.display();
	}

	return 0;
}

void setDotsColor(std::map <std::string, sf::Color>& _labelColors, std::vector<Dot>& _dots)
{
	for (int i(0); i < _dots.size(); i++)
	{
		_dots[i].setColor(_labelColors[_dots[i].getLabel()]);
	}
}

std::string dominantLabel(std::vector<Dot>& _dots)
{
	std::map<std::string, int> labelCount;
	for (auto& x : Dot::getAllLabels(_dots))
	{
		labelCount[x] = 0;
	}

	for (auto& x : _dots)
	{
		labelCount[x.getLabel()] ++;
	}

	std::string dominant;
	int maximum = 0;
	for (auto& x : labelCount)
	{
		if (x.second > maximum)
		{
			dominant = x.first;
			maximum = x.second;
		}
	}

	return dominant;
}

std::vector<sf::Color> getColors()
{
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color::White);
	colors.push_back(sf::Color::Yellow);

	return colors;
}

std::map <std::string, sf::Color> generateLabelColor(std::vector<Dot> _dots)
{
	std::vector<std::string> labels = Dot::getAllLabels(_dots);
	std::vector<sf::Color> colors = getColors();

	// Show all labels
	/*for (int i(0); i < labels.size(); i++)
	{
		std::cout << labels[i] << std::endl;
	}*/

	std::map <std::string, sf::Color> labelColors;
	for (int i(0); i < labels.size(); i++)
	{
		labelColors[labels[i]] = colors[i];
	}

	return labelColors;
}