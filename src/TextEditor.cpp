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

    DrawText(window, fontScale, fontColor);

    DrawCursor(window);
}

void TextEditor::Update(float delta)
{
    time = fmod(time, 2 * M_PI);
    cursorAlpha = static_cast<int>(200 * ((std::sin(time) + 1)/2));
    time += .055f;
}

void TextEditor::AddCharacterAtCursorPosition(char character)
{
    text.at(currentCursorPosition.y).insert(currentCursorPosition.x, std::string(1, character));
    MoveCursor({1, 0});
    CalculateCellsWidth();
}

void TextEditor::CreateNewLineAtCursorPosition()
{
    std::string previousLine = text.at(currentCursorPosition.y);
    std::string line1 = previousLine.substr(0, currentCursorPosition.x) + " ";
    std::string line2 = previousLine.substr(currentCursorPosition.x);

    currentCursorPosition.x = 0;

    text.at(currentCursorPosition.y) = line1;
    text.insert(text.begin() + currentCursorPosition.y + 1, line2);

    CalculateCellsWidth();

    currentCursorPosition.y++;
}

void TextEditor::MarkSelectedCells()
{
    if (startingPosition.x == -1 &&
        startingPosition.y == -1) 
    {
        startingPosition = currentCursorPosition;
    }

    int x = startingPosition.x, y = startingPosition.y;
    while (!(x == currentCursorPosition.x &&
             y == currentCursorPosition.y))
    {
        selectedPositions.insert({x, y});

        if (currentCursorPosition.y > y &&
            y + 1 < GetTextHeight()) 
        {
            if (startingPosition.y > y) 
            {
                std::cout << "\nGoing Down: removing cells as selected" << std::endl;
                UnmarkLineCellsAsSelected(y);
            }
            y++;
            x = 0;
        }
        else if (currentCursorPosition.y < y &&
                 y - 1 > 0)
        {
            if (startingPosition.y < y) 
            {
                std::cout << "\nGoing Up: removing cells as selected" << std::endl;
                UnmarkLineCellsAsSelected(y);
            }
            y--;
            x = 0;
        }

        if (currentCursorPosition.x > x &&
            x + 1 < GetLineSize(y)) 
        {
            x++;
            selectedPositions.erase({x, y});
        }
        else if (currentCursorPosition.x < x &&
                 x - 1 > 0)
        {
            x--;
            selectedPositions.erase({x, y});
        }
    }
}

void TextEditor::UnmarkLineCellsAsSelected(int line)
{
    if (line < 0 ||
        line > GetTextHeight()) 
    {
        return;
    }

    for (size_t x = 0; x < GetLineSize(line); x++)
    {
        selectedPositions.erase({x, line});
    }
}

void TextEditor::DeleteCharacterAtCursorPosition()
{
    if (currentCursorPosition.x == 0)
    {
        DeleteLineAtCursorPosition();
        return;
    }

    text.at(currentCursorPosition.y).erase(currentCursorPosition.x - 1, 1);
    MoveCursor({-1, 0});
    CalculateCellsWidth();
}

void TextEditor::DeleteLineAtCursorPosition()
{
    if (currentCursorPosition.y == 0)
        return;

    sf::Vector2i newCursorPosition = {static_cast<int>(text.at(currentCursorPosition.y - 1).size()), currentCursorPosition.y - 1};
    std::string currentLineContent = text.at(currentCursorPosition.y);

    text.at(newCursorPosition.y) += currentLineContent;
    text.erase(text.begin() + currentCursorPosition.y);

    CalculateCellsWidth();
    currentCursorPosition = newCursorPosition;
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

sf::Vector2f TextEditor::GetCursorPosition()
{
    return GetPositionFromGridCoordinates(currentCursorPosition);
}

sf::Vector2i TextEditor::GetCursorGridCoordinate()
{
    return currentCursorPosition;
}

void TextEditor::SetCursorPosition(sf::Vector2i globalPosition)
{
    if (globalPosition.x < 0 || globalPosition.y < 0)
        return;

    sf::Vector2i toPosition = GetGridCoordinatesFromPosition(globalPosition);

    if (toPosition.x < 0 || toPosition.y < 0)
        return;

    currentCursorPosition = toPosition;
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
            widthList.insert(widthList.end(), cachedWidth);
            cachedWidth += GetCharFontWidth(currentChar) + kerning;
            previousChar = currentChar;
        }
        cellCoordinateWidth.insert(cellCoordinateWidth.end(), widthList);
    }
}

void TextEditor::SetText(std::vector<std::string> toValue)
{
    for (std::string &line : toValue)
    {
        if (line == " ")
            continue;
        line.push_back(' ');
    }
    text = toValue;
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

void TextEditor::DrawText(sf::RenderWindow &window, unsigned int charSize, sf::Color fontColor)
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
    sf::Vector2f cursorPosition = GetPositionFromGridCoordinates(currentCursorPosition);
    float cursorWidth = GetCharFontWidth(text.at(currentCursorPosition.y).at(currentCursorPosition.x));
    float cursorHeight = charSize + CURSOR_Y_PADDING;

    sf::Color cursorColor = cursorHighlightShape.getFillColor();
    cursorColor.a = cursorAlpha;

    cursorHighlightShape.setFillColor(cursorColor);
    cursorHighlightShape.setSize({cursorWidth, cursorHeight});
    cursorHighlightShape.setPosition(cursorPosition);    
    window.draw(cursorHighlightShape);

    cursorColor.a = 200;
    for (auto position : selectedPositions) 
    {
        float cellWidth = GetCharFontWidth(text.at(currentCursorPosition.y).at(currentCursorPosition.x));
        float cellHeight = charSize + CURSOR_Y_PADDING;
        cursorHighlightShape.setSize({cellWidth, cellHeight});
        cursorHighlightShape.setFillColor(cursorColor);
        cursorHighlightShape.setPosition(GetPositionFromGridCoordinates(position));
        window.draw(cursorHighlightShape);
    }
}

sf::Vector2f TextEditor::GetPositionFromGridCoordinates(sf::Vector2i coordinates)
{
    sf::Vector2f position;
    position.y = coordinates.y * lineHeight + EDITOR_Y_OFFSET - CURSOR_Y_PADDING / 2;
    position.x = cellCoordinateWidth.at(coordinates.y).at(coordinates.x) + EDITOR_X_OFFSET;
    return position;
}

sf::Vector2i TextEditor::GetGridCoordinatesFromPosition(sf::Vector2i position)
{
    int x = -1, y = -1;

    for (size_t i = 0; i < text.size(); i++)
    {
        float sum;
        sum = GetLineHeight() * i + GetLineHeight() + EDITOR_Y_OFFSET;

        if (sum >= position.y)
        {
            y = i;
            break;
        }
    }

    for (size_t i = 0; i < text.at(y).size(); i++)
    {
        if (cellCoordinateWidth.at(y).at(i) + EDITOR_X_OFFSET >= position.x)
        {
            x = i;
            if (x > 0)
                x--;
            break;
        }
    }
    if (x == -1)
    {
        x = text.at(y).size() - 1;
    }
    return {x, y};
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
