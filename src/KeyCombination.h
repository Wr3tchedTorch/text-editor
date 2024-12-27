#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

struct KeyCombination
{
    sf::Keyboard::Key key;

    bool ctrl  = false;
    bool shift = false;
    bool alt   = false;

    bool operator==(const KeyCombination &other)
    {
        return key   == other.key   &&
               ctrl  == other.ctrl  &&
               shift == other.shift &&
               alt   == other.alt;
    }
};

struct KeyCombinationHash
{
    std::size_t operator()(const KeyCombination &keyCombination)
    {
        return std::hash<int>()(static_cast<int>(keyCombination.key)) ^
               (std::hash<bool>()(keyCombination.ctrl)  << 1)  ^
               (std::hash<bool>()(keyCombination.shift) << 2)  ^
               (std::hash<bool>()(keyCombination.alt)   << 3);
    }
};
