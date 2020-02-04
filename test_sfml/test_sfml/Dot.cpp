#include "Dot.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <algorithm>

Dot::Dot() : position(sf::Vector2i(0, 0)), label("no label") {}

Dot::Dot(sf::Vector2i _position, std::string _label) : position(_position), label(_label) {}

std::vector<std::string> Dot::getAllLabels(const std::vector<Dot>& _dots)
{
	std::vector<std::string> labels;
	for (int i(0); i < _dots.size(); i++)
	{
		if (std::find(labels.begin(), labels.end(), _dots[i].label) != labels.end())
		{
			// nothing
		}
		else
		{
			labels.push_back(_dots[i].label);
		}
	}
	return labels;
}

Dot Dot::findClosestDot(std::vector<Dot> _dots, int _x, int _y)
{
	std::vector<double> distances;
	for (int i(0); i < _dots.size(); i++)
	{
		double x = ((double)_dots[i].getPosition().x - _x);
		double y = ((double)_dots[i].getPosition().y - _y);
		distances.push_back(x*x + y*y);
	}

	/*for (auto& x : distances)
	{
		std::cout << x << std::endl;
	}*/

	std::vector<double>::iterator result = std::min_element(distances.begin(), distances.end());
	int index = std::distance(distances.begin(), result);

	return _dots[index];
}

std::vector<Dot> Dot::findClosestDots(std::vector<Dot> _dots, int _x, int _y, int k)
{
	std::vector<Dot> closers;
	for (int i(0); i < k; i++)
	{
		closers.push_back(findClosestDot(_dots, _x, _y));
		std::vector<Dot>::iterator it = std::find(_dots.begin(), _dots.end(), closers[i]);
		int index = std::distance(_dots.begin(), it);
		_dots.erase(_dots.begin() + index);
	}

	/*for (auto& x : closers)
	{
		std::cout << x.label << std::endl;
	}
	std::cout << "-----" << std::endl;*/

	return closers;
}

sf::Vector2i Dot::getPosition() const
{
	return position;
}

void Dot::setPosition(sf::Vector2i _position)
{
	position = _position;
}

std::string Dot::getLabel() const
{
	return label;
}

void Dot::setLabel(std::string _label) 
{
	label = _label;
}

sf::Color Dot::getColor() const
{
	return color;
}

void Dot::setColor(sf::Color _color)
{
	color = _color;
}

bool operator== (const Dot& n1, const Dot& n2)
{
	return n1.getPosition().x == n2.getPosition().x
		&& n1.getPosition().y == n2.getPosition().y;
}