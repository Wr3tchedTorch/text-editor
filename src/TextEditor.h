#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class TextEditor
{
private:
    std::vector<std::string> text;

public:
    TextEditor(std::vector<std::string> text);
    void Draw(sf::RenderWindow &window, sf::Font fontFamily, float fontScale, float lineHeight);

private:
    void WrapText();
};