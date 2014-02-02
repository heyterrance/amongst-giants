// water.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef WATER_H
#define WATER_H

#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "resources.h"

class Water : public sf::Drawable {
public:
  Water(float x=0.0f, float y=0.0f, float h=WIN_HEIGHT, float w=WIN_WIDTH);
  void update(float dt);

  const sf::Rect<float>& bounds() const;

public:
  float x,y;
  float height, width;

private:
  float total_time_;

  sf::Rect<float> bounds_;
  sf::RectangleShape image_;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
