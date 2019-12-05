#include "Resources.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

  sf::RenderWindow window{sf::VideoMode{1280, 960}, "SFML window"};
  window.setFramerateLimit(60);

  bool stuck;
  ball my_ball{sf::Vector2f{320.0, 240.0}};
  my_ball.richting = sf::Vector2f{10, 10};
  rectangle my_rec{sf::Vector2f{120.0, 140.0}, sf::Vector2f{110, 110},
                   sf::Color::Red};

  rectangle topw{sf::Vector2f{0.0, 0.0}, sf::Vector2f{1280, 50},
                 sf::Color::Magenta};
  rectangle leftw{sf::Vector2f{0.0, 0.0}, sf::Vector2f{50, 960},
                  sf::Color::Green};
  rectangle bottomw{sf::Vector2f{0.0, 910.0}, sf::Vector2f{1280, 50},
                    sf::Color::Yellow};
  rectangle rightw{sf::Vector2f{1230.0, 0.0}, sf::Vector2f{50, 960},
                   sf::Color::Cyan};

  rectangle walllist[] = {topw, rightw, leftw, bottomw};

  action actions[] = {// LMAO =D=D=D=D=D=D=D=D=D=D=D=D=D
                      action(std::function<bool()>{[]() { return true; }},
                             [&]() { my_ball.move(my_ball.richting); }),

                      action(sf::Keyboard::W,
                             [&]() {
                               my_rec.move(sf::Vector2f(0.0, -10.0));
                               if (my_rec.getPos().y < 50) {
                                 my_rec.move(sf::Vector2f(0.0, +10.0));
                               }
                             }),

                      action(sf::Keyboard::S,
                             [&]() {
                               my_rec.move(sf::Vector2f(0.0, 10.0));
                               if (my_rec.getPos().y > 810) {
                                 my_rec.move(sf::Vector2f(0.0, -10.0));
                               }
                             }),

                      action(sf::Keyboard::A,
                             [&]() {
                               my_rec.move(sf::Vector2f(-10.0, 0.0));
                               if (my_rec.getPos().x < 50) {
                                 my_rec.move(sf::Vector2f(+10.0, 0.0));
                               }
                             }),

                      action(sf::Keyboard::D,
                             [&]() {
                               my_rec.move(sf::Vector2f(+10.0, 0.0));
                               if (my_rec.getPos().x > 1130) {
                                 my_rec.move(sf::Vector2f(-10.0, 0.0));
                               }
                             })

  };

  while (window.isOpen()) {
    for (auto &action : actions) {
      action();
    }

    window.clear();
    my_ball.draw(window);
    my_rec.draw(window);
    for (auto i : walllist) {
      i.draw(window);
    };
    window.display();

    if (!my_ball.intersects(my_rec.getGlobalBounds())) {
      stuck = false;
    }

    if (my_ball.intersects(my_rec.getGlobalBounds()) && stuck == false) {
      std::cout << "BING BONG " << '\n';
      if (abs(my_rec.getCenter().x - my_ball.Center().x) >=
          abs(my_rec.getCenter().y - my_ball.Center().y)) {
        my_ball.richting =
            sf::Vector2f{my_ball.richting.x * -1, my_ball.richting.y};
      }
      if (abs(my_rec.getCenter().x - my_ball.Center().x) <
          abs(my_rec.getCenter().y - my_ball.Center().y)) {
        my_ball.richting =
            sf::Vector2f{my_ball.richting.x, my_ball.richting.y * -1};
      }
      stuck = true;
    }

    if (my_ball.intersects(leftw.getGlobalBounds()) ||
        my_ball.intersects(rightw.getGlobalBounds())) {
      my_ball.richting =
          sf::Vector2f{my_ball.richting.x * -1, my_ball.richting.y};
    }

    if (my_ball.intersects(bottomw.getGlobalBounds()) ||
        my_ball.intersects(topw.getGlobalBounds())) {
      my_ball.richting =
          sf::Vector2f{my_ball.richting.x, my_ball.richting.y * -1};
    }

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  std::cout << "Terminating application\n";
  return 0;
}
