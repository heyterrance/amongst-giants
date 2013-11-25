// battle_state.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef BATTLE_STATE_H
#define BATTLE_STATE_H

#include <SFML/System.hpp> // sf::Clock, sf::Keyboard
#include <SFML/Graphics.hpp> // sf::Font, sf::RenderWindow, sf::Text

#include "constants.h"
#include "resources.h"
#include "state.h"

class BattleState : public GameState {
public:
  BattleState();
  ~BattleState();

  // GameState Methods
  void update(float dt);
  void processKeyboard(float dt);
  void draw(sf::RenderWindow& window) const;

  void save();

private:
    
};

#endif
