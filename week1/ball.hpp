#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class rectangle {
private:
  sf::Vector2f position;
  float xdim;
  float ydim;

public:
  rectangle(sf::Vector2f position, float xdim, float ydim)
      : position(position), xdim(xdim), ydim(ydim) {}

	void draw(sf::RenderWindow &window) const;
	
};

class ball {
public:
  ball(sf::Vector2f position, float size = 30.0);

  void draw(sf::RenderWindow &window) const;

  void move(sf::Vector2f delta);

  void jump(sf::Vector2f target);
  void jump(sf::Vector2i target);

private:
  sf::Vector2f position;
  float size;
};

#endif