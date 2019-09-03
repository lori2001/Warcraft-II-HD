#pragma once

// Contains pathfinding algorithm intended for RTS Games
// File Contains refactored code from:
// Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu> -> AStar project licensed under ISC

#include "SFML/System.hpp"
#include <vector>
#include <functional>
#include <set>

namespace ngin {
	namespace AStar
	{
		using uint = unsigned int;
		using HeuristicFunction = std::function<uint(sf::Vector2i, sf::Vector2i)>;
		using CoordinateList = std::vector<sf::Vector2i>;

		struct Node
		{
			uint G, H;
			sf::Vector2i coordinates;
			Node* parent;

			Node(sf::Vector2i coord_, Node* parent_ = nullptr);
			uint getScore();
		};

		using NodeSet = std::set<Node*>;

		class Generator
		{
			bool detectCollision(sf::Vector2i coordinates_);
			Node* findNodeOnList(NodeSet& nodes_, sf::Vector2i coordinates_);
			void releaseNodes(NodeSet& nodes_);

		public:
			Generator();
			void setWorldSize(sf::Vector2i worldSize_);
			void setDiagonalMovement(bool enable_);
			void setHeuristic(HeuristicFunction heuristic_);
			CoordinateList findPath(sf::Vector2i source_, sf::Vector2i target_);
			void addCollision(sf::Vector2i coordinates_);
			void removeCollision(sf::Vector2i coordinates_);
			void clearCollisions();

		private:
			HeuristicFunction heuristic;
			CoordinateList direction, walls;
			sf::Vector2i worldSize;
			uint directions;
		};

		class Heuristic
		{
			static sf::Vector2i getDelta(sf::Vector2i source_, sf::Vector2i target_);

		public:
			static uint manhattan(sf::Vector2i source_, sf::Vector2i target_);
			static uint euclidean(sf::Vector2i source_, sf::Vector2i target_);
			static uint octagonal(sf::Vector2i source_, sf::Vector2i target_);
		};
	}
}