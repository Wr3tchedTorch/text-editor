#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

struct KeyCombination
{
    sf::Keyboard::Key key;

    bool ctrl  = false;
    bool shift = false;
    bool alt   = false;

    bool operator==(const KeyCombination &other) const
    {
        return key   == other.key   &&
               ctrl  == other.ctrl  &&
               shift == other.shift &&
               alt   == other.alt;
    }

    std::string toString() 
    {
        std::stringstream result;

        if (ctrl)  result << "Ctrl + ";
        if (shift) result << "Shift + ";
        if (alt)   result << "Alt + ";        

        result << key;

        return result.str();
    }
};

struct KeyCombinationHash
{
    std::size_t operator()(const KeyCombination &keyCombination) const
    {
        return std::hash<int>()(static_cast<int>(keyCombination.key)) ^
               (std::hash<bool>()(keyCombination.ctrl)  << 1)  ^
               (std::hash<bool>()(keyCombination.shift) << 2)  ^
               (std::hash<bool>()(keyCombination.alt)   << 3);
    }
};
