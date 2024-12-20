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

    sf::Vector2i currentCursorPosition = {0, 0};
    sf::RectangleShape cursorHighlightShape;

    sf::Font fontFamily;
    float lineHeight;
    unsigned int charSize = 30;    

public:
    TextEditor(std::vector<std::string> text, sf::Font fontFamily, sf::Color cursorColor);
    TextEditor(sf::Color cursorColor, sf::Font fontFamily);
    void Draw(sf::RenderWindow &window, unsigned int charSize, sf::Color fontColor);

    void AddCharacterAtCursorPosition(char character);
    void DeleteCharacterAtCursorPosition();

    void MoveCursor(sf::Vector2i offset);
    void CalculateCellsWidth();

    float GetTextHeight();
    float GetTextWidth();

    float GetLineSize(int lineIndex);
    int GetTotalNumberOfLines();

    sf::Vector2f GetCursorPosition();
    sf::Vector2i GetCursorGridCoordinate();

    void SetText(std::vector<std::string> toValue);
    std::vector<std::string> GetText();

    void SetLineHeight(float toValue);
    float GetLineHeight();

private:    
    void DrawText(sf::RenderWindow &window, unsigned int charSize, sf::Color fontColor);
    void DrawCursor(sf::RenderWindow &window);

    sf::Vector2f GetPositionFromGridCoordinates(sf::Vector2i coordinates);
    float GetCharFontWidth(char character);
    float GetCharSequenceTotalFontWidth(std::string charSequence);

    sf::Vector2i ClampPosition(sf::Vector2i & position);
};