#include "water.h"

Water::Water(float x, float y, float h, float w) :
    x(x), y(y), height(h), width(w),
    bounds_(x, y, w, h),
    image_(sf::Vector2f(w, h)) {
  image_.setFillColor(sf::Color(150, 170, 220));
  image_.setPosition(x, y);
}

void Water::update(float dt) {
	const float amp = 10.0f * dt;
	const float period = 2.0f;
  const float pi = 3.1415926535f;
	total_time_ += dt;
  y += amp * cos(total_time_ * pi / period);
  image_.setPosition(x, y);
}

const sf::Rect<float>& Water::bounds() const {
  return bounds_;
}

void Water::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(image_, states);
}
