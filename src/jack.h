// jack.h
// Terrance Howard (heyterrance@gmail.com)

#ifndef JACK_H
#define JACK_H

#include <stdio.h> // printf
#include <utility> // std::pair, std::make_pair

#include <SFML/Graphics.hpp> // sf::Sprite, sf::Drawable, sf::RenderTarget,
                             // sf::RenderStates, sf::Rect, sf::IntRect

#include "resources.h" // TextureManager

class Jack : public sf::Drawable {
public:
  // Jack(x, y)
  // Instantiate a Jack with coordinates (x, y).
  Jack(float x=0.0f, float y=0.0f);
 
  // update(dt)
  // Set new position using velocity and acceleration.
  void update(float dt);

  // fakeUpdate(dt)
  // Return a pair of bounds, where the first is updated only in the
  // x-direction and second in the y-direction.
  std::pair< sf::Rect<float>, sf::Rect<float> > fakeUpdate(float dt) const;

  // width(), height()
  // Return width and height.
  float width() const;
  float height() const;

  // bounds()
  // Return the bounding box.
  const sf::Rect<float>& bounds() const;

public:
  float x,y;
  float dx, dy;
  float ddy;
  bool grounded;

private:
  // draw(target, states)
  // Draw sprite to the target.
  // Inherited from sf::Drawable.
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  // animate(dt)
  // Update sprite frame.
  void animate(float dt);

private:
  unsigned int frame_;
  float time_;

  sf::Rect<float> bounds_;

  std::vector< sf::IntRect > frames_;
  sf::Sprite sprite_;
};

#endif
