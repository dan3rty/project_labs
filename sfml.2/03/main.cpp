#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    float ringRadius = 100;
    float angle = 0;
    constexpr int pointCount = 200;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Circle", sf::Style::Default, settings);

    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 300});
    ellipse.setFillColor(sf::Color(255, 20, 147));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float ellipseRadius = 200 * std::sin(6 * angle);
        sf::Vector2f point = {
            ellipseRadius * std::sin(angle),
            ellipseRadius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();

        angle += dt * 3;

        sf::Vector2f position = {
            ringRadius * std::sin(angle) + 400,
            ringRadius * std::cos(angle) + 300};
        ellipse.setPosition(position);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}