#include <SFML/Graphics.hpp>
#include <cmath>

float rotationSpeed = 15.0f;


float toDegrees(float radians)
{
    return float(radians * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{

    mousePosition = {float(event.x), float(event.y)};
}

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(255, 105, 180));
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event{};

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

void update(sf::ConvexShape &pointer, const float dt, const sf::Vector2f &mousePosition)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = toDegrees(std::atan2(delta.y, delta.x));
    float currentRotation = pointer.getRotation();
    if (std::abs(currentRotation - angle) > std::abs(currentRotation - (angle + 360)))
    {
        angle += 360;
    }
    float rotation = angle - currentRotation;
    float rotatePath = rotationSpeed * dt;
    if (rotation > rotatePath)
    {
        angle = currentRotation + rotatePath;
    }
    else if (rotation < -rotatePath)
    {
        angle = currentRotation - rotatePath;
    }
    pointer.setRotation(angle);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    sf::Clock clock;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer slowly follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(pointer, dt, mousePosition);
        redrawFrame(window, pointer);
    }
}