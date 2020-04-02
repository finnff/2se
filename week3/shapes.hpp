#pragma once

#include "drawable.hpp"

class circle : public drawable
{
public:
    float rad;
    circle(sf::Vector2f position, float radius, sf::Color color = sf::Color::White) : drawable(position, color)
    {
        rad = radius;
    }

    void draw(sf::RenderWindow &window) override
    {
        sf::CircleShape circle;
        circle.setRadius(rad);
        circle.setPosition(position);
        if (Selected)
        {
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(-2);
        }
        circle.setFillColor(color);
        window.draw(circle);
    }

    void writeType(std::ostream &output) override { output << "CIRCLE "; }

    void writeColorPlus(std::ofstream &output) override
    {

        writeColor(output);
        output << rad << '\n';
    }

private:
};

class rectangle : public drawable
{
public:
    sf::Vector2f size;
    rectangle(sf::Vector2f position, sf::Vector2f pos2, sf::Color color = sf::Color::White) : drawable(position, color)
    {
        size = pos2;
    }

    void draw(sf::RenderWindow &window) override
    {
        sf::RectangleShape rectangle;
        rectangle.setPosition(position);
        rectangle.setSize(sf::Vector2f(size.x, size.y));
        rectangle.setFillColor(color);
        if (Selected)
        {
            rectangle.setOutlineColor(sf::Color::White);
            rectangle.setOutlineThickness(-2);
        }
        window.draw(rectangle);
    }
    void writeType(std::ostream &output) override { output << "RECTANGLE "; }

    void writeColorPlus(std::ofstream &output) override
    {
        writeColor(output);
        output << "(" << size.x << "," << size.y << ")\n";
    }
};

class line : public drawable
{
public:
    sf::Vector2f length;
    line(sf::Vector2f position, sf::Vector2f size, sf::Color color) : drawable{position, color}
    {
        length = size;
        lines = sf::VertexArray(sf::LinesStrip, 2);
        lines[0].position = position;
        lines[1].position = position + length;
        lines[0].color = color;
        lines[1].color = color;
    }

    void jump(sf::Vector2f target) override
    {
        position = target;
        lines[0].position = position;
        lines[1].position = position + length;
    }

    void draw(sf::RenderWindow &window) override
    {
        if(Selected){
        lines[0].color = sf::Color::Cyan;
        lines[1].color = sf::Color::Cyan;
        }else{lines[0].color = color;
        lines[1].color = color;}
        window.draw(lines);
    }


    void writeType(std::ostream &output) override { output << "LINE "; }

    void writeColorPlus(std::ofstream &output) override
    {
        writeColor(output);
        output << "(" << length.x << "," << length.y << ")\n";
    }

private:
    sf::Vector2f size;
    sf::VertexArray lines;
};

class picture : public drawable
{
public:
    picture(sf::Vector2f position, std::string filename) : drawable(position, sf::Color::White),
                                                           filename(filename)
    {
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(0.2, 0.2));
    }

    void draw(sf::RenderWindow &window) override
    {
        if (Selected)
        {
            sprite.setColor(sf::Color(250, 50, 20, 120));
        }
        else
        {
            sprite.setColor(sf::Color(128, 128, 128, 255));
        }
        window.draw(sprite);
    }

    bool contains(const sf::Vector2i &point)
    {
        sf::Rect<float> rect = sprite.getGlobalBounds();
        return point.x >= rect.left &&
               point.x <= rect.left + rect.width &&
               point.y >= rect.top + 40.0 &&
               point.y <= rect.top + rect.height + 40.0;
    }

    void jump(sf::Vector2f target) override
    {
        sf::Rect<float> rect = sprite.getGlobalBounds();
        position.x = target.x - rect.width / 2;
        position.y = target.y - rect.height / 2;
        sprite.setPosition(position);
    }
    void writeType(std::ostream &output) override { output << "PICTURE "; }

    void writeColorPlus(std::ofstream &output) override
    {
        output << filename << '\n';
    }

private:
    std::string filename;
    sf::Texture texture;
    sf::Sprite sprite;
};