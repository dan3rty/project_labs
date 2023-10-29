#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arrow");

    sf::ConvexShape arrow;
    arrow.setPointCount(7);
    arrow.setPoint(0, { -60, -30 });
    arrow.setPoint(1, { 0, -30 });
    arrow.setPoint(2, { 0, -60 });
    arrow.setPoint(3, { 47, 0 });
    arrow.setPoint(4, { 0, 60 });
    arrow.setPoint(5, { 0, 30 });
    arrow.setPoint(6, { -60, 30 });

    arrow.setPosition(300, 200);

    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(arrow);

        window.display();
    }

}