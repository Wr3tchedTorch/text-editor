#pragma once
#include <SFML/Graphics.hpp>

class CameraManager
{
public:
    float GetBottomPosition() const
    {
        return camera.getCenter().y + camera.getSize().y / 2.0f;
    }

    float GetTopPosition() const
    {
        return camera.getCenter().y - camera.getSize().y / 2.0f;
    }

private:
    const float BOTTOM_PADDING = 100.0f;

    sf::View camera;
    sf::FloatRect limits;

    float movementSpeed = 50;
    float scrollSpeed = 50;

public:
    CameraManager(sf::Vector2f resolution, sf::FloatRect limits);
    CameraManager(sf::Vector2f resolution);

    void Move(sf::Vector2f direction);
    void Scroll(int direction);
    void Render(sf::RenderWindow &window);

    sf::Vector2f GetSize();

    void SetLimits(sf::FloatRect toValue);
    sf::FloatRect GetLimits();

    void SetScrollSpeed(float toSpeed);
    float GetScrollSpeed();

    void SetMovementSpeed(float toSpeed);
    float GetMovementSpeed();

private:
    bool IsPositionValid(sf::Vector2f position);
    void ClampCameraPosition();
};