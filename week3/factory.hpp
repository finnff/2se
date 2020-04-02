#pragma once

#include <fstream>
#include <iostream>
#include "exception.hpp"
#include <memory>
#include "shapes.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

std::ifstream &operator>>(std::ifstream &input, sf::Color &rhs)
{
    std::string s;
    input >> s;
    const struct
    {
        std::string name;
        sf::Color color;
    } colors[]{
        {"yellow", sf::Color::Yellow},
        {"red", sf::Color::Red},
        {"green", sf::Color::Green},
        {"blue", sf::Color::Blue},
        {"black", sf::Color::Black},
        {"white", sf::Color::White}};
    for (auto const &color : colors)
    {
        if (color.name == s)
        {
            rhs = color.color;
            return input;
        }
    }
    if (s == "")
    {
        throw end_of_file();
    }
    throw unknown_color(s);
}

std::ifstream &operator>>(std::ifstream &input, sf::Vector2f &rhs)
{
    char c;
    if (!(input >> c))
    {
        throw end_of_file();
    }
    if (c != '(')
    {
        throw invalid_position(c);
    }
    if (!(input >> rhs.x))
    {
        throw end_of_file();
    }
    if (!(input >> c))
    {
        throw end_of_file();
    }
    if (!(input >> rhs.y))
    {
        throw end_of_file();
    }
    if (!(input >> c))
    {
        throw end_of_file();
    }
    if (c != ')')
    {
        throw invalid_position(c);
    }
    return input;
}

std::unique_ptr<drawable> screen_object_read(std::ifstream &input)
{
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
    std::string name;
    std::string filename;
    float radius;
    input >> position >> name;
    std::cout << "Processing Name:   " << name << '\n';
    if (name == "circle")
    {
        input >> color >> radius;
        // std::cout << "rad1:   " << radius << std::endl;
        return std::make_unique<circle>(position, radius, color);
    }
    else if (name == "rectangle")
    {
        input >> color >> size;
        return std::make_unique<rectangle>(position, size, color);
    }
    else if (name == "picture")
    {
        input >> filename;
        return std::make_unique<picture>(position, filename);
    }
    else if (name == "line")
    {
        input >> color >> size;
        return std::make_unique<line>(position, size, color);
    }
    else if (name == "\0")
    {
        std::cout << "EOF" << '\n';
        throw end_of_file();
    }

    throw std::invalid_argument("unknown Shape");
}