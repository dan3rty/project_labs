#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

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
            default:
                break;
        }
    }
}

void redrawFrame(sf::RenderWindow& window, sf::Sprite& cat)
{
    window.clear(sf::Color::White);
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
            "Cat", sf::Style::Default, settings);


    sf::Vector2f mousePosition;
    sf::Texture catTexture;
    if (!catTexture.loadFromFile("cat.png"))
    {
        wcerr << L"Ошибка загрузки изображения" << endl;
        exit(1);
    }

    sf::Sprite cat(catTexture);
    cat.setPosition(
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
    );
    sf::Vector2f targetSize(40, 40);

    cat.setScale(
            targetSize.x / cat.getLocalBounds().width,
            targetSize.y / cat.getLocalBounds().height);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        redrawFrame(window, cat);
    }
}