#include "MainView.h"

namespace Sections
{
	void MainView::readFile()
	{
		if (filereader.isMap()) {
			map.setTexture(loading.summertilesT, loading.wastelandtilesT, loading.wintertilesT);
			map.setTiles(mapreader);
		}
	}
	void MainView::setTransform(const sf::Vector2f & scale)
	{
		map.setScale(scale);
		map.setPosition(sf::Vector2f(0, 40 * scale.y));
	}
	void MainView::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(map, states);
	}
}