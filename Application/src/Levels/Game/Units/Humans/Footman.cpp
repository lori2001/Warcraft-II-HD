#include "Footman.h"

void Footman::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
	
	for (int x = 0; x < 1920/32; x++)
	{
		for (int y = 0; y < 1080/32; y++)
		{
			target.draw(Tiles[x][y]);
		}
	}
	
}

void Footman::handleEvents(const sf::Event& event, const sf::Vector2f& mouse)
{
	cursorPosition_.x = static_cast<int>(ngin::Cursor::getPosition().x);
	cursorPosition_.y = static_cast<int>(ngin::Cursor::getPosition().y);

	if (event.mouseButton.button == sf::Mouse::Left)
	{
		shouldMove_ = true;
		for (int i = 0; i < 34; i++)
		{
			for (int j = 0; j < 60; j++)
			{
				if (cursorPosition_.x <= Tiles[i][j + 1].getPosition().x && cursorPosition_.x > Tiles[i][j].getPosition().x
					&& cursorPosition_.y >= Tiles[i][j].getPosition().y && cursorPosition_.y < Tiles[i + 1][j].getPosition().y)
				{
					cursorPosition_.x = i;
					cursorPosition_.y = j;
				}
			}
		}

		findPathTo({ cursorPosition_.x,cursorPosition_.y });

		for (size_t i = 0; i < tests.size(); i++)
		{
			Tiles[tests[i].x][tests[i].y].setFillColor(sf::Color::Red);
		}

		
		
		

		
		
	}

}

void Footman::animate(const float deltaTime)
{
	shape.setPosition({ static_cast<float>(position_.x * 32) ,
						static_cast<float>(position_.y * 32)});

	/*

	for (size_t i = 0; i < tests.size(); i++)
	{


		sf::Vector2f posForShape = shape.getPosition();
		sf::Vector2f posForTiles = Tiles[tests[i].x][tests[i].y].getPosition();




		if (posForShape.x < posForTiles.x)
		{
			shape.move(speed * deltaTime, 0);

			if (posForShape.y < posForTiles.y)
			{
				shape.move(0, speed * deltaTime);
			}

			if (posForShape.y > posForTiles.y)
			{
				shape.move(0, speed * -deltaTime);
			}

		}


		if (posForShape.x > posForTiles.x)
		{
			shape.move(speed * -deltaTime, 0);


			if (posForShape.y < posForTiles.y)
			{
				shape.move(0, speed * deltaTime);
			}

			if (posForShape.y > posForTiles.y)
			{
				shape.move(0, speed * -deltaTime);
			}


		}

		if (posForShape.y < posForTiles.y)
		{
			shape.move(0, speed * deltaTime);
		}
		if (posForShape.y > posForTiles.y)
		{
			shape.move(0, speed * -deltaTime);
		}


	}
	*/
}
		


	










		
	



	
	





