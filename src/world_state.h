// world_state.h 
// Terrance Howard (heyterrance@gmail.com)

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <iostream> // std::cout
#include <stdio.h> // printf
#include <sstream>
#include <thread>
#include <chrono>

#include <SFML/System.hpp> // sf::Clock, sf::Keyboard
#include <SFML/Graphics.hpp> // sf::Font, sf::RenderWindow, sf::Text

#include "constants.h"
#include "resources.h"
#include "state.h"
#include "jack.h"
#include "room.h"

class WorldState : public GameState {
public:
	WorldState();
	~WorldState();

	// GameState Methods
	void update(float dt);
	void processKeyboard(float dt);
	void draw(sf::RenderWindow& window) const;

	void save();

private:
	// loadRoom()
	// load specified room
	void loadRoom(int index, bool load_adjacent=false);
	void loadRoom(int i, int j, bool load_adjacent=false);

	// loadAdjacent()
	// load adjacent rooms
	void loadAdjacent(int index);
	void loadAdjacent(int i, int j);

	// reloadRoom()
	// reload current room
	void reloadRoom();
	
	void moveJack();
	void checkRoomBounds(float dt);
	void checkCollision(float dt);

private:
	Jack jack_;
	int room_idx_;
	std::vector<Room*> rooms_;

};

#endif
