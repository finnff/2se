#pragma once

#include <SFML/Graphics.hpp>
#include <tuple>
#include <stack>
#include "enum.hpp"
#include "iostream"
#include <vector>

sf::Vector2f index2coord(int index) //class that tranlates postions on board to pixel coordinates.
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

class drawable // base drawable class.
{
public:
    virtual void draw(sf::RenderWindow &w) = 0;
};

class gui_nought : public drawable // nought shape, using two overlapping circles.
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

class gui_cross : public drawable // Cross shape using 2 intersecting Rectangles.
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
    void draw(sf::RenderWindow &w) override  // 4 lines intersect to create 9 boxes
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

class imagelogos : public drawable
{
    private:
    sf::Texture keybtext;
    sf::Texture undotext;
    sf::Sprite keyb;
    sf::Sprite undo;

    public:
    imagelogos(){
        if (!keybtext.loadFromFile("keyb.png"))
            std::cout<<"failed to load texture"<<'\n';
        if (!undotext.loadFromFile("undo.png"))
            std::cout<<"failed to load texture"<<'\n';
    }
    void draw(sf::RenderWindow &w){
        keyb.setTexture(keybtext);
        undo.setTexture(undotext);
        keyb.setPosition(sf::Vector2f{600,400});
        undo.setPosition(sf::Vector2f{600,0});
        undo.setScale(0.2,0.3);

        w.draw(undo);
        w.draw(keyb);
    }

};


void gui_handler(std::stack<std::pair<int, states>> stk, sf::RenderWindow &w)
// clear window and create a gui_board.
{
    std::vector<drawable *> active; 
    w.clear();
    auto board = gui_board();
    auto logos = imagelogos();


    while (!stk.empty()) //remove items from stack (newest move first),check if these are noughts or crosses and append these to a ptr vector.
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
    for(auto i :active){ //draw the noughts and crosses out of the ptr vector.
        i->draw(w);
    }
    logos.draw(w);
    board.draw(w);
    w.display();
}
