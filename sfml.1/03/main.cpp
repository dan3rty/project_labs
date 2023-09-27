#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle...");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({200, 560});
    shape1.setRotation(0);
    shape1.setPosition({300, 20});
    shape1.setFillColor(sf::Color(128, 128, 128));
    window.draw(shape1);

    sf::CircleShape shape2(88);
    shape2.setPosition({312, 28});
    shape2.setFillColor(sf::Color(0, 255, 0));
    window.draw(shape2);

    sf::CircleShape shape3(88);
    shape3.setPosition({312, 213});
    shape3.setFillColor(sf::Color(255, 255, 0));
    window.draw(shape3);

    sf::CircleShape shape4(88);
    shape4.setPosition({312, 397});
    shape4.setFillColor(sf::Color(255, 0, 0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(10));
}