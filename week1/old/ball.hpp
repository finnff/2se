#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class rectangle {
private:
  sf::Vector2f position;
  float xdim;
  float ydim;
  sf::Color color;
  bool isIntersect;

public:
  rectangle(sf::Vector2f position, float xdim, float ydim, sf::Color color)
      : position(position), xdim(xdim), ydim(ydim), color(color) {}

  void draw(sf::RenderWindow &window) const;

  void move(sf::Vector2f delta);

  void jump(sf::Vector2f target);
  void jump(sf::Vector2i target);

  sf::Vector2f getPos();
};

class ball {
public:
  ball(sf::Vector2f position, float size = 30.0);

  void draw(sf::RenderWindow &window) const;

  void move(sf::Vector2f delta);

  void jump(sf::Vector2f target);
  void jump(sf::Vector2i target);
  bool collision();
  bool intersects(const sf::FloatRect& other);

private:
  sf::Vector2f position;
  float size;
};

#endif