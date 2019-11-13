#include "ball.hpp"
#include <SFML/Graphics.hpp>

ball::ball(sf::Vector2f position, float size)
    : position{position}, size{size} {}

void rectangle::draw(sf::RenderWindow &window) const {
  auto size  = sf::Vector2f(static_cast<float>(xdim), static_cast<float>(ydim));
	sf::RectangleShape recta;
	recta.setSize(size);
	recta.setPosition(position);
	window.draw(recta)

}

void ball::draw(sf::RenderWindow &window) const {
  sf::CircleShape circle;
  circle.setRadius(size);
  circle.setPosition(position);
  window.draw(circle);
}

void ball::move(sf::Vector2f delta) { position += delta; }

void ball::jump(sf::Vector2f target) { position = target; }

void ball::jump(sf::Vector2i target) {
  jump(
      sf::Vector2f(static_cast<float>(target.x), static_cast<float>(target.y)));
}
