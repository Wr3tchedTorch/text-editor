#include <iostream>
#include <SFML/Graphics.hpp>
#include "CameraManager.h"

//? Public

CameraManager::CameraManager(sf::Vector2f resolution, sf::FloatRect limits)
{
    this->limits = limits;

    camera.reset(sf::FloatRect({0, 0}, resolution));
}

CameraManager::CameraManager(sf::Vector2f resolution)
{
    camera.reset(sf::FloatRect({0, 0}, resolution));
}

void CameraManager::Move(sf::Vector2f offset)
{
    sf::Vector2f newPosition = {0, 0};
    if (offset.y > 0)
    {
        newPosition.y = GetBottomPosition() + offset.y;
        newPosition.y -= BOTTOM_PADDING;
    }
    else if (offset.y < 0)
    {
        newPosition.y = GetTopPosition() + offset.y;
    }

    camera.move(offset);

    ClampCameraPosition();
}

void CameraManager::Scroll(int direction)
{
    float movementIncrement = scrollSpeed * direction;
    Move({0, movementIncrement});
}

void CameraManager::Render(sf::RenderWindow &window)
{
    window.setView(camera);
}

sf::Vector2f CameraManager::GetSize()
{
    return camera.getSize();
}

//? Getters and Setters

void CameraManager::SetLimits(sf::FloatRect toValue)
{
    float limitPadding = 10.0f;
    float minYLimit = camera.getSize().y + limitPadding;

    if (toValue.height < minYLimit)
    {
        toValue.height = minYLimit;
    }
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

void CameraManager::ClampCameraPosition()
{
    if (GetBottomPosition() > limits.height + BOTTOM_PADDING)
    {
        camera.setCenter({camera.getSize().x / 2, limits.height - camera.getSize().y / 2 + BOTTOM_PADDING});
    }
    else if (GetTopPosition() < limits.getPosition().y)
    {
        camera.setCenter({camera.getSize().x / 2, camera.getSize().y / 2 + limits.getPosition().y});
    }
}
