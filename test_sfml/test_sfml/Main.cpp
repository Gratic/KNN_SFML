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

/*
* Name : setDotsColor
* Param1 : Dictionnary of label, color
* Param2 : Vector of Dot
* Description : Affect a color to each dot based on the dot's label.
*/
void setDotsColor(std::map <std::string, sf::Color>& _labelColors, std::vector<Dot>& _dots)
{
	for (int i(0); i < _dots.size(); i++)
	{
		_dots[i].setColor(_labelColors[_dots[i].getLabel()]);
	}
}

/*
* Name : dominantLabel
* Param1 : Vector of Dot
* Description : Return the label of the dominant label (most present one).
* Return : string
*/
std::string dominantLabel(std::vector<Dot>& _dots)
{
	// Initialization of the dictionnary
	std::map<std::string, int> labelCount;
	for (auto& x : Dot::getAllLabels(_dots))
	{
		labelCount[x] = 0;
	}

	// Counting
	for (auto& x : _dots)
	{
		labelCount[x.getLabel()] ++;
	}
	
	// Retrieving the dominant
	std::string dominant;
	int maximum = 0;
	for (auto& x : labelCount)
	{
		// Simple max function
		if (x.second > maximum)
		{
			dominant = x.first;
			maximum = x.second;
		}
	}

	return dominant;
}

/*
* Name : getColors
* Description : Return a vector of colors.
* Return : Vector of color
*/
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

/*
* Name : generateLabelColor
* Param1 : Vector of Dot
* Description : Generate a dictionnary of label and color.
* Return : Dictionnary of label and color.
*/
std::map <std::string, sf::Color> generateLabelColor(std::vector<Dot> _dots)
{
	// Retrieve all different labels
	std::vector<std::string> labels = Dot::getAllLabels(_dots);
	std::vector<sf::Color> colors = getColors();

	// Show all labels
	/*for (int i(0); i < labels.size(); i++)
	{
		std::cout << labels[i] << std::endl;
	}*/
	
	// Affect each label a color
	std::map <std::string, sf::Color> labelColors;
	for (int i(0); i < labels.size(); i++)
	{
		labelColors[labels[i]] = colors[i];
	}

	return labelColors;
}
