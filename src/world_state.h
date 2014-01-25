// world_state.h 
// Terrance Howard (heyterrance@gmail.com)

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include <stdio.h> // printf
#include <vector> // std::vector
#include <utility> // std::pair

#include <SFML/System.hpp> // sf::Clock, sf::Keyboard
#include <SFML/Graphics.hpp> // sf::RenderWindow

#include "constants.h"
#include "resources.h"
#include "state.h"
#include "jack.h"
#include "room.h"

class WorldState : public GameState {
public:
	WorldState();
	~WorldState();

	// Inherited GameState Methods
	void update(float dt);
	void processKeyboard(float dt);
	void draw(sf::RenderWindow& window) const;

  // save()
  // Save relevant information to a file.
  // TODO: Implement save()
	void save();

private:
	// loadRoom()
	// Load specified room.
	void loadRoom(int index, bool load_adjacent=false);
	void loadRoom(int i, int j, bool load_adjacent=false);

	// loadAdjacent()
	// Load adjacent rooms.
	void loadAdjacent(int index);
	void loadAdjacent(int i, int j);

	// refresh()
	// Reload current room.
	void refresh();

  // moveJack()
  // Move Jack using the keyboard.
	void moveJack();

  // checkRoomBounds()
  // Transition to next room if necessary.
	void checkRoomBounds(float dt);

  // checkCollision()
  // Check and correct for collisions.
	void checkCollision(float dt);

private:
	Jack jack_;
	int room_idx_;
	std::vector<Room*> rooms_;
};

#endif
