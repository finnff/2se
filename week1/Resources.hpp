#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>


class action {
private:
  std::function<bool()> condition;
  std::function<void()> work;

public:
  action(std::function<bool()> condition, std::function<void()> work)
      : condition(condition), work(work) {}


  action(sf::Keyboard::Key key, std::function<void()> work)
      : condition([key]() -> bool { return sf::Keyboard::isKeyPressed(key); }),
        work(work) {}

  action(sf::Mouse::Button button, std::function<void()> work)
      : condition(
            [button]() -> bool { return sf::Mouse::isButtonPressed(button); }),
        work(work) {}

  void operator()() {
    if (condition()) {
      work();
    }
  }
};



class drawable {
public:
  void virtual draw(sf::RenderWindow &w) const;
};

class ball : public drawable {
private:
  sf::CircleShape circle;
  sf::Vector2f position;
  float size;

public:
  sf::Vector2f richting;
  ball(sf::Vector2f position, float size = 30.0) {
    circle.setPosition(position);
    circle.setRadius(size);
  };


  void draw(sf::RenderWindow &w) const override { w.draw(circle); }

  bool intersects(const sf::FloatRect &other) {
    return circle.getGlobalBounds().intersects(other);
  }

  void move(sf::Vector2f delta) { circle.move(delta); }
};

class rectangle : public drawable {
private:
  sf::RectangleShape recta;
  sf::Vector2f positionv2;

public:
  rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    positionv2 =  position;
    recta.setPosition(position);
    recta.setSize(size);
    recta.setFillColor(color);
  }

  void draw(sf::RenderWindow &w) const override { w.draw(recta); }

  void move(sf::Vector2f delta) { recta.move(delta); 
  positionv2 =  positionv2 + delta;}

  sf::Vector2f getPos() { return (positionv2); }

  sf::FloatRect getGlobalBounds() { return recta.getGlobalBounds(); }
};
