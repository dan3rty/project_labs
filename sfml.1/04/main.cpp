#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void prepareShape(float x, float y, float width, float height, float rotation, sf::RectangleShape &shape)
{
    shape.setSize({width, height});
    shape.setRotation(rotation);
    shape.setPosition({x, y});
    shape.setFillColor(sf::Color(228, 35, 157));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle...");

    window.clear();

    sf::RectangleShape shape1;
    prepareShape(64, 465, 20, 232, -135, shape1);
    window.draw(shape1);

    sf::RectangleShape shape2;
    prepareShape(50, 150, 20, 300, 0, shape2);
    window.draw(shape2);

    sf::RectangleShape shape3;
    prepareShape(50, 150, 20, 232, -45, shape3);
    window.draw(shape3);

    sf::RectangleShape shape4;
    prepareShape(314, 465, 20, 232, -135, shape4);
    window.draw(shape4);

    sf::RectangleShape shape5;
    prepareShape(300, 150, 20, 300, 0, shape5);
    window.draw(shape5);

    sf::RectangleShape shape6;
    prepareShape(300, 150, 20, 232, -45, shape6);
    window.draw(shape6);

    sf::RectangleShape shape7;
    prepareShape(600, 150, 20, 300, 0, shape7);
    window.draw(shape7);

    window.display();

    sf::sleep(sf::seconds(5));
}