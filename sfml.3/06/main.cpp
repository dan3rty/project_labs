#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct Eye {
    sf::ConvexShape pupil;
    sf::ConvexShape sclera;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidian(float radius, float angle) {
    return {
            radius * std::cos(angle),
            radius * std::sin(angle)};
}

float toDegrees(float radians) {
    return float(double(radians) * 180.0 / M_PI);
}

void updateEye(Eye &eye) {
    sf::Vector2f pupilOffset = toEuclidian(50, eye.rotation);
    eye.pupil.setPosition(eye.position + pupilOffset);
}

void initEye(Eye &eye, float x, float y, sf::Vector2f radius, int pointCount, sf::Vector2f scleraRadius) {
    eye.pupil.setPosition({x, y});
    eye.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye.pupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                radius.x * std::sin(angle),
                radius.y * std::cos(angle)};
        eye.pupil.setPoint(pointNo, point);
    }

    eye.position = {x, y};

    eye.sclera.setPosition({x, y});
    eye.sclera.setFillColor(sf::Color(255, 0, 255));
    eye.sclera.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
                scleraRadius.x * std::sin(angle),
                scleraRadius.y * std::cos(angle)};
        eye.sclera.setPoint(pointNo, point);
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition) {
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
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

void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye) {
    const sf::Vector2f leftDelta = mousePosition - leftEye.position;
    leftEye.rotation = atan2(leftDelta.y, leftDelta.x);
    updateEye(leftEye);
    const sf::Vector2f rightDelta = mousePosition - rightEye.position;
    rightEye.rotation = atan2(rightDelta.y, rightDelta.x);
    updateEye(rightEye);
}


void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye) {
    window.clear();
    window.draw(leftEye.sclera);
    window.draw(rightEye.sclera);
    window.draw(leftEye.pupil);
    window.draw(rightEye.pupil);
    window.display();
}

int main() {
    constexpr int pointCount = 200;

    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Eyes follows mouse", sf::Style::Default, settings);
    Eye leftEye;
    Eye rightEye;
    sf::Vector2f mousePosition;

    initEye(leftEye, 300, 300, {30.f, 50.f}, pointCount, {95.f, 250.f});
    initEye(rightEye, 500, 300, {30.f, 50.f}, pointCount, {95.f, 250.f});

    while (window.isOpen()) {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}