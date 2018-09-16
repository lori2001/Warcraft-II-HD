#include "Window.h"

std::vector<int> Window::WindowNr;

void Window::create(sf::VideoMode resolution, const std::string & name)
{
	sf::RenderWindow::create(resolution, name);
	this->resolution = sf::Vector2i(resolution.width, resolution.height);
}

void Window::onResize(const sf::Vector2i & visibleArea)
{
	resolution.x = visibleArea.x;
	resolution.y = visibleArea.y;
}