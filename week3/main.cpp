// @finff march2020

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stack>
#include <tuple>
#include "factory.hpp"
#include "shapes.hpp"
#include "exception.hpp"
#include "drawable.hpp"

template <typename TO, typename FROM> //nodig voor sf::Mouse::getPosition
sf::Vector2<TO> ConvertToVector2(const sf::Vector2<FROM> &other)
{
    return sf::Vector2<TO>(
        static_cast<TO>(other.x),
        static_cast<TO>(other.y));
};

int main()
{
    std::vector<std::unique_ptr<drawable>> drawables;
    std::ifstream input("list.txt");
    bool errorOccurred = false;
    try
    {
        for (;;)
        {
            drawables.push_back(screen_object_read(input));
        }
    }
    catch (end_of_file &)
    {
        // do nothing
    }
    catch (std::exception &error)
    {
        std::cerr << error.what();
        errorOccurred = true;
    }

    sf::RenderWindow window{sf::VideoMode{900, 600}, "SFML window"};

    while (window.isOpen())
    {
        for (auto &obj : drawables)
        {
            obj->Selected = true;
            while (true)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                {
                    obj->Selected = false;
                    sf::sleep(sf::milliseconds(100));
                    break;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2f currmpos = ConvertToVector2<float>(sf::Mouse::getPosition(window));
                    obj->jump(sf::Mouse::getPosition(window));
                    obj->Selected = false;
                    sf::sleep(sf::milliseconds(100));
                    break;
                }
                window.clear();
                for (auto &obj : drawables)
                {
                    obj->draw(window);
                }
                window.display();
            }
        }

        window.clear();
        for (auto &object : drawables)
        {
            object->draw(window);
        }
        window.display();

        sf::sleep(sf::milliseconds(100));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (!errorOccurred)
        {
            std::ofstream output("list.txt");
            for (auto &obj : drawables)
            {
                obj->writePosition(output);
                obj->writeType(output);
                obj->writeColorPlus(output);
            }
        }
    }
}