// intro_state.cpp
// Terrance Howard (heyterrance@gmail.com)

#include "intro_state.h"

IntroState::IntroState() : GameState(), time_(0.0f) {
  // arial_ = FontManager::getFont("arial bold");
  setupText();
  positionText();
  srand( static_cast<unsigned int>(time(NULL)) );
}

void IntroState::update(float dt) {
  time_ += dt;
  if (time_ >= 6.0f) {
    replaceWith(new WorldState());
  } else if (time_ >= 1.5f) {
    const uint8_t top = std::max(static_cast<uint8_t>(256.f - time_ * 42.0f),
                                 static_cast<uint8_t>(1));
    const uint8_t r = rand() % top;
    const uint8_t g = rand() % top;
    const uint8_t b = rand() % top;
    title_.setColor(sf::Color(r,g,b));
  }
}

void IntroState::draw(sf::RenderWindow& window) const {
  window.clear(sf::Color::Black);
  window.draw(title_);
}

void IntroState::setupText() {
  // title_.setFont(arial_);
  title_.setFont( FontManager::getFont("arial bold") );
  title_.setCharacterSize(92);
  title_.setColor(sf::Color(220, 220, 220));
  title_.setString("Amongst Giants");
}

void IntroState::positionText() {
  sf::FloatRect bounds = title_.getGlobalBounds();
  title_.setOrigin(bounds.width/2.0f, bounds.height/2.0f);
  title_.setPosition((float) WIN_WIDTH / 2.0f, (4.0f * WIN_HEIGHT) / 5.0f);
}
