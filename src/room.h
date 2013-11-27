// room.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef ROOM_H
#define ROOM_H

#include <stdio.h> // printf
#include <algorithm> // std::min, std::max
#include <fstream> // std::ifstream
#include <sstream> // std::istringstream

#include <SFML/Graphics.hpp> // sf::RenderWindow, sf::Drawable

#include "resources.h" // FontManager
#include "constants.h"
#include "util.h" // dbprintf

class Room : public sf::Drawable {
public:
	const int x, y;
	const int index;

	static const int kRoomsX = 2;
	static const int kRoomsY = 2;
	static const int kRooms = kRoomsX * kRoomsY;

	// TODO Think of a way to represent depth/order of drawing
	std::vector<sf::Drawable*> drawables;

	std::vector< sf::Rect<float> > blocks;

public:
	Room(int x, int y);
	~Room();

	static int getIndex(int i, int j);
	static std::pair<int, int> getPos(int index);

	// next(x, y)
	// @return -- index of adjacent room
	int next(int x, int y) const;

	void load(const std::string& filename);
	void save() const;

private:
	Room() : x(-1), y(-1), index(-1) { } // A room must have a location
	
  void addBlock(float left, float top, float width, float height,
								const sf::Color& color=sf::Color::Black);
	void loadBlocks();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
