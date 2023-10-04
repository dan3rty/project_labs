#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;

int main()
{
    constexpr float BALL_SIZE = 40;
    float speedX = 100.f;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clockY;
    sf::Clock clockX;

    sf::Vector2f position = {10, 350};

    sf::CircleShape circle(BALL_SIZE);
    circle.setFillColor(sf::Color(255, 20, 147));

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

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clockY.getElapsedTime().asSeconds();
        const float dt = clockX.restart().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = speedX * dt;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};
        position.x += offset.x;

        if ((position.x + 2 * BALL_SIZE + x >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x + x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        circle.setPosition({position.x, position.y + offset.y});

        window.clear();
        window.draw(circle);
        window.display();
    }
}