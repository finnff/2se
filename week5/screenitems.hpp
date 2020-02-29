#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>
#include <stack>
#include "enum.hpp"
#include "iostream"
#include <vector>

sf::Vector2f index2coord(int index)
{
    if (index > 5)
    {
        return sf::Vector2f((index - 6) * 200, 400);
    }
    else if (index > 2)
    {
        return sf::Vector2f((index - 3) * 200, 200);
    }
    else
    {
        return sf::Vector2f((index)*200, 0);
    }
};

class drawable
{
public:
    virtual void draw(sf::RenderWindow &w) = 0;
};

class gui_nought : public drawable
{
private:
    sf::Vector2f pos2f;
    sf::CircleShape inner;
    sf::CircleShape outer;

public:
    gui_nought(sf::Vector2f pos2f) : pos2f(pos2f + sf::Vector2f{45, 45}) {}
    void draw(sf::RenderWindow &w) override
    {
        inner.setFillColor(sf::Color::Black);
        outer.setFillColor(sf::Color::Red);
        inner.setPosition(pos2f + sf::Vector2f{10, 10});
        outer.setPosition(pos2f);
        inner.setRadius(50);
        outer.setRadius(60);
        w.draw(outer);
        w.draw(inner);
    }
};

class gui_cross : public drawable
{
private:
    sf::Vector2f pos2f;
    sf::RectangleShape partA;
    sf::RectangleShape partB;

public:
    gui_cross(sf::Vector2f pos2f) : pos2f(pos2f + sf::Vector2f{133, 67}) {}
    void draw(sf::RenderWindow &w) override
    {
        partA.setPosition(pos2f);
        partA.setSize(sf::Vector2f{10, 100});
        partA.setRotation(45);
        partA.setFillColor(sf::Color::Cyan);
        partB.setPosition(pos2f - sf::Vector2f{67, -7});
        partB.setSize(sf::Vector2f{10, 100});
        partB.setRotation(315);
        partB.setFillColor(sf::Color::Cyan);
        w.draw(partA);
        w.draw(partB);
    }
};

class gui_board : public drawable
{
private:
    sf::RectangleShape partA;
    sf::RectangleShape partB;
    sf::RectangleShape partC;
    sf::RectangleShape partD;

public:
    gui_board() {}
    void draw(sf::RenderWindow &w) override
    {
        partA.setPosition(sf::Vector2f{200, 0});
        partA.setSize(sf::Vector2f{5, 600});

        partB.setPosition(sf::Vector2f{400, 0});
        partB.setSize(sf::Vector2f{5, 600});

        partC.setPosition(sf::Vector2f{0, 200});
        partC.setSize(sf::Vector2f{600, 5});

        partD.setPosition(sf::Vector2f{0, 400});
        partD.setSize(sf::Vector2f{600, 5});

        w.draw(partA);
        w.draw(partB);
        w.draw(partC);
        w.draw(partD);
    }
};
void gui_handler(std::stack<std::pair<int, states>> stk, sf::RenderWindow &w)
{
    std::vector<drawable *> active; 
    w.clear();
    auto board = gui_board();

    
    while (!stk.empty())
    {
        auto current = stk.top();
        stk.pop();
        if (std::get<1>(current) == crosses)
        {
            active.push_back(new gui_cross(index2coord(std::get<0>(current))));
        }
        else if (std::get<1>(current) == noughts)
        {
            active.push_back(new gui_nought(index2coord(std::get<0>(current))));
        }
    };
    for(auto i :active){
        i->draw(w);
    }
    board.draw(w);
    w.display();
}