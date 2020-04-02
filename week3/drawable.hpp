#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>

class drawable
{
public:
    drawable(sf::Vector2f position, sf::Color color) : position{position},
                                                       color{color}
    {
    }
    virtual void draw(sf::RenderWindow &window) {};

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
    //
    // virtual bool selected(sf::Vector2i mouseLocation) = 0;

    bool Selected = false;

    void writePosition(std::ostream &output) { output << "(" << position.x << "," << position.y << ") "; }

    virtual void writeType(std::ostream &output);
    virtual void writeColorPlus(std::ofstream &output);

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
    virtual void writeObjectSpecificStuff(std::ostream &output){};
    sf::Vector2f position;

//    virtual sf::FloatRect ggb();

protected:
    sf::Color color;
};