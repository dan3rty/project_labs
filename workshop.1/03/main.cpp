#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


void onMouseClick(const sf::Event::MouseButtonEvent& event, sf::Vector2f& mousePosition)
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
            case sf::Event::MouseButtonPressed:
                onMouseClick(event.mouseButton, mousePosition);
                break;
            default:
                break;
        }
    }
}

void setScale(sf::Sprite& player, float widthMultiplier, float heightMultiplier)
{
    sf::Vector2f targetSize(sf::VideoMode::getDesktopMode().height / 20, sf::VideoMode::getDesktopMode().height / 20);
    player.setScale(
            targetSize.x / player.getLocalBounds().width * widthMultiplier,
            targetSize.y / player.getLocalBounds().height * heightMultiplier
    );
}

void updatePosition(const sf::Vector2f& mousePosition, sf::Sprite& player, float dt)
{
    const sf::Vector2f delta = mousePosition - player.getPosition();
    const float deltaLength = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    const sf::Vector2f direction = { delta.x / deltaLength, delta.y / deltaLength };
    const float speed = 20.0f;
    player.move(direction * speed * dt);
    if (delta.x >= 0)
    {
        setScale(player, 1, 1);
    }
    else
    {
        setScale(player, -1, 1);
    }
}

void update(const sf::Vector2f& mousePosition, sf::Sprite& player, sf::Clock& clock, sf::Sprite& pointer)
{
    const float dt = clock.restart().asSeconds();
    pointer.setPosition(mousePosition);
    updatePosition(mousePosition, player, dt);
}

void redrawFrame(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& pointer)
{
    window.clear(sf::Color::White);
    window.draw(player);
    window.draw(pointer);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode::getDesktopMode(),
            "Kitty :3", sf::Style::Fullscreen, settings);

    sf::Vector2f mousePosition;
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("cat.png"))
    {
        std::wcerr << L"Ошибочька загрузки картиночьки" << std::endl;
        exit(1);
    }

    sf::Texture pointerTexture;
    if (!pointerTexture.loadFromFile("red_pointer.png"))
    {
        std::wcerr << L"Ошибка загрузки спрайта указки" << std::endl;
        exit(1);
    }

    sf::Sprite pointer(pointerTexture);
    pointer.setOrigin(pointer.getLocalBounds().width / 2, pointer.getLocalBounds().height / 2);
    setScale(pointer, 1, 1);


    sf::Sprite player(playerTexture);
    player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
    setScale(player, 1, 1);

    player.setPosition(
            sf::VideoMode::getDesktopMode().width / 2,
            sf::VideoMode::getDesktopMode().height / 2
    );

    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, player, clock, pointer);
        redrawFrame(window, player, pointer);
    }
}