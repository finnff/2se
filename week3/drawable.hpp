#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>

//base drawable class that different shapes will inherit methods from.
class drawable
{
public:
    drawable(sf::Vector2f position, sf::Color color) : position{position},
                                                       color{color}
    {
    }
    virtual void draw(sf::RenderWindow &window){};

    virtual void interact(drawable *other) {}

    virtual void jump(sf::Vector2f target)
    {
        position = target;
    }

    void jump(sf::Vector2i target)
    {
        jump(sf::Vector2f(
            static_cast<float>(target.x),
            static_cast<float>(target.y)));
    }
    bool Selected = false;
    //write functions that will write colour/type/position and other(radius/size/image) to text file
    void writePosition(std::ostream &output) { output << "(" << position.x << "," << position.y << ") "; }
    virtual void writeType(std::ostream &output);
    virtual void writeColorPlus(std::ofstream &output);
    // write color uses a struct to contain all availible colours objects can be.
    void writeColor(std::ostream &output)
    {
        const struct
        {
            const char *name;
            sf::Color color;
        } colors[]{
            {"yellow", sf::Color::Yellow},
            {"red", sf::Color::Red},
            {"green", sf::Color::Green},
            {"blue", sf::Color::Blue},
            {"black", sf::Color::Black},
            {"white", sf::Color::White},
        };
        for (auto const &colour : colors)
        {
            if (colour.color == color)
            {
                output << colour.name << " ";
            }
        }
    }
    sf::Vector2f position;

protected:
    sf::Color color;
};