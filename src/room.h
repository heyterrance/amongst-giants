// room.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef ROOM_H
#define ROOM_H

#include <stdio.h> // printf
#include <algorithm> // std::min, std::max
#include <iostream> // std::cout
#include <fstream> // std::ifstream
#include <sstream> // std::istringstream

#include <SFML/Graphics.hpp> // sf::RenderWindow, sf::Drawable

#include "resources.h" // FontManager
#include "constants.h"
#include "util.h" // errprintf, dbprintf

#include "water.h" // Water

class Room : public sf::Drawable {
public:
	Room(int x, int y);
	~Room();

	static int getIndex(int i, int j);
	static std::pair<int, int> getPos(int index);

	// next(x, y)
	// @return -- index of adjacent room
	int next(int x, int y) const;

  void update(float dt);

	void load(const std::string& filename);
	void save() const;

public:
	const int x, y;
	const int index;

	static const int kRoomsX = 2;
	static const int kRoomsY = 2;
	static const int kRooms = kRoomsX * kRoomsY;

	// TODO Think of a way to represent depth/order of drawing
	std::vector<sf::Drawable*> drawables;

	std::vector< sf::Rect<float> > blocks;
  std::vector<Water> waters;

private:
	Room() : x(-1), y(-1), index(-1) { } // A room must have a location

  void addBlock(float left, float top, float width, float height,
								const sf::Color& color=sf::Color::Black);
	void buildBounds();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
