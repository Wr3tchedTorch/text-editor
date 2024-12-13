#include <cmath>
#include "TextEditor.h"

//? Public

TextEditor::TextEditor(std::vector<std::string> text)
{
    SetText(text);

    currentCursorPosition = {0, 0};
    cursorHighlightShape.setFillColor(sf::Color::White);
}

void TextEditor::Draw(sf::RenderWindow &window, sf::Font fontFamily, unsigned int fontScale, sf::Color fontColor)
{
    this->fontFamily = fontFamily;

    sf::Text textToDraw("", fontFamily, charSize);
    textToDraw.setColor(fontColor);

    int lineCounter = 1;
    sf::Vector2f textPosition = {EDITOR_OFFSET, EDITOR_OFFSET};
    for (auto line : text)
    {
        textToDraw.setString(std::to_string(lineCounter++) + "  " + line);
        textToDraw.setPosition(textPosition);
        window.draw(textToDraw);

        textPosition.y += GetLineHeight();
    }

    if (!hasBeenDraw)
        CalculateCellsWidth();

    cursorHighlightShape.setSize(sf::Vector2f(GetCharWidth(text.at(currentCursorPosition.y).at(currentCursorPosition.x)), charSize));
    cursorHighlightShape.setPosition(GetPositionFromGridCoordinates(currentCursorPosition));
    window.draw(cursorHighlightShape);
    hasBeenDraw = true;
}

float TextEditor::GetTextHeight()
{
    return text.size() * GetLineHeight();
}

void TextEditor::MoveCursor(sf::Vector2i offset)
{
    sf::Vector2i toCursorPosition = currentCursorPosition;

    // ! ADD: limit offset within the max grid length and height as well
    toCursorPosition += offset;
    if (toCursorPosition.x < 0 || toCursorPosition.y < 0)
        return;

    currentCursorPosition = toCursorPosition;
}

void TextEditor::MoveCursor(float xOffset, float yOffset)
{
    MoveCursor(sf::Vector2i(xOffset, yOffset));
}

void TextEditor::CalculateCellsWidth()
{
    cellCoordinateWidth.clear();

    int i = 0, j = 0;
    for (std::string line : text)
    {
        std::vector<float> widthList;
        float cachedWidth = 0;
        for (char character : line)
        {
            float charWidth = GetCharWidth(character);
            widthList.insert(widthList.end(), charWidth + cachedWidth);
            cachedWidth += charWidth;
            j++;
        }
        cellCoordinateWidth.insert(cellCoordinateWidth.end(), widthList);
        i++;
    }
}

void TextEditor::SetText(std::vector<std::string> toValue)
{
    text = toValue;
    if (hasBeenDraw)
        CalculateCellsWidth();
}

std::vector<std::string> TextEditor::GetText()
{
    return text;
}

//? Getters and Setters

void TextEditor::SetLineHeight(float toValue)
{
    if (toValue < 0)
        return;
    lineHeight = toValue;
}

float TextEditor::GetLineHeight()
{
    return lineHeight;
}

//? Private

sf::Vector2f TextEditor::GetPositionFromGridCoordinates(sf::Vector2i coordinates)
{
    sf::Vector2f position;
    position.y = coordinates.y * lineHeight + EDITOR_OFFSET;

    float totalXoffset = GetCharsWidth("00") + EDITOR_OFFSET;
    position.x = cellCoordinateWidth.at(coordinates.y).at(coordinates.x) + totalXoffset;
    return position;
}

float TextEditor::GetCharWidth(char character)
{
    return fontFamily.getGlyph(character, charSize, false).advance;
}

float TextEditor::GetCharsWidth(std::string charSequence)
{
    float total = 0;
    for (char c : charSequence)
    {
        total += fontFamily.getGlyph(c, charSize, false).advance;
    }
    return total;
}
