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
    sf::Vector2f bottomPosition = GetBottomPosition() + offset;
    bottomPosition.y -= BOTTOM_PADDING;

    if (IsPositionValid(bottomPosition) &&
        IsPositionValid(GetTopPosition() + offset))
    {
        camera.move(offset);
    }
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