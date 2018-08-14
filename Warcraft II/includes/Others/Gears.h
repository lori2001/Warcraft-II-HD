#pragma once
#include "SFML\Graphics.hpp"
#include "..\RW\Loading.h"

class Gears : public sf::Drawable
{
private:
	const short *SIZE = new const short{ 20 }; // the number of frames
	const float *SPF = new const float{ 0.1f }; // Seconds for each frame (the framerate of the gears' animation)

	RW::Loading loading;

	sf::Sprite *topgearsS = new sf::Sprite;
	sf::Sprite *botgearsS = new sf::Sprite;

	sf::Clock *clock = new sf::Clock;

	unsigned short *curr = new unsigned short{ 0 }; //current frame to display

	const int *topdim = new const int{ 700 };
	const int *botdim = new const int{ 520 };
public:
	Gears()
	{
		topgearsS->setTexture(loading.topgearsT[*curr]);
		botgearsS->setTexture(loading.botgearsT[*curr]);
		botgearsS->setOrigin(sf::Vector2f(float(*botdim), float(*botdim)));
	}
	~Gears()
	{
		delete SIZE;
		delete SPF;
		delete topgearsS;
		delete botgearsS;
		delete clock;
		delete curr;
		delete topdim;
		delete botdim;
	}

	void setTopPosition(const sf::Vector2f & position);
	void setBotPosition(const sf::Vector2f & position);
	void setTopScale(const sf::Vector2f & scale);
	void setBotScale(const sf::Vector2f & scale);

	void animate();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
