#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class TextEditor
{
private:
    std::vector<std::string> text;

    float lineHeight;

public:
    TextEditor(std::vector<std::string> text);
    void Draw(sf::RenderWindow &window, sf::Font fontFamily, float fontScale, sf::Color fontColor);
    float GetTextHeight();
    
    void SetLineHeight(float toValue);
    float GetLineHeight();

private:
    void WrapText();
};