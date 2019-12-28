#pragma once
#include "SFML/System.hpp"

// This file contains operations with sfml vectors
// which might shorten otherwise long code

namespace ngin {
	
	// converts floating point to an unidimensional vector
	sf::Vector2f ftoVec(const float floatingPoint);
	// converts integer to an unidimensional vector
	sf::Vector2i itoVec(const int integer);

	// multiplies two float vectors
	sf::Vector2f multiplyVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand);
	// multiplies two int vectors
	sf::Vector2i multiplyVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand);

	// divides float leftHand vector with rightHand vector
	sf::Vector2f divVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand);
	// divides int leftHand vector with rightHand vector
	sf::Vector2i divVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand);
	// divides float leftHand vector with rightHand float
	sf::Vector2f divVec(const sf::Vector2f& leftHand, const float rightHand);

	// adds up two float vectors
	sf::Vector2f addVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand);
	// adds up two int vectors
	sf::Vector2i addVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand);

	// substracts float rightHand vector from left hand vector
	sf::Vector2f subsVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand);
	// substracts int rightHand vector from left hand vector
	sf::Vector2i subsVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand);
}