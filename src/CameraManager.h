#pragma once
#include <SFML/Graphics.hpp>

class CameraManager
{
private:
    const float BOTTOM_PADDING = 100.0f;

    sf::View camera;
    sf::FloatRect limits;

    float movementSpeed = 50;
    float scrollSpeed = 50;


    sf::Vector2f GetBottomPosition() const
    {
        return camera.getCenter() + camera.getSize() / 2.0f;
    }

    sf::Vector2f GetTopPosition() const
    {
        return camera.getCenter() - camera.getSize() / 2.0f;
    }

public:
    CameraManager(sf::Vector2f resolution, sf::FloatRect limits);
    CameraManager(sf::Vector2f resolution);

    void Move(sf::Vector2f direction);
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