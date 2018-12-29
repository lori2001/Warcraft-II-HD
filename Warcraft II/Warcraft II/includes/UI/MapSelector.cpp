#include "MapSelector.h"

namespace UI
{
	void MapSelector::checkSelected(const sf::Vector2f & mouse)
	{
		//checks if the mouse and the right button intersect
		rightbutton.checkSelected(mouse);
		//checks if the mouse and the left button intersect
		leftbutton.checkSelected(mouse);
	}
	void MapSelector::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		//handle inputs for buttons
		rightbutton.handleInput(event, pressbutton);
		leftbutton.handleInput(event, pressbutton);

		//if right button is pressed
		if (rightbutton.getPressed())
			container.setTextureRect(sf::IntRect((int)containersize.x, 0, (int)containersize.x, (int)containersize.y)); //set visuals
		
		//if left button is pressed
		if (leftbutton.getPressed()) 
			container.setTextureRect(sf::IntRect((int)containersize.x * 2, 0, (int)containersize.x, (int)containersize.y)); //set visuals

		// if no buttons are pressed
		if (!rightbutton.getPressed() && !leftbutton.getPressed())
			container.setTextureRect(sf::IntRect(0, 0, (int)containersize.x, (int)containersize.y)); //reset visuals

	}
	void MapSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(container, states);

		target.draw(rightbutton, states);
		target.draw(leftbutton, states);

		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &(tilesT);

		// draw the vertex array
		target.draw(tilesV, states);

	}
	void MapSelector::setTexture(const sf::Texture & summertilesT, const sf::Texture & wastelandtilesT, const sf::Texture & wintertilesT, const sf::Texture & mapcontainerT)
	{
		this->summertilesT = summertilesT;
		this->wastelandtilesT = wastelandtilesT;
		this->wintertilesT = wintertilesT;

		container.setTexture(&mapcontainerT);
		container.setTextureRect(sf::IntRect(0, 0, int(containersize.x), int(containersize.y)));
	}
	void MapSelector::setTiles(const RW::MapReader &mapreader)
	{
		nroftiles = mapreader.getTilessize();

		if (mapreader.getTheme() == 0)
			tilesT = summertilesT;
		else if (mapreader.getTheme() == 1)
			tilesT = wastelandtilesT;
		else if (mapreader.getTheme() == 2)
			tilesT = wintertilesT;

		tilesV.setPrimitiveType(sf::Quads);
		tilesV.resize(nroftiles.x * nroftiles.y * 4);

		for (int y = 0; y < nroftiles.y; ++y)
		{
			for (int x = 0; x < nroftiles.x; ++x)
			{
				// get a pointer to the current tile'ssc quad
				sf::Vertex* quad = &(tilesV)[(x + y * nroftiles.x) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(float(x * (tilesize)), float(y * (tilesize)));
				quad[1].position = sf::Vector2f(float((x + 1) * (tilesize)), float(y * (tilesize)));
				quad[2].position = sf::Vector2f(float((x + 1) * (tilesize)), float((y + 1) * (tilesize)));
				quad[3].position = sf::Vector2f(float(x * (tilesize)), float((y + 1) * (tilesize)));

				int tu = mapreader.getTiles(x, y) % (tilesT.getSize().x / (tilesize));
				int tv = mapreader.getTiles(x, y) / (tilesT.getSize().x / (tilesize));

				quad[0].texCoords = sf::Vector2f(float(tu * ((tilesize) + 1)), float(tv * ((tilesize) + 1)));
				quad[1].texCoords = sf::Vector2f(float((tu) * ((tilesize) + 1) + (tilesize)), float(tv * ((tilesize) + 1)));
				quad[2].texCoords = sf::Vector2f(float((tu) * ((tilesize) + 1) + (tilesize)), float((tv) * ((tilesize)) + (tilesize)));
				quad[3].texCoords = sf::Vector2f(float(tu * ((tilesize) + 1)), float((tv) * ((tilesize) + 1) + (tilesize)));
			}
		}

		//center the map after the number of tiles
		Transformable::setOrigin(float(tilesize * nroftiles.x / 2), float(tilesize * nroftiles.y / 2));

		//calculating the scale of the minimap
		sf::Vector2f scale(minimapsize.x / (tilesize * nroftiles.x), minimapsize.y / (tilesize * nroftiles.y));

		//using the smaller scale for no deformation
		if (scale.x <= scale.y) {
			//actually setting the scale
			Transformable::setScale({ scale.x, scale.x });
		}
		else {
			//actually setting the scale
			Transformable::setScale({ scale.y, scale.y });
		}
	}
	void MapSelector::setPosition(sf::Vector2f position)
	{
		position.x = round(position.x);
		position.y = round(position.y);

		Transformable::setPosition(position);
		container.setPosition(position);
		leftbutton.setPosition({ container.getPosition().x - (containersize.x / 2 - buttonsize.x / 2), container.getPosition().y });
		rightbutton.setPosition({ container.getPosition().x + (containersize.x / 2 - buttonsize.x / 2), container.getPosition().y });
	}
}