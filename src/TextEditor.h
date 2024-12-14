#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class TextEditor
{
private:
    const float EDITOR_X_OFFSET = 70.0f;
    const float EDITOR_Y_OFFSET = 20.0f;

    const float CURSOR_Y_PADDING = 20.0f;

    std::vector<std::string> text;
    std::vector<std::vector<float>> cellCoordinateWidth;

    sf::Vector2i currentCursorPosition;
    sf::RectangleShape cursorHighlightShape;

    sf::Font fontFamily;
    unsigned int charSize = 30;
    bool hasBeenDraw = false;    
    float lineHeight;

public:
    TextEditor(std::vector<std::string> text, sf::Color cursorColor);
    void Draw(sf::RenderWindow &window, sf::Font fontFamily, unsigned int charSize, sf::Color fontColor);

    float GetTextHeight();
    float GetLineWidth(int lineIndex);
    int GetTotalNumberOfLines();

    void MoveCursor(sf::Vector2i offset);
    void MoveCursor(float xOffset, float yOffset);

    void CalculateCellsWidth();

    void SetText(std::vector<std::string> toValue);
    std::vector<std::string> GetText();

    void SetLineHeight(float toValue);
    float GetLineHeight();

private:
    sf::Vector2f GetPositionFromGridCoordinates(sf::Vector2i coordinates);
    float GetCharWidth(char character);
    float GetCharsWidth(std::string charSequence);
};