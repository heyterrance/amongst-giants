#include "water.h"

Water::Water(float x, float y, float h, float w) :
    x(x), y(y), height(h), width(w),
    bounds_(x, y, w, h),
    image_(sf::Vector2f(width, height)) {
  image_.setFillColor(sf::Color::Blue);
}

void Water::update(float dt) {
  const float pi = 3.1415926535;
  y += 8 * cos(dt * pi);
  image_.setPosition(x,y);
}

const sf::Rect<float>& Water::bounds() const {
  return bounds_;
}

void Water::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(image_, states);
}
