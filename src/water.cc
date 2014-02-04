#include "water.h"

Water::Water(float x, float y, float h, float w) :
    x(x), y(y), y0(y), height(h), width(w),
    total_time_(0),
    bounds_(x, y, w, h),
    image_(sf::Vector2f(w, h)) {
  image_.setFillColor(sf::Color(150, 170, 220, 196));
  image_.setPosition(x, y);
}

void Water::update(float dt) {
	static const float amp = 10.0f;
	static const float period = 2.0f;
  static const float pi = 3.1415926535f;
	total_time_ += dt;
  static const float EPSILON = 0.1f;
  // Reset total_time_ after a full period
  if (fabs(total_time_ - 2.0f * period) < EPSILON)
    total_time_ = 0.0f;
  y = y0 + amp * cos(total_time_ * pi / period);
  image_.setPosition(x, y);
}

const sf::Rect<float>& Water::bounds() const {
  return bounds_;
}

void Water::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(image_, states);
}
