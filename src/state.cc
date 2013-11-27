// state.cpp
// Terrance Howard (heyterrance@gmail.com)

#include "state.h"

// =============================================================================
// GameState
// =============================================================================

GameState::GameState() : manager_(nullptr) {

}

GameState::~GameState() {
  dbprintf("~GameState()\n");
}

void GameState::push(GameState* state) const {
	if (manager_) manager_->push(state);
}

void GameState::replaceWith(GameState* state) const {
	if (manager_) manager_->replaceWith(state);
}

void GameState::pop() const {
	if (manager_) manager_->pop();
}

void GameState::setManager(StateManager* manager) {
  manager_ = manager;
}

StateManager* GameState::manager() const {
	return manager_;
}

// =============================================================================
// StateManager
// =============================================================================
  
StateManager::StateManager() : state_(nullptr), keep_state_(true) { }

StateManager::~StateManager() {
	while (state_) {
		state_->save();
		delete state_;
		states_.pop();
		state_ = states_.empty() ? nullptr : states_.top();
	}
}

void StateManager::push(GameState* state) {
  if (state) {
    state->setManager(this);
    states_.push(state);
    keep_state_ = true;
  }
}

void StateManager::replaceWith(GameState* state) {
  states_.pop();
  if (state) {
    state->setManager(this);
    states_.push(state);
    keep_state_ = false;
  }
}

void StateManager::pop() {
  states_.pop();
  keep_state_ = false;
}

void StateManager::update(float dt) {
	if (state_ != states_.top()) { // Pushed a new state
    if (!keep_state_) deleteState();
		state_ = states_.top();
		dt = 0.0f;
	}
	if(state_) state_->update(dt);
	else dbprintf(stderr, "Empty state stack!\n");
}

void StateManager::draw(sf::RenderWindow& window) const {
	if (state_) state_->draw(window);
}

void StateManager::deleteState() {
  if (state_) delete state_;
  keep_state_ = true;
  state_ = nullptr;
}
