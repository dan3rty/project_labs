#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    const sf::Vector2f position = {10, 350};

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

        constexpr float speedX = 100.f;
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        // if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        // {
        //     speed.x = -speed.x;
        // }
        // if ((position.x < 0) && (speed.x < 0))
        // {
        //     speed.x = -speed.x;
        // }
        // if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
        // {
        //     speed.y = -speed.y;
        // }
        // if ((position.y < 0) && (speed.y < 0))
        // {
        //     speed.y = -speed.y;
        // }

        circle.setPosition(position + offset);

        window.clear();
        window.draw(circle);
        window.display();
    }
}