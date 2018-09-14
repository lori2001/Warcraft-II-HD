#include "Windows.h"

sf::Vector2i MainWindow::resolution;
sf::Vector2i MainWindow::res1920 = { 1920,1080 };

void MainWindow::onResize(sf::FloatRect & visibleArea)
{
	resolution.x = (int)visibleArea.width;
	resolution.y = (int)visibleArea.height;
}

void MainWindow::create(sf::VideoMode resolution, const std::string &name)
{
	sf::RenderWindow::create(resolution, name);
	this->resolution = sf::Vector2i(resolution.width, resolution.height);
}

int Window::index = 0;

void Window::create(sf::VideoMode resolution, const std::string & name)
{
	sf::RenderWindow::create(resolution, name);
	this->resolution = sf::Vector2i(resolution.width, resolution.height);
}
