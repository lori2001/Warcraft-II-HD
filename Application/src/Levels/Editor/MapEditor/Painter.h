#pragma once
#include "NGin.h" 

// abstract class inherited by painters for aditional memory savings

class Painter : public ng::Level{
public:
	virtual void handleEvents(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual bool isFocused() const = 0;
	virtual int getChoosen() const = 0;
	virtual sf::IntRect getChoosenTextureRect() const = 0;
	virtual bool getChoosenHasChanged() const = 0;
};