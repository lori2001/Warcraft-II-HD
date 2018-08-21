#include "MapSelector.h"

namespace UI
{
	void MapSelector::setSelected(const sf::Vector2f & mouse)
	{
		//checks if the mouse and the left button intersect
		*islSelected = (leftbutton->getPosition().x - this->buttonsize->x / 2 * leftbutton->getScale().x <= mouse.x &&
			leftbutton->getPosition().x + this->buttonsize->x / 2 * leftbutton->getScale().x >= mouse.x &&
			leftbutton->getPosition().y - this->buttonsize->y / 2 * leftbutton->getScale().y <= mouse.y &&
			leftbutton->getPosition().y + this->buttonsize->y / 2 * leftbutton->getScale().y >= mouse.y);

		*isrSelected = (rightbutton->getPosition().x - this->buttonsize->x / 2 * rightbutton->getScale().x <= mouse.x &&
			rightbutton->getPosition().x + this->buttonsize->x / 2 * rightbutton->getScale().x >= mouse.x &&
			rightbutton->getPosition().y - this->buttonsize->y / 2 * rightbutton->getScale().y <= mouse.y &&
			rightbutton->getPosition().y + this->buttonsize->y / 2 * rightbutton->getScale().y >= mouse.y);
	}
	void MapSelector::handleInput(const sf::Event & event, sf::Sound & pressbutton)
	{
		// if the mouse intersects with the  left button and leftmousebutton is enabled
		if (event.mouseButton.button == sf::Mouse::Left && *islSelected)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (pressbutton.getStatus() != sf::Music::Status::Playing) // play button sound
					pressbutton.play();

				//create the "pressed in" visual effect
				container->setTextureRect(sf::IntRect(2 * (int)containersize->x, 0, (int)containersize->x, (int)containersize->y));
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				//take action
				*islActive = true;
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Left && *isrSelected)
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (pressbutton.getStatus() != sf::Music::Status::Playing) // play button sound
					pressbutton.play();

				//create the "pressed in" visual effect
				container->setTextureRect(sf::IntRect((int)containersize->x, 0, (int)containersize->x, (int)containersize->y));
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				//take action
				*isrActive = true;
			}
		}

		// if the mouse looses touch with the button, or the mouse is released make the button inactive
		if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased || (!*islSelected && !*isrSelected))
		{
			container->setTextureRect(sf::IntRect(0, 0, (int)containersize->x, (int)containersize->y));
		}
	}
	void MapSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*container, states);

		if (*islSelected)
			target.draw(*leftbutton, states);
		else if (*isrSelected)
			target.draw(*rightbutton, states);

		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &(*tilesT);

		// draw the vertex array
		target.draw(*tilesV, states);

	}
	void MapSelector::setTexture(const sf::Texture & summertilesT, const sf::Texture & wastelandtilesT, const sf::Texture & wintertilesT, const sf::Texture & mapcontainerT)
	{
		*this->summertilesT = summertilesT;
		*this->wastelandtilesT = wastelandtilesT;
		*this->wintertilesT = wintertilesT;

		container->setTexture(&mapcontainerT);
		container->setTextureRect(sf::IntRect(0, 0, int(containersize->x), int(containersize->y)));
	}
	void MapSelector::setTiles(const RW::MapReader &mapreader)
	{
		*tilessize = mapreader.getTilessize();

		if (mapreader.getTheme() == 0)
			*tilesT = *summertilesT;
		else if (mapreader.getTheme() == 1)
			*tilesT = *wastelandtilesT;
		else if (mapreader.getTheme() == 2)
			*tilesT = *wintertilesT;

		tilesV->setPrimitiveType(sf::Quads);
		tilesV->resize(tilessize->x * tilessize->y * 4);

		for (int y = 0; y< tilessize->y; ++y)
		{
			for (int x = 0; x < tilessize->x; ++x)
			{
				// get a pointer to the current tile's quad
				sf::Vertex* quad = &(*tilesV)[(x + y * tilessize->x) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(float(x * (*tilesize)), float(y * (*tilesize)));
				quad[1].position = sf::Vector2f(float((x + 1) * (*tilesize)), float(y * (*tilesize)));
				quad[2].position = sf::Vector2f(float((x + 1) * (*tilesize)), float((y + 1) * (*tilesize)));
				quad[3].position = sf::Vector2f(float(x * (*tilesize)), float((y + 1) * (*tilesize)));

				int tu = mapreader.getTiles(x, y) % (tilesT->getSize().x / (*tilesize));
				int tv = mapreader.getTiles(x, y) / (tilesT->getSize().x / (*tilesize));

				quad[0].texCoords = sf::Vector2f(float(tu * ((*tilesize) + 1)), float(tv * ((*tilesize) + 1)));
				quad[1].texCoords = sf::Vector2f(float((tu) * ((*tilesize) + 1) + (*tilesize)), float(tv * ((*tilesize) + 1)));
				quad[2].texCoords = sf::Vector2f(float((tu) * ((*tilesize) + 1) + (*tilesize)), float((tv) * ((*tilesize)) + (*tilesize)));
				quad[3].texCoords = sf::Vector2f(float(tu * ((*tilesize) + 1)), float((tv) * ((*tilesize) + 1) + (*tilesize)));
			}
		}

		//center the map after the number of tiles
		Transformable::setOrigin(float(*tilesize * tilessize->x / 2), float(*tilesize * tilessize->y / 2));
	}
	void MapSelector::setScale(const sf::Vector2f &scale)
	{
		//saves scale for further use
		*this->scale = scale;

		float usedScale;

		//scales according to the bigger size
		if (tilessize->x >= tilessize->y)
			usedScale = (minimapsize->x * scale.x) / (tilessize->x * (*tilesize));
		else
			usedScale = (minimapsize->y * scale.y) / (tilessize->y * (*tilesize));

		//TODO: Get rid of black tripes inside the minimap
		float temp; // holds the part that needs to be cut
		float whole; // not really used (just for modf to work

		temp = usedScale * 10000; // separates the last two digits by the decimal (y.xxxxxx)=>(yyyyy.xx)
		temp = std::modf(temp, &whole); // gets rid of whole part
		temp /= 10000; //puts the las to decimals back to their original position

		usedScale -= temp;

		Transformable::setScale(usedScale, usedScale);
		container->setScale(scale);
		leftbutton->setScale(scale);
		rightbutton->setScale(scale);
	}
	void MapSelector::setPosition(const sf::Vector2f & position)
	{
		Transformable::setPosition(position);
		container->setPosition(position);
		leftbutton->setPosition(container->getPosition().x - (containersize->x / 2 - buttonsize->x / 2) * scale->x, container->getPosition().y);
		rightbutton->setPosition(container->getPosition().x + (containersize->x / 2 - buttonsize->x / 2) * scale->x, container->getPosition().y);
	}
}