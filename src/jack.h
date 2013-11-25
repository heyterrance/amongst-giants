// jack.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef JACK_H
#define JACK_H

#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "resources.h"

class Jack : public sf::Drawable {
public:
  float x,y;
  float dx, dy;
  float ddx, ddy;
  bool can_jump;
  bool in_air;

public:
  Jack(float x=0.0f, float y=0.0f);
  void update(float dt);

  std::pair< sf::Rect<float>, sf::Rect<float> > fakeUpdate(float dt) const;
  float width() const;
  float height() const;
  const sf::Rect<float>& bounds() const;

  unsigned int frame;
  float total_time;

private:
  std::vector< sf::IntRect > frames_;
  sf::Sprite sprite_;

  sf::Rect<float> bounds_;
  void animate(float dt);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
