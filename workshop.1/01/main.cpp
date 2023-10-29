#include <SFML/Graphics.hpp>
#include <cmath>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({400, 300});

    arrow.setPointCount(7);
    arrow.setPoint(0, { -60, -30 });
    arrow.setPoint(1, { 0, -30 });
    arrow.setPoint(2, { 0, -60 });
    arrow.setPoint(3, { 47, 0 });
    arrow.setPoint(4, { 0, 60 });
    arrow.setPoint(5, { 0, 30 });
    arrow.setPoint(6, { -60, 30 });


    arrow.setFillColor(sf::Color::Yellow);
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(3);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove, mousePosition);
                break;
            default:
                break;
        }
    }
}

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock &clock)
{
    const float dt = clock.restart().asSeconds();
    const sf::Vector2f deltaRotation = mousePosition - arrow.getPosition();
    float angle = toDegrees(atan2(deltaRotation.y, deltaRotation.x));
    float rotation;
    float prevRotation = arrow.getRotation();

    if (angle < 0)
    {
        angle += 360;
    }
    if (std::abs(360 - prevRotation + angle) > 360)
    {
        angle -= 360;
    }
    if (std::abs(360 - prevRotation + angle) > std::abs(angle - prevRotation))
    {
        rotation = -90 * dt;
    }
    else
    {
        rotation = 90 * dt;
    }
    arrow.rotate(rotation);
    const sf::Vector2f deltaPosition = mousePosition - arrow.getPosition();
    const float deltaLength = std::sqrt(deltaPosition.x * deltaPosition.x + deltaPosition.y * deltaPosition.y);
    const sf::Vector2f direction = { deltaPosition.x / deltaLength, deltaPosition.y / deltaLength };
    const float speed = 20.0f;
    arrow.move(direction * speed * dt);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
    window.clear(sf::Color::White);
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Arrow follows mouse", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }
}
