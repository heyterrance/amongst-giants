// intro_state.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include <stdio.h> // printf
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <sstream>

#include <SFML/System.hpp> // sf::Clock
#include <SFML/Graphics.hpp> // sf::Font, sf::RenderWindow, sf::Text

#include "constants.h"
#include "resources.h"
#include "state.h"
#include "world_state.h"

class IntroState : public GameState {
public:
  IntroState();
 
  // GameState methods
  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  
  void save() { printf("Saving...\n"); }

private:
  sf::Text title_;
  float time_;

  void setupText();
  void positionText();
};

#endif
