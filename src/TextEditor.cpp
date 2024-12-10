#include "TextEditor.h"

//? Public

TextEditor::TextEditor(std::vector<std::string> text)
{
    this->text = text;
}

void TextEditor::Draw(sf::RenderWindow &window, sf::Font fontFamily, float fontScale, sf::Color fontColor)
{
    sf::Text textToDraw;
    textToDraw.setFont(fontFamily);
    textToDraw.setScale(fontScale, fontScale);
    textToDraw.setColor(fontColor);

    int lineCounter = 1;
    sf::Vector2f textPosition = {20.0f, 20.0f};
    for (auto line : text)
    {
        textToDraw.setString(std::to_string(lineCounter++) + "  " + line);
        textToDraw.setPosition(textPosition);
        window.draw(textToDraw);

        textPosition.y += GetLineHeight();
    }
}

float TextEditor::GetTextHeight()
{
    return text.size() * GetLineHeight();
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