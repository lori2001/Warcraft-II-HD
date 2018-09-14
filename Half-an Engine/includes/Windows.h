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
	void createWindow(sf::VideoMode resolution);

	//getters
	static sf::Vector2i getRes() { return resolution; }
	static sf::Vector2f get1920Scale() { return sf::Vector2f(float(resolution.x) / res1920.x, float(resolution.y) / res1920.y); }
};

class Window
{

};