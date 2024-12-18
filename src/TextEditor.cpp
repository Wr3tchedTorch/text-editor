#include <cmath>
#include "TextEditor.h"

//? Public

TextEditor::TextEditor(std::vector<std::string> text, sf::Font fontFamily, sf::Color cursorColor)
{
    this->fontFamily = fontFamily;
    SetText(text);

    cursorHighlightShape.setFillColor(cursorColor);
}

TextEditor::TextEditor(sf::Color cursorColor, sf::Font fontFamily)
{
    this->fontFamily = fontFamily;
    cursorHighlightShape.setFillColor(cursorColor);
}

void TextEditor::Draw(sf::RenderWindow &window, unsigned int fontScale, sf::Color fontColor)
{
    this->fontFamily = fontFamily;

    DrawText(window, fontFamily, fontScale, fontColor);

    DrawCursor(window);
}

float TextEditor::GetTextHeight()
{
    return text.size() * GetLineHeight();
}

float TextEditor::GetTextWidth()
{
    float highestSize = 0.0f;
    for (const std::string line : text)
    {        
        float lineSize = GetCharSequenceTotalFontWidth(line);
        if (lineSize > highestSize)
        {
            highestSize = lineSize;
        }
    }
    return highestSize;
}

float TextEditor::GetLineSize(int lineIndex)
{
    return text.at(lineIndex).size();
}

int TextEditor::GetTotalNumberOfLines()
{
    return text.size();
}

void TextEditor::MoveCursor(sf::Vector2i offset)
{
    sf::Vector2i toCursorPosition = currentCursorPosition;
    toCursorPosition += offset;

    ClampPosition(toCursorPosition);

    currentCursorPosition = toCursorPosition;
}

void TextEditor::CalculateCellsWidth()
{
    cellCoordinateWidth.clear();

    for (size_t y = 0; y < GetTotalNumberOfLines(); y++)
    {
        std::vector<float> widthList;

        float cachedWidth = 0;
        char previousChar = '\0';
        for (size_t x = 0; x < GetLineSize(y); x++)
        {
            char currentChar = text.at(y).at(x);
            float kerning = fontFamily.getKerning(previousChar, currentChar, charSize);
            cachedWidth += GetCharFontWidth(currentChar) + kerning;

            widthList.insert(widthList.end(), cachedWidth);
            previousChar = currentChar;
        }
        cellCoordinateWidth.insert(cellCoordinateWidth.end(), widthList);
    }
}

void TextEditor::SetText(std::vector<std::string> toValue)
{
    text = toValue;
    if (!isFirstTimeBeingDraw)
    {
        CalculateCellsWidth();
    }
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

void TextEditor::DrawText(sf::RenderWindow &window, sf::Font fontFamily, unsigned int charSize, sf::Color fontColor)
{
    sf::Text textToDraw("", fontFamily, charSize);
    textToDraw.setFillColor(fontColor);

    sf::Vector2f textPosition = {EDITOR_X_OFFSET, EDITOR_Y_OFFSET};
    for (size_t i = 0; i < GetTotalNumberOfLines(); i++)
    {
        std::string lineNumberIndicator = std::to_string(i + 1) + "  ";
        sf::Vector2f linePosition = {textPosition.x - GetCharSequenceTotalFontWidth(lineNumberIndicator), textPosition.y};

        textToDraw.setString(lineNumberIndicator + text.at(i));
        textToDraw.setPosition(linePosition);
        window.draw(textToDraw);

        textPosition.y += GetLineHeight();
    }
}

void TextEditor::DrawCursor(sf::RenderWindow &window)
{
    if (isFirstTimeBeingDraw)
    {
        CalculateCellsWidth();
        isFirstTimeBeingDraw = false;
    }

    sf::Vector2f cursorPosition = GetPositionFromGridCoordinates(currentCursorPosition);
    float cursorWidth = GetCharFontWidth(text.at(currentCursorPosition.y).at(currentCursorPosition.x));
    float cursorHeight = charSize + CURSOR_Y_PADDING;

    cursorHighlightShape.setSize({cursorWidth, cursorHeight});
    cursorHighlightShape.setPosition(cursorPosition);
    window.draw(cursorHighlightShape);
}

sf::Vector2f TextEditor::GetPositionFromGridCoordinates(sf::Vector2i coordinates)
{
    sf::Vector2f position;
    position.y = coordinates.y * lineHeight + EDITOR_Y_OFFSET - CURSOR_Y_PADDING / 2;
    position.x = cellCoordinateWidth.at(coordinates.y).at(coordinates.x) + EDITOR_X_OFFSET;
    return position;
}

float TextEditor::GetCharFontWidth(char character)
{
    return fontFamily.getGlyph(character, charSize, false).advance;
}

float TextEditor::GetCharSequenceTotalFontWidth(std::string charSequence)
{
    float total = 0;
    for (char c : charSequence)
    {
        total += GetCharFontWidth(c);
    }
    return total;
}

sf::Vector2i TextEditor::ClampPosition(sf::Vector2i &position)
{
    int totalNumOfLines = GetTotalNumberOfLines() - 1;
    if (position.y < 0)
    {
        position.y = 0;
    }
    else if (position.y > totalNumOfLines)
    {
        position.y = totalNumOfLines;
    }

    int lineWidth = GetLineSize(position.y) - 1;
    if (position.x < 0)
    {
        position.x = 0;
    }
    else if (position.x > lineWidth)
    {
        position.x = lineWidth;
    }
}
