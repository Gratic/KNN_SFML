#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>
#include <algorithm>
class Dot : public sf::Drawable
{
private:
	sf::Vector2i position;
	std::string label;
	sf::Color color;
public:
	Dot();
	Dot(sf::Vector2i _position, std::string _label);

	static std::vector<std::string> getAllLabels(const std::vector<Dot>& _dots);
	static Dot findClosestDot(std::vector<Dot> _dots, int _x, int _y);
	static std::vector<Dot> findClosestDots(std::vector<Dot> _dots, int _x, int _y, int k);

	sf::Vector2i getPosition() const;
	void setPosition(sf::Vector2i _position);

	std::string getLabel() const;
	void setLabel(std::string _label);

	sf::Color getColor() const;
	void setColor(sf::Color _color);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::CircleShape shape(5.f);
        shape.setPosition(sf::Vector2f(getPosition().x, getPosition().y));

		shape.setFillColor(getColor());
		shape.setOutlineThickness(2.f);
		shape.setOutlineColor(sf::Color::Black);

        target.draw(shape);
    }

	friend bool operator== (const Dot& n1, const Dot& n2);
};

