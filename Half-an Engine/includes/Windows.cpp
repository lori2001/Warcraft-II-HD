#include "Windows.h"

sf::Vector2i MainWindow::resolution;
sf::Vector2i MainWindow::res1920 = { 1920,1080 };

void MainWindow::onResize(sf::FloatRect & visibleArea)
{
	resolution.x = (int)visibleArea.width;
	resolution.y = (int)visibleArea.height;
}

void MainWindow::createWindow(sf::VideoMode resolution)
{
	//sf::VideoMode temp = sf::VideoMode(resolution.x ,resolution.y);
	sf::RenderWindow::create(resolution, "Half-an Engine");
	this->resolution = sf::Vector2i(resolution.width, resolution.height);
}
