#include <cmath>
#include "TextEditor.h"

//? Public

TextEditor::TextEditor(std::vector<std::string> text, sf::Color cursorColor)
{
    SetText(text);

    currentCursorPosition = {0, 0};
    cursorHighlightShape.setFillColor(cursorColor);
}

void TextEditor::Draw(sf::RenderWindow &window, sf::Font fontFamily, unsigned int fontScale, sf::Color fontColor)
{
    this->fontFamily = fontFamily;

    sf::Text textToDraw("", fontFamily, charSize);
    textToDraw.setColor(fontColor);

    int lineCounter = 1;
    sf::Vector2f textPosition = {EDITOR_X_OFFSET, EDITOR_Y_OFFSET};
    for (auto line : text)
    {
        std::string lineHeader = std::to_string(lineCounter++) + "  ";
        textToDraw.setString(lineHeader + line);
        textToDraw.setPosition(sf::Vector2f(textPosition.x - GetCharsWidth(lineHeader), textPosition.y));
        window.draw(textToDraw);

        textPosition.y += GetLineHeight();
    }

    if (!hasBeenDraw)
        CalculateCellsWidth();

    cursorHighlightShape.setSize(sf::Vector2f(GetCharWidth(text.at(currentCursorPosition.y).at(currentCursorPosition.x)), charSize + CURSOR_Y_PADDING));
    cursorHighlightShape.setPosition(GetPositionFromGridCoordinates(currentCursorPosition));
    window.draw(cursorHighlightShape);
    hasBeenDraw = true;
}

float TextEditor::GetTextHeight()
{
    return text.size() * GetLineHeight();
}

float TextEditor::GetLineWidth(int lineIndex)
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
    if (toCursorPosition.x < 0)
        toCursorPosition.x = 0;
        
    if (toCursorPosition.y < 0)
        toCursorPosition.y = 0;

    int totalNumOfLines = GetTotalNumberOfLines() - 1;
    if (toCursorPosition.y >= totalNumOfLines)
        toCursorPosition.y = totalNumOfLines;

    int lineWidth = GetLineWidth(toCursorPosition.y) - 1;
    if (toCursorPosition.x >= lineWidth)
        toCursorPosition.x = lineWidth;

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
        char previousChar = '\0';
        float cachedWidth = 0;
        for (char character : line)
        {
            float kerning = fontFamily.getKerning(previousChar, character, charSize);
            widthList.insert(widthList.end(), cachedWidth);
            cachedWidth += GetCharWidth(character) + kerning;

            previousChar = character;
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
    position.y = coordinates.y * lineHeight + EDITOR_Y_OFFSET - CURSOR_Y_PADDING / 2;

    position.x = cellCoordinateWidth.at(coordinates.y).at(coordinates.x) + EDITOR_X_OFFSET;
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
