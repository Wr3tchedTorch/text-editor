#include <iostream>
#include <SFML/Graphics.hpp>

struct Vector2iHash {
    std::size_t operator()(const sf::Vector2i &v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

struct Vector2iEqual 
{
    bool operator()(const sf::Vector2i &me, const sf::Vector2i &other) const {
        return me.x == other.x && me.y == other.y;
    }
};