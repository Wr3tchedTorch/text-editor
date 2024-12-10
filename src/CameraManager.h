#pragma once
#include <SFML/Graphics.hpp>

class CameraManager
{
private:
    sf::View camera;
    sf::FloatRect limits;

    float movementSpeed = 50;
    float scrollSpeed = 50;

public:
    CameraManager(sf::Vector2f resolution, sf::FloatRect limits);

    void Scroll(int direction);
    void Render(sf::RenderWindow &window);

    void SetLimits(sf::FloatRect toValue);
    sf::FloatRect GetLimits();

    void SetScrollSpeed(float toSpeed);
    float GetScrollSpeed();

    void SetMovementSpeed(float toSpeed);
    float GetMovementSpeed();

private:
    bool IsPositionValid(sf::Vector2f position);
};