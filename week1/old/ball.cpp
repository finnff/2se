#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void rectangle::draw(sf::RenderWindow &window) const {
  auto size = sf::Vector2f(static_cast<float>(xdim), static_cast<float>(ydim));
  sf::RectangleShape recta;
  recta.setSize(size);
  recta.setPosition(position);
  recta.setFillColor(color);
  window.draw(recta);
}

sf::Vector2f rectangle::getPos() { return (position); }

void rectangle::move(sf::Vector2f delta) { position += delta; }

void rectangle::jump(sf::Vector2f target) { position = target; }

void rectangle::jump(sf::Vector2i target) {
  jump(
      sf::Vector2f(static_cast<float>(target.x), static_cast<float>(target.y)));
}

//####BALL ##### BALL #########BALL ##### BALL #########BALL ##### BALL
//#########BALL ##### BALL #####

ball::ball(sf::Vector2f position, float size)
    : position{position}, size{size} {}

void ball::draw(sf::RenderWindow &window) const {
  sf::CircleShape circle;
  circle.setRadius(size);
  circle.setPosition(position);
  window.draw(circle);
}

bool ball::collision() {
  if (true) {
    std::cout << "COLLISISIONNNN" << '\n';
    return true;
  }
}

// bool ball::intersects(const sf::FloatRect& other) {
//         return circle.getGlobalBounds().intersects(other);
//     }

void ball::move(sf::Vector2f delta) { position += delta; }

void ball::jump(sf::Vector2f target) { position = target; }

void ball::jump(sf::Vector2i target) {
  jump(
      sf::Vector2f(static_cast<float>(target.x), static_cast<float>(target.y)));
}
