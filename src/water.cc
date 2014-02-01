
Water::Water(float x=0.0f, float y=0.0f) : x(x), y(y) {
}

void Water::update(float dt) {
  const float pi = 3.1415926535;
  y += cos(dt * pi);
}

const sf::Rect<float>& Water::bounds() const {
  return bounds_;
}
