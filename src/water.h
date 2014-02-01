// water.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef WATER_H
#define WATER_H

#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "resources.h"

class Water : public sf::Drawable {
public:
  float x,y;
  float height, width;

public:
  Water(float x=0.0f, float y=0.0f);
  void update(float dt);

  const sf::Rect<float>& bounds() const;

  unsigned int frame;
  float total_time;

private:
  sf::Rect<float> bounds_;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
