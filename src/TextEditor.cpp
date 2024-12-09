#include "TextEditor.h"

TextEditor::TextEditor(std::vector<std::string> text)
{
    this->text = text;
}

void TextEditor::Draw(sf::RenderWindow &window, sf::Font fontFamily, float fontScale, float lineHeight)
{
    sf::Text textToDraw;
    textToDraw.setFont(fontFamily);
    textToDraw.setScale(fontScale, fontScale);    

    sf::Vector2f textPosition = {20.0f, 20.0f};
    for (auto line : text)
    {
        textToDraw.setString(line);
        textToDraw.setPosition(textPosition);
        window.draw(textToDraw);

        textPosition.y += lineHeight;
    }
}
