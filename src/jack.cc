// jack.cc
// Terrance Howard (heyterrance@gmail.com)

#include "jack.h"

Jack::Jack(float x, float y) : x(x), y(y), dx(0.0f), dy(0.0f), ddy(0.0f),
                               grounded(false), frame_(0u), time_(0.0f) {
  sprite_.setTexture( TextureManager::getTexture("jack-walk") );
  sprite_.setPosition(x, y);
  for (int i = 0; i < 6; ++i)
    frames_.push_back(sf::IntRect(12*i, 0, 12, 24));
  sprite_.setTextureRect(frames_[frame_]);
  bounds_.left = x;
  bounds_.top = y;
  bounds_.width = sprite_.getTextureRect().width;
  bounds_.height = sprite_.getTextureRect().height;
}

void Jack::update(float dt) {
  animate(dt);

  dy += ddy * 1.4f * dt;
  x += dx * dt;
  y += dy * dt;
  sprite_.setPosition(x, y);
  bounds_.left = x;
  bounds_.top = y;
  dx = 0.0f;
}

void Jack::animate(float dt) {
  const float f_time = 1.0f/6.0f;
  time_ += dt;
  if (time_ > f_time) {
    time_ = 0.0f;
    frame_ = (frame_ > 8) ? 0 : frame_ + 1;
  }

  if (not grounded or dx == 0.0f) {
    frame_ = 0;
    sprite_.setTextureRect(frames_[0]);
  } else  if (dx > 0.0f) {
    switch (frame_) {
      case 0:         sprite_.setTextureRect(frames_[1]); break;
      case 1: case 7: sprite_.setTextureRect(frames_[2]); break;
      case 2: case 6: sprite_.setTextureRect(frames_[3]); break;
      case 3: case 5: sprite_.setTextureRect(frames_[4]); break;
      case 4:         sprite_.setTextureRect(frames_[5]); break;
      default: break;
    }
  } else if (dx < 0.0f) {
    switch (frame_) {
      case 0:         sprite_.setTextureRect(frames_[5]); break;
      case 1: case 7: sprite_.setTextureRect(frames_[4]); break;
      case 2: case 6: sprite_.setTextureRect(frames_[3]); break;
      case 3: case 5: sprite_.setTextureRect(frames_[2]); break;
      case 4:         sprite_.setTextureRect(frames_[1]); break;
      default: break;
    }
  }
  
}

std::pair< sf::Rect<float>, sf::Rect<float> > Jack::fakeUpdate(float dt) const {
  const float f_dy = dy + 1.4 * ddy * dt;
  const float f_y = y + f_dy * dt;
  sf::Rect<float> x_bounds(bounds_), y_bounds(bounds_);
  x_bounds.left += dx * dt;
  y_bounds.top = f_y;
  return {x_bounds, y_bounds};
}

typedef std::pair< sf::Rect<float>, sf::Rect<float> > rectFloatPair;
rectFloatPair Jack::fakeUpdateY(float dt) const {
  const float f_dy = dy + 1.4 * ddy * dt;
  const float f_y = y + f_dy * dt;
  sf::Rect<float> x_bounds(bounds_), y_bounds(bounds_);
  y_bounds.top = f_y;
  return {x_bounds, y_bounds};
}

float Jack::width() const {
  return bounds_.width;
}

float Jack::height() const {
  return bounds_.height;
}

const sf::Rect<float>& Jack::bounds() const {
  return bounds_;
}

void Jack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}
