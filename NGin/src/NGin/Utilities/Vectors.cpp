#include "Vectors.h"

namespace ngin {
	sf::Vector2f ftoVec(const float floatingPoint)
	{
		return { floatingPoint, floatingPoint };
	}
	sf::Vector2i itoVec(const int integer)
	{
		return { integer, integer };
	}
	sf::Vector2f multiplyVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand)
	{
		return { leftHand.x * rightHand.x, leftHand.y * rightHand.y };
	}
	sf::Vector2i multiplyVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand)
	{
		return { leftHand.x * rightHand.x, leftHand.y * rightHand.y };
	}
	sf::Vector2f divVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand)
	{
		return { leftHand.x / rightHand.x, leftHand.y / rightHand.y };
	}
	sf::Vector2i divVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand)
	{
		return { leftHand.x / rightHand.x, leftHand.y / rightHand.y };
	}
	sf::Vector2f divVec(const sf::Vector2f& leftHand, const float rightHand)
	{
		return { leftHand.x / rightHand, leftHand.y / rightHand };
	}
	sf::Vector2f addVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand)
	{
		return { leftHand.x + rightHand.x, leftHand.y + rightHand.y };
	}
	sf::Vector2i addVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand)
	{
		return { leftHand.x + rightHand.x, leftHand.y + rightHand.y };
	}
	sf::Vector2f subsVec(const sf::Vector2f& leftHand, const sf::Vector2f& rightHand)
	{
		return { leftHand.x - rightHand.x, leftHand.y - rightHand.y };
	}
	sf::Vector2i subsVec(const sf::Vector2i& leftHand, const sf::Vector2i& rightHand)
	{
		return { leftHand.x - rightHand.x, leftHand.y - rightHand.y };
	}
}