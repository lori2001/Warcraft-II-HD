#pragma once
#include "SFML/Graphics.hpp"

class MainWindow : public sf::RenderWindow
{
private:
	static sf::Vector2u resolution;

	static sf::Vector2u scale1920;
	static sf::Vector2u scale1000;
public:
	void createWindow(sf::Vector2u resolution);
};

class Window
{

};