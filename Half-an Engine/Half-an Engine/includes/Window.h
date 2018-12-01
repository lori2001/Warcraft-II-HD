#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Window : public sf::RenderWindow
{
private:
	sf::Vector2i resolution;
	sf::Vector2i res1920{ 1920,1080 };

	static std::vector<int> WindowNr;
	int index = -1;
public:
	void create(sf::VideoMode resolution, const std::string &name);
	void create(sf::VideoMode resolution) {
		index = WindowNr.size();
		WindowNr.push_back(index);
		create(resolution, std::string("Window " + std::to_string(index)));
	}

	void close() {

		if(index != -1)
			WindowNr.erase(WindowNr.begin() + index);

		sf::RenderWindow::close();
	}

	void onResize(const sf::Vector2i &visibleArea);

	//getters
	sf::Vector2i getRes() { return resolution; }
	sf::Vector2f get1920Scale() { return sf::Vector2f(float(resolution.x) / res1920.x, float(resolution.y) / res1920.y); }

	//setters
	void setRes(sf::Vector2i resolution) { this->resolution = resolution; }
};