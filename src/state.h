// state.cpp
// Terrance Howard (heyterrance@gmail.com)

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <stdio.h> // printf
#include <iostream> // std::cout
#include <stack> // std::stack

#include <SFML/System.hpp> // float
#include <SFML/Window.hpp> // sf::Event
#include <SFML/Graphics.hpp> // sf::RenderWindow

class StateManager;

// GameState
// Base class, defines a game state
class GameState {
public:
  GameState();

  virtual ~GameState();

  // update(dt)
  // Update scene
  // @param float dt - time since last call
  virtual void update(float dt) = 0;

  // draw(window)
  // @param RenderWindow window - window to draw to
  virtual void draw(sf::RenderWindow& window) const = 0;

  // save()
  // Save necessary information
  virtual void save() = 0;

  // Get and set StateManager
  void setManager(StateManager* manager);
  StateManager* manager() const;

protected:
  void push(GameState* state) const;
  void replaceWith(GameState* state) const;
  void pop() const;

private:
  StateManager* manager_;
};

class StateManager {
public:
  StateManager() : state_(nullptr), keep_state_(true) {}
  ~StateManager();

  void push(GameState* state);
  void replaceWith(GameState* state);
  void pop();
  void deleteState();

  void update(float dt);
  void draw(sf::RenderWindow& window) const;
  void close();

private:
  std::stack< GameState* > states_;
  GameState* state_;
  bool keep_state_;

};

#endif
