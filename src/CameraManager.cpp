#include <SFML/Graphics.hpp>
#include "CameraManager.h"

//? Public

CameraManager::CameraManager(sf::Vector2f resolution, sf::FloatRect limits)
{
    this->limits = limits;

    camera.reset(sf::FloatRect({0, 0}, resolution));
}

void CameraManager::Scroll(int direction)
{
    float movementIncrement = scrollSpeed * direction;

    sf::Vector2f newPosition = camera.getCenter() - camera.getSize() / 2.0f;
    newPosition.y += movementIncrement;
    if (!IsPositionValid(newPosition))
        return;

    camera.move(0, movementIncrement);
}

void CameraManager::Render(sf::RenderWindow &window)
{
    window.setView(camera);
}

//? Getters and Setters

void CameraManager::SetLimits(sf::FloatRect toValue)
{
    limits = toValue;
}

sf::FloatRect CameraManager::GetLimits()
{
    return limits;
}

void CameraManager::SetScrollSpeed(float toSpeed)
{
    if (toSpeed < 0)
        return;
    scrollSpeed = toSpeed;
}

float CameraManager::GetScrollSpeed()
{
    return scrollSpeed;
}

//? Private

bool CameraManager::IsPositionValid(sf::Vector2f position)
{
    return limits.contains(position);
}