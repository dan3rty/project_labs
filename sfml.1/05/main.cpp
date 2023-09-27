#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangles and circle...");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({500, 300});
    shape1.setRotation(0);
    shape1.setPosition({150, 250});
    shape1.setFillColor(sf::Color(43, 29, 20));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({100, 220});
    shape2.setRotation(0);
    shape2.setPosition({180, 330});
    shape2.setFillColor(sf::Color(16, 16, 16));
    window.draw(shape2);

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(128, 0, 0));
    trapeze.setPosition(250, 190);
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-50, -50});
    trapeze.setPoint(1, {350, -50});
    trapeze.setPoint(2, {450, 110});
    trapeze.setPoint(3, {-150, 110});
    window.draw(trapeze);

    sf::RectangleShape shape3;
    shape3.setSize({40, 80});
    shape3.setRotation(0);
    shape3.setPosition({500, 130});
    shape3.setFillColor(sf::Color(58, 58, 58));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({70, 40});
    shape4.setRotation(0);
    shape4.setPosition({485, 110});
    shape4.setFillColor(sf::Color(58, 58, 58));
    window.draw(shape4);

    sf::CircleShape shape5(10);
    shape5.setPosition({510, 90});
    shape5.setFillColor(sf::Color(150, 150, 150));
    window.draw(shape5);

    sf::CircleShape shape6(13);
    shape6.setPosition({512, 70});
    shape6.setFillColor(sf::Color(150, 150, 150));
    window.draw(shape6);

    sf::CircleShape shape7(16);
    shape7.setPosition({514, 50});
    shape7.setFillColor(sf::Color(150, 150, 150));
    window.draw(shape7);

    sf::CircleShape shape8(19);
    shape8.setPosition({516, 30});
    shape8.setFillColor(sf::Color(150, 150, 150));
    window.draw(shape8);

    window.display();

    sf::sleep(sf::seconds(2));
}