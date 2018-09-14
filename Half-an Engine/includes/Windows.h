#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class MainWindow : public sf::RenderWindow
{
private:
	static sf::Vector2i resolution;
	static sf::Vector2i res1920;

public:
	static void onResize(sf::FloatRect &visibleArea);
	void create(sf::VideoMode resolution, const std::string &name);

	//getters
	static sf::Vector2i getRes() { return resolution; }
	static sf::Vector2f get1920Scale() { return sf::Vector2f(float(resolution.x) / res1920.x, float(resolution.y) / res1920.y); }
};

class Window : public sf::RenderWindow
{
private:
	sf::Vector2i resolution;
	sf::Vector2i res1920;

	static std::vector<int> WindowNr;
	int index = 0;
public:
	void create(sf::VideoMode resolution, const std::string &name);
	void create(sf::VideoMode resolution) {
		index = WindowNr.size();
		WindowNr.push_back(index);
		create(resolution, std::string("Window " + std::to_string(index)));
	}

	void close() {
		WindowNr.erase(WindowNr.begin() + index);
		sf::RenderWindow::close();
	}

	//getters
	sf::Vector2i getRes() { return resolution; }
	sf::Vector2f get1920Scale() { return sf::Vector2f(float(resolution.x) / res1920.x, float(resolution.y) / res1920.y); }

	//setters
	void setRes(sf::Vector2i resolution) { this->resolution = resolution; }
};