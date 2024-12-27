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

void CameraManager::CenterAtPosition(sf::Vector2f position)
{
    if (position.y > GetTopPosition() && position.y < GetBottomPosition())
    {
        position.y = camera.getCenter().y;
    }
    if (position.x > GetLeftPosition() && position.x < GetRightPosition())
    {
        position.x = camera.getCenter().x;
    }
    
    camera.setCenter(position);
    ClampCameraPosition();
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

float CameraManager::GetMovementSpeed()
{
    return movementSpeed;
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
        camera.setCenter({camera.getCenter().x, limits.height - camera.getSize().y / 2 + BOTTOM_PADDING});
    }
    else if (GetTopPosition() < limits.getPosition().y)
    {
        camera.setCenter({camera.getCenter().x, camera.getSize().y / 2 + limits.getPosition().y});
    }

    if (GetRightPosition() > limits.width)
    {
        camera.setCenter({limits.width - camera.getSize().x / 2, camera.getCenter().y});
    }
    else if (GetLeftPosition() < limits.getPosition().x)
    {
        camera.setCenter({limits.getPosition().x + camera.getSize().x / 2, camera.getCenter().y});
    }
}
